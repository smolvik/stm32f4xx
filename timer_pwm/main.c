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
extern void timer_config();
extern void dds_config();

__attribute__ ((section(".main_sec")))
int main()
{
	set_ram_vt();
	clock_config();
	port_config();
	timer_config();
	dds_config();
	
	while(1)
	{										
		__WFE ();
	}
}
