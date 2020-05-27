#include "stm32f4xx.h"
#include "mku.h"


void can_config()
{
	// enable clock on can1
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
	
	/*The software initialization can be done while the hardware is in Initialization mode. To enter
	this mode the software sets the INRQ bit in the CAN_MCR register and waits until the
	hardware has confirmed the request by setting the INAK bit in the CAN_MSR register.
	*/
	CAN1->MCR = 0;
	while(CAN1->MSR & CAN_MSR_SLAK) {};
	
	CAN1->MCR = CAN_MCR_INRQ;
	while(0 == (CAN1->MSR & CAN_MSR_INAK) ) {};
	
	// tbr = tsync + tbs1 +tbs2 = tq + 3*tq + 2*tq = 6*tq
	CAN1->BTR = (0<<24) + // SJMP = trjw/tq-1 = 1-1 = 0
				(3<<16) + // TS1 = tbs1/tq-1 = 4-1 = 3
				(2<<20) + // TS2 = tbs2/tq-1 = 3-1 = 2
				49; // BRP = tq/tpclk1 - 1 = Fpclk1/(8*Fbr) - 1 = 40/(8*0.1) - 1 = 49
	
	/*
	 * Filtering bank 0 setting
	 */
	CAN1->FMR |= (1<<0);
	CAN1->FS1R = (1<<0);
	CAN1->sFilterRegister[0].FR1 = MKU1_ADDR<<(8+3);	// identifier
	CAN1->sFilterRegister[0].FR2 = 0xff<<(8+3);			// mask
	CAN1->FA1R = (1<<0);
	CAN1->FMR &= ~(1<<0);
	
	/* To leave Initialization mode, the software clears the INQR bit. bxCAN has left Initialization
	mode once the INAK bit has been cleared by hardware.
	*/
	CAN1->MCR = CAN_MCR_ABOM;
	while(CAN1->MSR & CAN_MSR_INAK) {};
}

void can_send_pack(uint32_t id, uint8_t dlc, uint8_t *data)
{
	/*In order to transmit a message, the application must select one empty transmit mailbox, set
	up the identifier, the data length code (DLC) and the data before requesting the transmission
	by setting the corresponding TXRQ bit in the CAN_TIxR register. There are three TX Mailboxes.
	*/
	CAN1->sTxMailBox[0].TDTR = dlc & 0x0f;	// sel DLC
	uint32_t w[2];
	uint8_t *pb = (uint8_t*)w;
	while(dlc--) *pb++ = *data++;
	CAN1->sTxMailBox[0].TDLR = w[0];
	CAN1->sTxMailBox[0].TDHR = w[1];
	
	CAN1->sTxMailBox[0].TIR = (id<<3) + CAN_TI0R_TXRQ + CAN_TI0R_IDE;
	
	/*The hardware
	indicates a successful transmission by setting the RQCP and TXOK bits in the CAN_TSR
	register. If the transmission fails, the cause is indicated by the ALST bit in the CAN_TSR register in
	case of an Arbitration Lost, and/or the TERR bit, in case of transmission error detection.
	*/
	while(0 == (CAN1->TSR & (CAN_TSR_RQCP0+CAN_TSR_TERR0) ) ) {};
	if(CAN1->TSR & CAN_TSR_TERR0) {
		uint32_t dbg = CAN1->ESR;
		dbg = 0;
	}
}

int can_read_pack(uint32_t *id, uint8_t *data)
{
	/*
	When a message has been received, it is available to the software in the FIFO output
	mailbox. Once the software has handled the message (e.g. read it) the software must
	release the FIFO output mailbox by means of the RFOM bit in the CAN_RFR register to
	make the next incoming message available.

	Starting from the empty state, the first valid message received is stored in the FIFO which
	becomes pending_1. The hardware signals the event setting the FMP[1:0] bits in the
	CAN_RFR register to the value 01b. The message is available in the FIFO output mailbox.
	The software reads out the mailbox content and releases it by setting the RFOM bit in the
	CAN_RFR register. The FIFO becomes empty again. If a new valid message has been
	received in the meantime, the FIFO stays in pending_1 state and the new message is
	available in the output mailbox.
	*/
	if(CAN1->RF0R & 0x03) {
		*id = 0x1fffffff & (CAN1->sFIFOMailBox[0].RIR >> 3);
		int dl = 0x0f & CAN1->sFIFOMailBox[0].RDTR;		
		int i;
		uint32_t w[2];
		uint8_t *pb = (uint8_t*)w;
		w[0] = CAN1->sFIFOMailBox[0].RDLR;
		w[1] = CAN1->sFIFOMailBox[0].RDHR;
		CAN1->RF0R |= CAN_RF0R_RFOM0; // release FIFO0
		
		if(dl<=8) {
			for(i=0; i < dl; i++) *data++ = *pb++;
			return dl;
		}
	}
	return 0;
}
