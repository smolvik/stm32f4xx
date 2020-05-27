/**********************************************************************
 * 
 * stm32 debuging
 * 
 *********************************************************************/
#include "stm32f4xx.h"
#include "xprintf.h"

#define LED_PIN 9

extern void sleep(uint32_t ms);
extern void port_config();
extern void clock_config();
extern void set_ram_vt();
extern void uart_config();
extern void uart_putch(unsigned char b);

int main()
{	
	int i = 0;
		
	set_ram_vt();
	clock_config();
	port_config();
	uart_config();
	
	xdev_out(uart_putch);
		
	xprintf("hello\r\n");	
	
	while(1)
	{
		//__WFE ();
		sleep(1000);
		
		xprintf("hello %d\r\n", i++);	
	}
}
