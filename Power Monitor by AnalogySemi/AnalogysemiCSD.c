#include "AnalogysemiCSD.h"
/*Initial CSD203*/
void CSD203_Init(CSD_CONFIG *CSD203_CFG)
{
	uint16_t Data=0,ADDR=0;
	Data|=(CSD203_CFG->RST)<<15;
	Data|=(CSD203_CFG->Average)<<9;
	Data|=(CSD203_CFG->VBUS_Conv_Time)<<5;
	Data|=(CSD203_CFG->VShunt_Conv_Time)<<2;
	Data|=CSD203_CFG->Mode;
	ADDR=(CSD203_CFG->DeviceADDR);
	IIC_DUT_W(ADDR,CONFIGURATION,Data);
	printf("%x\r\n",Data);
}
/*Read Vbus*/
uint16_t CSD203_ReadVbus(CSD_CONFIG *CSD203_CFG)
{
	uint16_t Data=0,ADDR=0;
	ADDR=(CSD203_CFG->DeviceADDR);
	Data=IIC_DUT_R(ADDR,BUS_VOLTAGE);
	return Data;
}
/*Read Rshunt*/
uint16_t CSD203_ReadRshunt(CSD_CONFIG *CSD203_CFG)
{
	uint16_t Data=0,ADDR=0;
	ADDR=(CSD203_CFG->DeviceADDR);
	Data=IIC_DUT_R(ADDR,SHUNT_VOLTAGE);
	return Data;
}
/*Read Power*/
uint16_t CSD203_ReadPower(CSD_CONFIG *CSD203_CFG)
{
	uint16_t Data=0,ADDR=0;
	ADDR=(CSD203_CFG->DeviceADDR);
	Data=IIC_DUT_R(ADDR,POWER);
	return Data;
}
/*Read Current*/
uint16_t CSD203_ReadCurrent(CSD_CONFIG *CSD203_CFG)
{
	uint16_t Data=0,ADDR=0;
	ADDR=(CSD203_CFG->DeviceADDR);
	Data=IIC_DUT_R(ADDR,CURRENT);
	return Data;
}

