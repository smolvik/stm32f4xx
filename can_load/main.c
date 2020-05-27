/**********************************************************************
 * 
 * stm32 debuging
 * 
 *********************************************************************/
#include "stm32f4xx.h"
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

int main()
{	
	int i = 0;
	char buf[16];

	clock_config();
	port_config();
	can_config();

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

	}
}
