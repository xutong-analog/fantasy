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


/*Calibration Calculation parameter*/
/* This Parameter Gain*10000K*/
#define CalParam        51200
/* ↓ add your shunt here ↓   */
#define CSD_CONFIG_Rs_1mR						1
#define CSD_CONFIG_Rs_2mR						2
#define CSD_CONFIG_Rs_5mR						5
#define CSD_CONFIG_Rs_10mR					10
#define CSD_CONFIG_Rs_20mR					20
#define CSD_CONFIG_Rs_50mR					50
#define CSD_CONFIG_CurrentLsb1mA   	10
#define CSD_CONFIG_CurrentLsb2mA   	20
#define CSD_CONFIG_CurrentLsb5mA   	50
#define CSD_CONFIG_CurrentLsb10mA  	100
#define CSD_CONFIG_CurrentLsb20mA  	200
/*Calibration Calculation parameter*/




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

#define CSD_CONFIG_ADDR_A1_GND_A0_GND 64
#define CSD_CONFIG_ADDR_A1_GND_VS_GND 65
#define CSD_CONFIG_ADDR_A1_GND_SDA_GND 66
#define CSD_CONFIG_ADDR_A1_GND_SCL_GND 67
#define CSD_CONFIG_ADDR_A1_VS_A0_GND 68
#define CSD_CONFIG_ADDR_A1_VS_A0_VS 69
#define CSD_CONFIG_ADDR_A1_VS_A0_SDA 70
#define CSD_CONFIG_ADDR_A1_VS_A0_SCL 71
#define CSD_CONFIG_ADDR_A1_SDA_A0_GND 72
#define CSD_CONFIG_ADDR_A1_SDA_A0_VS 73
#define CSD_CONFIG_ADDR_A1_SDA_A0_SDA 74
#define CSD_CONFIG_ADDR_A1_SDA_A0_SCL 75
#define CSD_CONFIG_ADDR_A1_SCL_A0_GND 76
#define CSD_CONFIG_ADDR_A1_SCL_A0_VS 77
#define CSD_CONFIG_ADDR_A1_SCL_A0_SDA 78
#define CSD_CONFIG_ADDR_A1_SCL_A0_SCL 79
/******************/
/*CSD Alert Option*/
/******************/
/*Vshunt Voltage Over Voltage*/
#define CSD_ALERT_VShunt_OVA_ON 	1
#define CSD_ALERT_VShunt_OVA_OFF 	0
/*Vshunt Voltage Under Voltage*/
#define CSD_ALERT_VShunt_UVA_ON 	1
#define CSD_ALERT_VShunt_UVA_OFF 	0
/*VBus Voltage Over Voltage*/
#define CSD_ALERT_VBUS_OVA_ON 	1
#define CSD_ALERT_VBUS_OVA_OFF 	0
/*VBus Voltage Under Voltage*/
#define CSD_ALERT_VBUS_UVA_ON 	1
#define CSD_ALERT_VBUS_UVA_OFF 	0
/* Power Over Limit */
#define CSD_ALERT_Power_Over_ON 	1
#define CSD_ALERT_Power_Over_OFF 	0
/* ADC Coversion Ready */
#define CSD_ALERT_CoversionReady_ON 	1
#define CSD_ALERT_CoversionReady_OFF 	0
#define CSD_ALERT_CNVR_FLAG_ON 	1
#define CSD_ALERT_CNVR_FLAG_OFF 	0
/*  ALERT Function Flag and Alert latch Work Together */
#define CSD_ALERT_ALERT_FLAG_ON 	1
#define CSD_ALERT_ALERT_FLAG_OFF 	0
#define CSD_ALERT_ALERT_Latch_ON 	1
#define CSD_ALERT_ALERT_Latch_OFF 	0
/*Power over flow */
#define CSD_ALERT_OVF_ON 	1
#define CSD_ALERT_OVF_OFF 	0
/*Alert Pin */
#define CSD_ALERT_APOL_ActiveLow 	1
#define CSD_ALERT_APOL_ActiveHigh 0

/*CSD Basic Configuration struct*/
typedef struct{
	uint8_t DeviceADDR;
	uint8_t RST;
	uint8_t Average;
	uint8_t VBUS_Conv_Time;
	uint8_t VShunt_Conv_Time;
	uint8_t Mode;
	uint16_t CurrentLSB;
	uint16_t Rshunt;
}CSD_CONFIG;
/*CSD Basic Configuration struct*/

/*CSD ALERT Configuration struct*/
typedef struct{
	uint8_t VShunt_OVA;
	uint8_t VShuntUVA;
	uint8_t VBUS_OVA;
	uint8_t VBUS_UVA;
	uint8_t Power_OVER_Limit;
	uint8_t CNVR;
	uint8_t ALERT_FLAG;
	uint8_t CNVR_FLAG;
	uint8_t OVF;
	uint8_t APOL;
	uint8_t ALERT_Latch;
}CSD_ALERT;
/*CSD ALERT Configuration struct*/


/*Initial CSD203 Config*/
void CSD203_Alert(CSD_ALERT *CSD_ALT);
void CSD203_Init(CSD_CONFIG *CSD203_CFG);
/* Read Vbus Voltage*/
uint16_t CSD203_ReadVbus(CSD_CONFIG *CSD203_CFG);
/*Read Rshunt*/
uint16_t CSD203_ReadRshunt(CSD_CONFIG *CSD203_CFG);
/*Read Power*/
uint16_t CSD203_ReadPower(CSD_CONFIG *CSD203_CFG);
/*Read Current*/
uint16_t CSD203_ReadCurrent(CSD_CONFIG *CSD203_CFG);

#endif 

