#include "stm32f4xx.h"

#define FLASH_START 0x8000000
#define NUM_IRQS	98
#define SYS_TICKS	160000
#define LED_PIN 9

void (* table_interrupt_vector_RAM[NUM_IRQS])(void) __attribute__((aligned (256)));

volatile uint32_t system_time;

void SysTick_Handler_RAM(void)
{
	system_time ++;
}

void TIM4_Handler_RAM(void)
{
	TIM4->SR &= ~TIM_SR_UIF;
	GPIOB->ODR ^= (1<<LED_PIN);
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
	table_interrupt_vector_RAM[46] = TIM4_Handler_RAM;
	
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
	GPIOB->OSPEEDR |= 3<<(LED_PIN*2);			// PB9 - max speed
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

void timer_config()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;	// enable clock on TIM4
	
	// tim clock is 80 MHz
	TIM4->PSC = 8000 - 1; // 10kHz
	TIM4->ARR = 10000;
	TIM4->CCR4 = 500;
	
	TIM4->DIER |= TIM_DIER_UIE;	// enable int by update
	TIM4->CR1 |= TIM_CR1_CEN;	// start timer	
	NVIC_EnableIRQ(TIM4_IRQn);
	
}
