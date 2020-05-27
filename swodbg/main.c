/**********************************************************************
 * 
 * stm32 debuging
 * 
 *********************************************************************/
#include "stm32f4xx.h"
#include "xprintf.h"
#include "uart.h"

#define LED_PIN 9

extern void sleep(uint32_t ms);
extern void port_config();
extern void clock_config();
extern void set_ram_vt();
extern void uart_config();

/*
ITM_SendChar(ch) is used to transmit a character over ITM channel 0 from 
the microcontroller system to the debug system.
Only a 8 bit value is transmitted.
*/

int main()
{	
	int i = 0;
	char buf[16];
			
	set_ram_vt();
	clock_config();
	port_config();
	
	xdev_out(ITM_SendChar);
		
	xprintf("hello\r\n");
	
	while(1)
	{
		sleep(1000);
		xprintf("hello\r\n");
	}
}
