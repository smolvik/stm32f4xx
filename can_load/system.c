#include "stm32f4xx.h"

#define FLASH_START 0x8000000
#define NUM_IRQS	98
#define SYS_TICKS	160000
#define LED_PIN 9

extern void USART2_Handler_RAM(void);

volatile uint32_t system_time;

void SysTick_Handler(void)
{
	system_time ++;
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
	
	/* CAN1 pin config
	 * PD0 - RX
	 * PD1 - TX
	 */
	GPIOD->MODER |= (2<<(1*2)) + (2<<(0*2));	// alternate mode for PD0 and PD1 
	GPIOD->AFR[0] |= (9<<4) + (9<<0);			// alternate function 9 PD0 and PD1
	GPIOD->OSPEEDR |= 3<<(1*2);					// PD1 - max speed
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
	 * SYSCLK = 160 MHz
	 * HCLK = 160 MHz
	 * PCLK1 = 160/4 = 40 MHz
	 * PCLK1 = 160/2 = 80 MHz
	 */
	// PLL setting
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM + RCC_PLLCFGR_PLLN + RCC_PLLCFGR_PLLP);
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;			// HCE is source for PLL
	RCC->PLLCFGR |= 25;							// M = 25
	RCC->PLLCFGR |= (320<<6);					// N = 320
	RCC->CR |= RCC_CR_PLLON;					// set PLL on
	while(0 == (RCC->CR & RCC_CR_PLLRDY)) {}; 	// wait for pll ready
	
	/* setting for flash
	 * LATENCY = 5 for 160 MHz
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
