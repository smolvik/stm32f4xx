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

int main()
{	
	int i = 0;
	char buf[16];
			
	set_ram_vt();
	clock_config();
	port_config();
	uart_config();
	
	xdev_out(uart_putch);
		
	xprintf("hello\r\n");	
	
	while(1)
	{
		sleep(3000);
	
		int nb = 0;
		if(nb = uart_read(buf, 16)){
			uart_send(buf, nb);
		}		
	}
}
