#include <_types/_uint16_t.h>
#include "CSD203.h"
#include "Arduino.h"
#include "Wire.h"
void CSD203::begin()
{
  uint16_t Data=0,ADDR=0;
	Data|=(CSD203_CFG->RST)<<15;
	Data|=(CSD203_CFG->Average)<<9;
	Data|=(CSD203_CFG->VBUS_Conv_Time)<<5;
	Data|=(CSD203_CFG->VShunt_Conv_Time)<<2;
	Data|=CSD203_CFG->Mode;
	ADDR=(CSD203_CFG->DeviceADDR);
  //使用Arduino 自带的IIC库
  //设定器件地址
  Wire.beginTransmission(ADDR);
  //写寄存器地址
	Wire.write(CONFIGURATION);
  Wire.write(Data);
  Wire.endTransmission();
	//printf("Config Register :%x\r\n",Data);
	Data=CalParam/((CSD203_CFG->CurrentLSB)*(CSD203_CFG->Rshunt));
  Wire.write(Data);
}
uint16_t CSD203::GetCurrent()
{
  uint16_t Current;

  return Current;
}
uint16_t CSD203::GetPower()
{
  uint16_t Power;
  
  return Power;
}
uint16_t CSD203::GetVoltage()
{
  uint16_t Voltage;
  return Voltage;
}
void IIC_DUT_W(u_int8_t DUT_ADDR,u_int8_t REG,u_int16_t Data)
{
    
}
