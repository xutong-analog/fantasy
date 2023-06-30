#include "include.h"
#include "i2c.h"
#include "adx1xx.h"

//adx1xx Device address
uint16_t slaveaddess = 0x90;

/*
Function:       adx1xx_i2c_set_reg
Description:    Adx1xx write reg
Input :         reg ,write register address
                pdata,Data written to register
return:         ret, Register write status
*/
uint16_t adx1xx_i2c_set_reg(uint8_t reg, uint16_t pdata)
{
    uint8_t p[2] = {0};
    p[0] = (pdata >> 8) & 0XFF;
    p[1] = pdata & 0XFF;
    return IIC_WriteByte(slaveaddess,reg,p,2);
}

/*
Function:       adx1xx_i2c_read_reg
Description:    Adx1xx read reg
Input :         reg ,Read register address
                pdata,Read where the data is stored
return:         ret, Register read status
*/
uint16_t adx1xx_i2c_read_reg(uint8_t reg, uint8_t *pdata)
{
    return IIC_ReadByte(slaveaddess,reg,pdata,2);
}

/*
Function:       adx1xx_i2c_initSet
Description:    Adx1xx initialization set
Input :         buff ,ADX1xx reg value 
return:         ret, Register write status
*/
uint16_t adx1xx_i2c_initSet(adx1xx_InitTypeDef *buff)
{
    adx1xx_i2c_set_reg(CONFIG_REG, buff->config);
    adx1xx_i2c_set_reg(LO_THRESH_REG, buff->loThresh);
    adx1xx_i2c_set_reg(HI_THRESH_REG, buff->hiThresh);
}

/*
Function:       adx1xx_init
Description:    Adx1xx initialization
Input :         reg ,ADX1xx reg value
return:         ret, initialization state
*/
uint16_t adx1xx_init(adx1xx_InitTypeDef *reg)
{
    if(reg == NULL) return ERROR;

    I2C_Initializes();
    //I2C_OpenHighspeed();
    return adx1xx_i2c_initSet(reg);
}
uint8_t ADCValue[2];
int main_ADX111()
{
    adx1xx_InitTypeDef regValue;
    regValue.config = MUX_A0_GND | FSR_2_048V | MODE_CONTINUOUS | DR_128SPS | COMP_LAT | COMP_QUE_ONE;
    regValue.hiThresh = 0x8000;
    regValue.loThresh = 0x0000;

    adx1xx_init(&regValue);

    while(1)
    {
        if (ALERT_READ == 0)
        {
            adx1xx_i2c_read_reg(CONVERSION_REG,ADCValue);
        }
        
    }
}
