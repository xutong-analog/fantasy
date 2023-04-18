#include <sys/_stdint.h>
  //#include <_types/_uint16_t.h>
  #include "CSD203.h"
  #include <Arduino.h>

  //#include <TwoWire.h>
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
  uint16_t CSD203::IIC_DUT_R(uint8_t DUT_ADDR,uint8_t REG)
  {
    uint16_t len=2,i=0,Datas;
    uint8_t  Data[3];
    Wire.beginTransmission(DUT_ADDR);
    //写寄存器地址
    Wire.write(REG);

   if (Wire.endTransmission(false) == 0 &&Wire.requestFrom(DUT_ADDR, (uint8_t)len)) 
   {
      while (Wire.available()) 
        Data[i++] = Wire.read();
    }
    Datas=Data[0];
    Datas<<=8;
    Datas|=Data[1];
    Wire.endTransmission();
    return Datas;
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
