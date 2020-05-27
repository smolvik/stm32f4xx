#include "stm32f4xx.h"
#include "mku.h"

static inline void dbg_prn(uint8_t *p)
{
	uint8_t c;
	while(c = *p++) ITM_SendChar(c);
}

extern void can_send_pack(uint32_t id, uint8_t dlc, uint8_t *data);
extern int can_read_pack(uint32_t *id, uint8_t *data);

STR_CAN_PACK rec_pack;

void mku_send_pack(STR_CAN_PACK *p)
{
	can_send_pack(p->id.w, p->dl, p->data);
}

void mku_send_status(int addr)
{
	STR_CAN_PACK tstp;
	tstp.id.f.pri = 0x01;
	tstp.id.f.from = addr;
	tstp.id.f.to = rec_pack.id.f.from;
	tstp.id.f.pack_id = KMD_C;
	tstp.dl = 3;
	tstp.data[0] = 0x01; //rec_pack.id.f.pack_id;
	tstp.data[1] = 0x02; //0x00;
	tstp.data[2] = 0x03; //0x00;

	can_send_pack(tstp.id.w, tstp.dl, tstp.data);
}

void mku_send_AB1(int addr)
{
	STR_CAN_PACK tstp;
	tstp.id.f.pri = 0x01;
	tstp.id.f.from = addr;
	tstp.id.f.to = rec_pack.id.f.from;
	tstp.id.f.pack_id = PRM_AB_1;
	
	tstp.dl = sizeof(STR_MKU_AB1);
	STR_MKU_AB1 *pab1 = (STR_MKU_AB1*)tstp.data;
	pab1->ab_mode = 0x5;
	pab1->comm_id = 0xf;
	pab1->dis_chT = 1;
	pab1->dis_chU = 0;
	pab1->dis_dchT = 1;
	pab1->dis_dchU = 0;
	pab1->set_Ich_AB = 3;

	can_send_pack(tstp.id.w, tstp.dl, tstp.data);
}

void mku_send_AB2(int addr)
{
	STR_CAN_PACK tstp;
	tstp.id.f.pri = 0x01;
	tstp.id.f.from = addr;
	tstp.id.f.to = rec_pack.id.f.from;
	tstp.id.f.pack_id = PRM_AB_2;
	
	tstp.dl = sizeof(STR_MKU_AB2);
	STR_MKU_AB2 *pab = (STR_MKU_AB2*)tstp.data;
	pab->voltAB = 0x1;
	pab->voltABmin = 0x2;
	pab->voltABmax = 0x3;
	pab->tempABmin = 0x4;
	pab->tempABmax = 0x5;

	can_send_pack(tstp.id.w, tstp.dl, tstp.data);
}

void mku_send_AB3(int addr)
{
	STR_CAN_PACK tstp;
	tstp.id.f.pri = 0x01;
	tstp.id.f.from = addr;
	tstp.id.f.to = rec_pack.id.f.from;
	tstp.id.f.pack_id = PRM_AB_3;
	
	tstp.dl = sizeof(STR_MKU_AB3);
	STR_MKU_AB3 *pab = (STR_MKU_AB3*)tstp.data;
	pab->voltAB = 0x1;
	pab->voltAK1 = 0x2;
	pab->voltAK2 = 0x3;
	pab->voltAK3 = 0x4;

	can_send_pack(tstp.id.w, tstp.dl, tstp.data);
}

void mku_send_AB4(int addr)
{
	STR_CAN_PACK tstp;
	tstp.id.f.pri = 0x01;
	tstp.id.f.from = addr;
	tstp.id.f.to = rec_pack.id.f.from;
	tstp.id.f.pack_id = PRM_AB_4;
	
	tstp.dl = sizeof(STR_MKU_AB4);
	STR_MKU_AB4 *pab = (STR_MKU_AB4*)tstp.data;
	pab->voltAK4 = 0x1;
	pab->voltAK5 = 0x2;
	pab->voltAK6 = 0x3;
	pab->voltAK7 = 0x4;

	can_send_pack(tstp.id.w, tstp.dl, tstp.data);
}

void mku_send_AB5(int addr)
{
	STR_CAN_PACK tstp;
	tstp.id.f.pri = 0x01;
	tstp.id.f.from = addr;
	tstp.id.f.to = rec_pack.id.f.from;
	tstp.id.f.pack_id = PRM_AB_5;
	
	tstp.dl = sizeof(STR_MKU_AB5);
	STR_MKU_AB5 *pab = (STR_MKU_AB5*)tstp.data;
	pab->statusBS1 = 1;
	pab->statusBS2 = 0;
	pab->statusBS3 = 1;
	pab->statusBS4 = 0;
	pab->statusBS5 = 1;
	pab->statusBS6 = 0;
	pab->statusBL1 = 1;
	pab->statusBL2 = 0;
	pab->statusBL3 = 1;
	pab->statusBL4 = 0;
	pab->statusBL5 = 1;
	pab->statusBL6 = 0;
	pab->statusBL7 = 1;
	pab->tempABavg = 0x25;
	pab->tempDT1 = 0x28;
	pab->tempDT2 = 0x29;
	pab->tempDT3 = 0x30;
	pab->tempDT4 = 0x31;

	can_send_pack(tstp.id.w, tstp.dl, tstp.data);
}

int mku_rec_pack()
{
	if(rec_pack.dl = can_read_pack(&rec_pack.id.w, rec_pack.data))
	{
		int i = 0;
		int addr = rec_pack.id.f.to;
		//if( (addr == MKU1_ADDR) || (addr == MKU2_ADDR) || (addr == MKU3_ADDR) || (addr == MKU4_ADDR))
		if((addr == MKU2_ADDR) || (addr == MKU4_ADDR))
		{
			switch(rec_pack.id.f.pack_id) {
				case KMD_PRM1:
				mku_send_AB1(addr);
				break;
				
				case KMD_PRM2:
				mku_send_AB2(addr);
				break;
				
				case KMD_PRM3:
				mku_send_AB3(addr);
				break;
				
				case KMD_PRM4:
				mku_send_AB4(addr);
				break;
				
				case KMD_PRM5:
				mku_send_AB5(addr);
				break;
				
				default:
				mku_send_status(addr);
				break;
			}
		}

		if(rec_pack.id.f.to == MKU4_ADDR) {
			dbg_prn("MKU4\n");
		}
		else if(rec_pack.id.f.to == MKU3_ADDR) {
			dbg_prn("MKU3\n");
		}
		else if(rec_pack.id.f.to == MKU2_ADDR) {
			dbg_prn("MKU2\n");
		}		
		else if(rec_pack.id.f.to == MKU1_ADDR) {
			dbg_prn("MKU1\n");
		}
		
		return 1;
	}
	
	return 0;
}
