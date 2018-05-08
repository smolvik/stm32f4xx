/**********************************************************************
 * 
 * stm32 debuging
 * 
 *********************************************************************/
#include "stm32f4xx.h"

#define LED_PIN 9

extern void sleep(uint32_t ms);
extern void port_config();
extern void clock_config();
extern void set_ram_vt();

__attribute__ ((section(".main_sec")))
int main()
{
	set_ram_vt();
	clock_config();
	port_config();
	
	while(1)
	{										
		sleep(1000);
		GPIOB->ODR ^= (1<<LED_PIN);
	}
}
