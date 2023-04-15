//#include <_types/_uint16_t.h>
#include "CSD203.h"
#include "Arduino.h"
#include "Wire.h"
void CSD203::begin(CSD_CONFIG *CSD203_CFG)
{
  uint16_t Data=0,ADDR=0;
	Data|=(CSD203_CFG->RST)<<15;
	Data|=(CSD203_CFG->Average)<<9;
	Data|=(CSD203_CFG->VBUS_Conv_Time)<<5;
	Data|=(CSD203_CFG->VShunt_Conv_Time)<<2;
	Data|=CSD203_CFG->Mode;
	ADDR=(CSD203_CFG->DeviceADDR);
	IIC_DUT_W(ADDR,CONFIGURATION,Data);
	Data=CalParam/((CSD203_CFG->CurrentLSB)*(CSD203_CFG->Rshunt));
	IIC_DUT_W(ADDR,CALIBRATION,Data);
}
void CSD203::IIC_DUT_W(u_int8_t DUT_ADDR,u_int8_t REG,u_int16_t Data)
{
  Wire.beginTransmission(DUT_ADDR);
  //写寄存器地址
	Wire.write(CONFIGURATION);
  Wire.write(Data);
  Wire.endTransmission();
}
uint16_t CSD203::IIC_DUT_R(u_int8_t DUT_ADDR,u_int8_t REG)
{
  uint16_t Data;
  Wire.beginTransmission(DUT_ADDR);
  //写寄存器地址
	Wire.write(REG);
  //结束传输
  Wire.endTransmission();

  Wire.beginTransmission(DUT_ADDR);
  //从这个地址获取两个Byte的数据
  Wire.requestFrom(DUT_ADDR,2);
  if(Wire.available())
  {
    Data=Wire.read();
  }
  Wire.endTransmission();
  return Data;
}
/*Read Vbus*/
uint16_t CSD203::CSD203_ReadVbus(CSD_CONFIG *CSD203_CFG)
{
	uint16_t Data=0,ADDR=0;
	ADDR=(CSD203_CFG->DeviceADDR);
	Data=IIC_DUT_R(ADDR,BUS_VOLTAGE);
	return Data;
}
/*Read Rshunt*/
uint16_t CSD203::CSD203_ReadRshunt(CSD_CONFIG *CSD203_CFG)
{
	uint16_t Data=0,ADDR=0;
	ADDR=(CSD203_CFG->DeviceADDR);
	Data=IIC_DUT_R(ADDR,SHUNT_VOLTAGE);
	return Data;
}
/*Read Power*/
uint16_t CSD203::CSD203_ReadPower(CSD_CONFIG *CSD203_CFG)
{
	uint16_t Data=0,ADDR=0;
	ADDR=(CSD203_CFG->DeviceADDR);
	Data=IIC_DUT_R(ADDR,POWER);
	return Data;
}

uint16_t CSD203::CSD203_ReadCurrent(CSD_CONFIG *CSD203_CFG)
{
	uint16_t Data=0,ADDR=0;
	ADDR=(CSD203_CFG->DeviceADDR);
	Data=IIC_DUT_R(ADDR,CURRENT);
	return Data;
}
