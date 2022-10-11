#ifndef AnalogysemiCSD_H
#define AnalogysemiCSD_H
/* include mcu lib*/
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "IIC.h"

/* CSD203 Regsistor map */
#define CONFIGURATION   0X00
/*Read Only*/
#define SHUNT_VOLTAGE   0X01
#define BUS_VOLTAGE     0X02
#define POWER           0X03
#define CURRENT         0x04
/*Read Only*/
#define CALIBRATION     0x05
#define MASKENABLE      0x06
#define ALERTLIMIT      0x07


/* CSD203 Regsistor Config*/
#define CSD_CONFIG_RST 		 1
#define CSD_CONFIG_UnRST 	 0

#define CSD_CONFIG_Avg1			0
#define CSD_CONFIG_Avg4			1
#define CSD_CONFIG_Avg16		2
#define CSD_CONFIG_Avg64		3
#define CSD_CONFIG_Avg128		4
#define CSD_CONFIG_Avg256		5
#define CSD_CONFIG_Avg512		6
#define CSD_CONFIG_Avg1024	7

#define CSD_CONFIG_VBUS_CT1_1mS 4
#define CSD_CONFIG_VShunt_CT1_1mS 4

#define CSD_CONFIG_ShuntBus_CON 7

#define CSD_CONFIG_ADDR_A1_GND_A2_GND 64
typedef struct{
	uint8_t DeviceADDR;
	uint8_t RST;
	uint8_t Average;
	uint8_t VBUS_Conv_Time;
	uint8_t VShunt_Conv_Time;
	uint8_t Mode;
}CSD_CONFIG;
/*Initial CSD203 Config*/
void CSD203_Init(CSD_CONFIG *CSD203_CFG);
/* Read Vbus Voltage*/
uint16_t CSD203_ReadVbus(CSD_CONFIG *CSD203_CFG);
/*Read Rshunt*/
uint16_t CSD203_ReadRshunt(CSD_CONFIG *CSD203_CFG);
/*Read Power*/
uint16_t CSD203_ReadPower(CSD_CONFIG *CSD203_CFG);
/*Read Current*/
uint16_t CSD203_ReadCurrent(CSD_CONFIG *CSD203_CFG)

#endif 
