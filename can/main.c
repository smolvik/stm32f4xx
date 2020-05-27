/**********************************************************************
 * 
 * stm32 debuging
 * 
 *********************************************************************/
#include "stm32f4xx.h"
#include "xprintf.h"
#include "uart.h"
#include "mku.h"

#define LED_PIN 9

extern void sleep(uint32_t ms);
extern void port_config();
extern void clock_config();
extern void set_ram_vt();
extern void uart_config();
extern void can_config();
extern void can_send_pack(uint32_t id, uint8_t dlc, uint8_t *data);
extern int can_read_pack(uint32_t *id, uint8_t *data);
extern void mku_send_pack(STR_CAN_PACK *p);
extern int mku_rec_pack();

/*
void mku_send_pack(STR_CAN_PACK *p)
{
	can_send_pack(p->id.w, p->dl, p->data);
}
*/

int main()
{	
	int i = 0;
	char buf[16];
			
	set_ram_vt();
	clock_config();
	port_config();
	//uart_config();
	can_config();
	
	//xdev_out(uart_putch);
		
	//xprintf("hello\r\n");	
	int lcnt = 0;
	while(1)
	{
		//GPIOB->ODR ^= (1<<LED_PIN);
		//sleep(1000);
		
		if(mku_rec_pack()) {
			GPIOB->ODR |= (1<<LED_PIN);
			lcnt = 100000;
		}
		
		if(0 == --lcnt) GPIOB->ODR &= ~(1<<LED_PIN);
		
		
		/*
		STR_CAN_PACK pack;
		pack.id.f.pack_id = 0x6D;
		pack.id.f.from = MKU1_ADDR;
		pack.id.f.to = MK1_ADDR;
		pack.id.f.pri = 0x01;
		pack.dl = 3;
		pack.data[0] = 0x01;
		pack.data[1] = 0x02;
		pack.data[2] = 0x03;
		pack.data[3] = 0x04;
		pack.data[4] = 0x05;
		pack.data[5] = 0x06;
		pack.data[6] = 0x07;
		pack.data[7] = 0x08;
		
		mku_send_pack(&pack);
		*/
		/*
		STR_CAN_PACK rx_pack;
		if(rx_pack.dl = can_read_pack(&rx_pack.id.w, rx_pack.data))
		{
			int i = 0;
		}
		*/
	/*
		int nb = 0;
		if(nb = uart_read(buf, 16)){
			uart_send(buf, nb);
		}		
		*/
		
	}
}
