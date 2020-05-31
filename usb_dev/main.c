/**********************************************************************
 * 
 * stm32 debuging
 * 
 *********************************************************************/
#include "stm32f407xx.h"
#include "xprintf.h"
#include "uart.h"

#define LED_PIN 9

extern void sleep(uint32_t ms);
extern void port_config();
extern void clock_config();
extern void set_ram_vt();
extern void uart_config();
extern void usb_config();

static inline void dbg_prn(uint8_t *p)
{
	uint8_t c;
	while(c = *p++) ITM_SendChar(c);
}

/*
 * Endpoints:
 * 1. IN bulk
 * 2. IN interrupt
 * 3. OUT bulk
*/

void usb_update()
{
	if(USB_OTG_FS->GINTSTS & USB_OTG_GINTSTS_OTGINT) 
	{
		USB_OTG_FS->GOTGINT = 0;
		
		if(USB_OTG_FS->GINTSTS & USB_OTG_GINTSTS_CMOD){
			dbg_prn("host mode\n");
		}
		else{
			dbg_prn("device mode\n");
		}
	}
	
	if(USB_OTG_FS->GINTSTS & USB_OTG_GINTSTS_USBRST) {
		USB_OTG_FS->GINTSTS |= USB_OTG_GINTSTS_USBRST;
		dbg_prn("USB RST\n");
		
		// Endpoint initialization on USB reset
		/*

		– Program the OTG_FS_TX0FSIZ register (depending on the FIFO number chosen)
		to be able to transmit control IN data. At a minimum, this must be equal to 1 max
		packet size of control endpoint 0.
		Program the following fields in the endpoint-specific registers for control OUT endpoint
		0 to receive a SETUP packet
		–
		STUPCNT = 3 in OTG_FS_DOEPTSIZ0 (to receive up to 3 back-to-back SETUP
		packets)
		At this point, all initialization required to receive SETUP packets is done.
		*/
		
		/*
		Set the NAK bit for all OUT endpoints
		SNAK = 1 in OTG_FS_DOEPCTLx (for all OUT endpoints)
		*/
		USB_OTG_FS_OUT_ENDPOINT[0].DOEPCTL |= (1<<27);
		USB_OTG_FS_OUT_ENDPOINT[1].DOEPCTL |= (1<<27);
		USB_OTG_FS_OUT_ENDPOINT[2].DOEPCTL |= (1<<27);
		USB_OTG_FS_OUT_ENDPOINT[3].DOEPCTL |= (1<<27);
		/*
		Unmask the following interrupt bits
		– INEP0 = 1 in OTG_FS_DAINTMSK (control 0 IN endpoint)
		– OUTEP0 = 1 in OTG_FS_DAINTMSK (control 0 OUT endpoint)
		– STUP = 1 in DOEPMSK
		– XFRC = 1 in DOEPMSK
		– XFRC = 1 in DIEPMSK
		– TOC = 1 in DIEPMSK* 
		 */
		USB_OTG_FS_DEVICE->DAINTMSK |= (1<<16)+(1<<0);
		USB_OTG_FS_DEVICE->DOEPMSK |= (1<<3)+(1<<0);
		USB_OTG_FS_DEVICE->DIEPMSK |= (1<<3)+(1<<0);
		/*
		 Set up the Data FIFO RAM for each of the FIFOs
		–Program the OTG_FS_GRXFSIZ register, to be able to receive control OUT data
		and setup data. If thresholding is not enabled, at a minimum, this must be equal to
		1 max packet size of control endpoint 0 + 2 words (for the status of the control
		OUT data packet) + 10 words (for setup packets).
		 */
		USB_OTG_FS->GRXFSIZ &= 0xffff;
		USB_OTG_FS->GRXFSIZ |= 160;
	}
	
	if(USB_OTG_FS->GINTSTS & USB_OTG_GINTSTS_ENUMDNE) {
		USB_OTG_FS->GINTSTS |= USB_OTG_GINTSTS_ENUMDNE;
		dbg_prn("USB enumeration done\n");
		xprintf( "USBSPD=%x\n", 0x03&((USB_OTG_FS_DEVICE->DSTS)>>1) );

	}	
	

}

int main()
{	
	int i = 0;
	char buf[16];
			
	set_ram_vt();
	clock_config();
	port_config();
	//uart_config();
	usb_config();
	
	xdev_out(ITM_SendChar);
	xprintf("hello\r\n");
	xprintf("%x\r\n", sizeof(USB_OTG_OUTEndpointTypeDef));
	xprintf("%x\r\n", sizeof(USB_OTG_INEndpointTypeDef));
	//dbg_prn("hello\n");
	
	
	while(1)
	{
		//sleep(1000);
		//GPIOB->ODR ^= (1<<LED_PIN);
		//dbg_prn("hello\n");
		
		
		usb_update();
		
		
	/*
		int nb = 0;
		if(nb = uart_read(buf, 16)){
			uart_send(buf, nb);
		}
		*/
	}
}
