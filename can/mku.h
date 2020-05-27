#ifndef _MKU_H
#define _MKU_H

#define MK1_ADDR 0x01
#define MK2_ADDR 0x02
#define MK3_ADDR 0x03

#define MKU1_ADDR 0x04
#define MKU2_ADDR 0x05
#define MKU3_ADDR 0x06
#define MKU4_ADDR 0x07

#define MY_MKU_ADDR MKU1_ADDR

typedef struct {
	union {
		struct{
			uint8_t pack_id:8;
			uint8_t to:8;
			uint8_t from:8;
			uint8_t pri:5;
			uint8_t res:3;
		}f;
		uint32_t w;
	} id;
	
	uint8_t dl;
	uint8_t data[8];
} STR_CAN_PACK;

/* Коды пакетов */
typedef enum {
	KMD_UNZ = 0x60,
	KMD_BS = 0x61,
	KMD_BS_P = 0x62,
	KMD_BS_OTM = 0x63,
	KMD_ARK = 0x64,
	KMD_C = 0x6D,
	KMD_SH = 0x6E,
	KMD_UPR_M = 0x6F,
	KMD_PRM1 = 0x65,
	KMD_PRM2 = 0x66,
	KMD_PRM3 = 0x67,
	KMD_PRM4 = 0x68,
	KMD_PRM5 = 0x69,
	PRM_AB_1 = 0x70,
	PRM_AB_2 = 0x71,
	PRM_AB_3 = 0x72,
	PRM_AB_4 = 0x73,
	PRM_AB_5 = 0x74
} ENM_PACK_ID;

/* Статус выполненной команды */
typedef struct {
	uint8_t id;
	uint8_t par;
	uint8_t status;
} STR_MKU_STATUS;

/* Оперативные параметры АБ */
/* Параметры пакета Параметры АБ ч. 1 */
typedef struct {
		uint8_t ab_mode:3;
		uint8_t comm_id:5;
		uint8_t dis_dchT:1;
		uint8_t dis_dchU:1;
		uint8_t dis_chT:1;
		uint8_t dis_chU:1;
		uint8_t res1:4;
		uint8_t set_Ich_AB:3;
		uint8_t res2:5;
} STR_MKU_AB1;

/* Параметры пакета «Параметры АБ ч. 2» */
typedef struct {
	uint16_t voltAB;
	int16_t voltABmin;
	int16_t voltABmax;
	int8_t tempABmin;
	int8_t tempABmax;
} STR_MKU_AB2;

/* Дополнительные параметры АБ */
/* Параметры пакета «Параметры АБ ч. 3» */
typedef struct {
	uint16_t voltAB;
	int16_t voltAK1;
	int16_t voltAK2;
	int16_t voltAK3;
} STR_MKU_AB3;

/* Параметры пакета «Параметры АБ ч. 4» */
typedef struct {
	int16_t voltAK4;
	int16_t voltAK5;
	int16_t voltAK6;
	int16_t voltAK7;
} STR_MKU_AB4;

/* Параметры пакета «Параметры АБ ч. 5» */
typedef struct {
	uint8_t statusBS1:1;
	uint8_t statusBS2:1;
	uint8_t statusBS3:1;
	uint8_t statusBS4:1;
	uint8_t statusBS5:1;
	uint8_t statusBS6:1;
	uint8_t statusBS7:1;
	uint8_t res1:1;
	uint8_t statusBL1:1;
	uint8_t statusBL2:1;
	uint8_t statusBL3:1;
	uint8_t statusBL4:1;
	uint8_t statusBL5:1;
	uint8_t statusBL6:1;
	uint8_t statusBL7:1;
	uint8_t res2:1;
	int8_t tempABavg;
	int8_t tempDT1;
	int8_t tempDT2;
	int8_t tempDT3;
	int8_t tempDT4;
} STR_MKU_AB5;
	
	
	


#endif
