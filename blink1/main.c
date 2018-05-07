/**********************************************************************
 * 
 * stm32 debuging
 * 
 *********************************************************************/
#include "stm32f4xx.h"
#define LED_PIN 9

volatile int counter;

int main()
{
	counter = 0;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;		// enable clock for portB
	
	// configure portB
	GPIOB->MODER |= 1<<(LED_PIN*2);				// PB9 - push-pull output
	GPIOB->OSPEEDR |= 3<<(LED_PIN*2);			// PB9 - max speed
	
	while(1)
	{										
		while(100000 != ++counter){};
		counter = 0;
		GPIOB->ODR ^= (1<<LED_PIN);
	}
}
