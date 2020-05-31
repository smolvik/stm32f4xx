#include "stm32f407xx.h"

#define FLASH_START 0x8000000
#define NUM_IRQS	98
#define SYS_TICKS	144000
#define LED_PIN 9

extern void USART2_Handler_RAM(void);

void (* table_interrupt_vector_RAM[NUM_IRQS])(void) __attribute__((aligned (256)));

volatile uint32_t system_time;

void SysTick_Handler_RAM(void)
{
	system_time ++;
}

void set_ram_vt()
{
	uint32_t i = 0;
	uint32_t *ps = (uint32_t*)FLASH_START;
	uint32_t *pd = (uint32_t*) table_interrupt_vector_RAM;

	// copy vector table with default values from flash to ram	
	for(i = 0; i < NUM_IRQS; i++){
		*pd++ = ps[i];
	}
	
	// replase default Vt values with RAM handlers
	table_interrupt_vector_RAM[15] = SysTick_Handler_RAM;
	table_interrupt_vector_RAM[54] = USART2_Handler_RAM;

	
	// set vtor
	SCB->VTOR = ((uint32_t)table_interrupt_vector_RAM);
	__DSB();
}

void sleep(uint32_t ms)
{
	uint32_t tend = system_time + ms;
	while(system_time != tend){
		__WFE ();
	}
}

void port_config()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;		// enable clock for portB
	
	// configure portB output for LED
	GPIOB->MODER |= 1<<(LED_PIN*2);				// PB9 - push-pull output
	//GPIOB->MODER |= 2<<(LED_PIN*2);				// PB9 - alternate mode 
	//GPIOB->AFR[1] |= 2<<4;
	GPIOB->OSPEEDR |= 3<<(LED_PIN*2);			// PB9 - max speed
	
	/* UART2 pins config
	 * PD5 - TX
	 * PD6 - RX
	 */	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;		// enable clock for portD
	GPIOD->MODER |= (2<<(5*2)) + (2<<(6*2));	// alternate mode for PD5 and PD6
	GPIOD->AFR[0] |= (7<<20) + (7<<24);			// alternate function 7 PD5 and PD6
	GPIOD->OSPEEDR |= 3<<(5*2);					// PD5 - max speed
	
	/* USB device pins config
	 * PA9 - USB_VBUS
	 * PA11 - USB_DM
	 * PA12 - USB_DP
	 */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;			// enable clock for portA
	GPIOA->MODER |= (2<<(11*2)) + (2<<(12*2));		// alternate mode for PA11 and PA12
	GPIOA->AFR[1] |= (10<<12) + (10<<16);			// alternate function 10 PA11 and PA12
	GPIOA->OSPEEDR |= (3<<(11*2)) + (3<<(12*2));	// max speed
}

void clock_config()
{
	/* Enable HSE */
	RCC->CR |= (1<<16);
	while (0==(RCC->CR & (1<<17))) {};
	
	/* SYSCLOCK from HSE */
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSE;
	while( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE ) {};
	
	/* SYSCLOCK from PLL
	 * SYSCLK = 144 MHz
	 * HCLK = 144 MHz
	 * PCLK1 = 144/4 = 36 MHz
	 * PCLK1 = 144/2 = 72 MHz
	 * PLLUSB = 288/6 = 48 MHz
	 */
	// PLL setting
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM + RCC_PLLCFGR_PLLN + RCC_PLLCFGR_PLLP);
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;			// HCE is source for PLL
	RCC->PLLCFGR |= 25;							// M = 25
	RCC->PLLCFGR |= (288<<6);					// N = 288
	RCC->PLLCFGR |= (6<<24);					// Q = 6
	RCC->CR |= RCC_CR_PLLON;					// set PLL on
	while(0 == (RCC->CR & RCC_CR_PLLRDY)) {}; 	// wait for pll ready
	
	/* setting for flash
	 * LATENCY = 5 for 144 MHz
	 * and enable prefetch buffer
	 */
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_5WS;	// set 5 WS
	FLASH->ACR |= FLASH_ACR_PRFTEN;			// enable prefetch buffer	
	
	// APB1,2 prescallers
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4 + RCC_CFGR_PPRE2_DIV2;
	
	// switch SYSCLOCK to PLL
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL ) {}; 	
	
	system_time = 0;
	SysTick_Config(SYS_TICKS);
}

#define USB_TOCAL 17
#define USB_TRDT 6

void usb_config()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
/*
	The application must perform the core initialization sequence. If the cable is connected
	during power-up, the current mode of operation bit in the OTG_FS_GINTSTS (CMOD bit in
	OTG_FS_GINTSTS) reflects the mode. The OTG_FS controller enters host mode when an
	“A” plug is connected or device mode when a “B” plug is connected.
	This section explains the initialization of the OTG_FS controller after power-on. The
	application must follow the initialization sequence irrespective of host or device mode
	operation. All core global registers are initialized according to the core’s configuration:

	1.Program the following fields in the OTG_FS_GAHBCFG register:
	– Global interrupt mask bit GINTMSK = 1
	– RxFIFO non-empty (RXFLVL bit in OTG_FS_GINTSTS)
	– Periodic TxFIFO empty level
	2.Program the following fields in the OTG_FS_GUSBCFG register:
	– HNP capable bit
	– SRP capable bit
	– FS timeout calibration field
	– USB turnaround time field
	3.The software must unmask the following bits in the OTG_FS_GINTMSK register:
	-OTG interrupt mask
	-Mode mismatch interrupt mask
	4.The software can read the CMOD bit in OTG_FS_GINTSTS to determine whether the
	OTG_FS controller is operating in host or device mode.
*/	
	
	USB_OTG_FS->GAHBCFG = USB_OTG_GAHBCFG_GINT;		// Global interrupt mask bit
	USB_OTG_FS->GUSBCFG &= ~(USB_OTG_GUSBCFG_TOCAL + USB_OTG_GUSBCFG_TRDT);
	USB_OTG_FS->GUSBCFG |= USB_OTG_GUSBCFG_FDMOD;
	USB_OTG_FS->GUSBCFG |= (USB_TRDT<<10) + USB_TOCAL;
	USB_OTG_FS->GINTMSK |= USB_OTG_GINTMSK_MMISM + USB_OTG_GINTMSK_OTGINT;
/*	
	Device initialization
	The application must perform the following steps to initialize the core as a device on power-
	up or after a mode change from host to device.

	1.Program the following fields in the OTG_FS_DCFG register:
	– Device speed
	– Non-zero-length status OUT handshake
	2.Program the OTG_FS_GINTMSK register to unmask the following interrupts:
	– USB reset
	– Enumeration done
	– Early suspend
	– USB suspend
	– SOF
	3. Program the VBUSBSEN bit in the OTG_FS_GCCFG register to enable V BUS sensing
	in “B” device mode and supply the 5 volts across the pull-up resistor on the DP line.
	4. Wait for the USBRST interrupt in OTG_FS_GINTSTS. It indicates that a reset has been
	detected on the USB that lasts for about 10 ms on receiving this interrupt.
	Wait for the ENUMDNE interrupt in OTG_FS_GINTSTS. This interrupt indicates the end of
	reset on the USB. On receiving this interrupt, the application must read the OTG_FS_DSTS
	register to determine the enumeration speed and perform the steps listed in Endpoint
	initialization on enumeration completion on page 1353.
	At this point, the device is ready to accept SOF packets and perform control transfers on
	control endpoint 0.
*/	
	USB_OTG_FS_DEVICE->DCFG |= 0x03;
	USB_OTG_FS->GINTMSK |= USB_OTG_GINTMSK_USBRST+USB_OTG_GINTMSK_ENUMDNEM +
						USB_OTG_GINTMSK_ESUSPM+USB_OTG_GINTMSK_USBSUSPM+
						USB_OTG_GINTMSK_SOFM;
	USB_OTG_FS->GCCFG = (1<<21) + (1<<16);
}
