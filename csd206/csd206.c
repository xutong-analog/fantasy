#include "main.h"
#include "include.h"
#include "spi.h"
#include "CSD206M.h"
#include "drive_gpio.h"

#define Current_Lsb 31.25

void CSD206M_WriteReg(uint8_t addess,uint16_t reg)
{
    uint8_t pTxData[3];
    uint8_t pRxData[3];
    pTxData[0] = (addess << 2) & 0xfc;
    pTxData[1] = (reg >> 8) & 0xff;
    pTxData[2] = (reg >> 0) & 0xff;
	CS_L;
    SPI_transmitreceive(pTxData,pRxData,3);
	CS_H;
}

uint16_t CSD206M_ReadReg(uint8_t addess)
{
    uint8_t pTxData[3];
    uint8_t pRxData[3];
    uint16_t value;
    pTxData[0] = (addess << 2) | 0x01;
	CS_L;
    SPI_transmitreceive(pTxData,pRxData,3);
	CS_H;
    value = (pRxData[1] << 8) + pRxData[2];
    return value;
}

uint32_t CSD206M_ReadReg20(uint8_t addess)
{
    uint8_t pTxData[5];
    uint8_t pRxData[5];
    uint32_t value;
    pTxData[0] = (addess << 2) | 0x01;
		CS_L;
    SPI_transmitreceive(pTxData,pRxData,5);
		CS_H;
    value = (pRxData[1] << 12) + (pRxData[2] << 4) + ((pRxData[3] >> 4) & 0x0f);
    return value;
}

uint32_t CSD206M_ReadReg24(uint8_t addess)
{
    uint8_t pTxData[5];
    uint8_t pRxData[5];
    uint32_t value;
    pTxData[0] = (addess << 2) | 0x01;
		CS_L;
    SPI_transmitreceive(pTxData,pRxData,5);
		CS_H;
    value = (pRxData[1] << 16) + (pRxData[2] << 8) + pRxData[3];
    return value;
}

void CSD206M_config(CSD206M_Handle *sensor)
{
    //Write sensor Configuration Registers
    CSD206M_WriteReg(CSD206M_CONFIG_REGISTER, sensor->configReg);
    CSD206M_WriteReg(CSD206M_CALIB_REGISTER, sensor->calibrationReg);
    /*CSD206M_WriteReg(CSD206M_ALERT_LIMIT_REGISTER, sensor->alertReg);
    CSD206M_WriteReg(CSD206M_CONFIG_TEMP_REGISTER, sensor->tempConfigReg);
    //CSD206M_WriteReg(CSD206M_CONFIG_TEMP_REGISTER, sensor->diagAlrtRegister);
    CSD206M_WriteReg(CSD206M_SOVL_TH_REGISTER, sensor->vshuntOLThrReg);
    CSD206M_WriteReg(CSD206M_SUVL_TH_REGISTER, sensor->vshuntULThrReg);
    CSD206M_WriteReg(CSD206M_BOVL_TH_REGISTER, sensor->vbusOLThrReg);
    CSD206M_WriteReg(CSD206M_BUVL_TH_REGISTER, sensor->vbusULThrReg);
    CSD206M_WriteReg(CSD206M_TEMP_OL_TH_REGISTER, sensor->tempOLThrReg);
    CSD206M_WriteReg(CSD206M_SMART_ALERT_REGISTER, sensor->smartAlertReg);
    //INA229_writeReg(CSD206M_POWER_OL_TH_REGISTER, sensor->pwrLimitRegister);*/

}


float CSD206M_GetVshout_mV(CSD206M_Handle *sensor)
{
    float value;
		uint32_t reg;
    float lsb,PoN = 1;
    
    reg = CSD206M_ReadReg20(CSD206M_VSHUNT_REGISTER);

    if(reg & 0x80000)
    {
        reg -= 1;
        reg = (~reg) & 0xfffff;  
        PoN = -1; 
    }

    if (sensor->configReg & 0X2000)
    {
        lsb = 5/16;
    }
    else
    {
        lsb = 2.5/16;
    }
    value = (reg * lsb) / 1000 * PoN;
    return value;
    
}

float CSD206M_GetVbus_V(void)
{
    float value;
		uint32_t reg;
    float lsb = 0.125,PoN = 1;

    reg = CSD206M_ReadReg20(CSD206M_VBUS_REGISTER);
    if(reg & 0x80000)
    {
        reg -= 1;
        reg = (~reg) & 0xfffff; 
        PoN = -1; 
    }
    value = (reg * lsb) / 1000 * PoN;
    return value;
}


float CSD206M_GetPOWER(CSD206M_Handle *sensor)
{
    float value;
		uint32_t reg;
    float lsb = 0.078125;
		uint16_t ADCRange,i;
			
		ADCRange = CSD206M_ReadReg(0x00);
		if(ADCRange & 0x2000)	i = 2;
		else
			i = 1;
		
    reg = CSD206M_ReadReg24(CSD206M_POWRE_REGISTER);
    value = lsb * reg * i;
    return value;
}

float CSD206M_GetCURRENT(CSD206M_Handle *sensor)
{
    float value,pos = 1;
	uint32_t reg;
	uint16_t ADCRange,i;
		
	ADCRange = CSD206M_ReadReg(0x00);
	if(ADCRange & 0x2000)	i = 2;
	else
		i = 1;
    
    reg = CSD206M_ReadReg20(CSD206M_CURRENT_REGISTER);
		if(reg & 0x80000)
    {
        reg -= 1;
        reg = (~reg) & 0xfffff; 
				pos = -1;
    }
    value = reg * Current_Lsb * i * pos;
    return value;
}



