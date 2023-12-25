#ifndef __ADX122_H
#define __ADX122_H
//#include "stm32h7xx_hal.h"
//#include "stm32g0xx_hal.h"
#include "stm32f1xx.h"
#include "bsp_lpspi.h"
//#include "SPI.h"
//#include "systick.h"

#define ADX122_ENABLE           Lpspi_Start()  //PULL DOWM CS START ADC
#define ADX122_DISABLE          Lpspi_Stop()   //PULL UP CS STOP ADC

// Register Value
#define ADX122_SS_START        0X8000    //Start ADC
#define ADX122_NO_EFECT        0X0000    //NO Start ADC

#define ADX122_MUX_AIN0_AIN1   0X0000    //000 = AINP is AIN0 and AINN is AIN1 (default)
#define ADX122_MUX_AIN0_AIN3   0x1000    //001 = AINP is AIN0 and AINN is AIN3
#define ADX122_MUX_AIN1_AIN3   0X2000    //010 = AINP is AIN1 and AINN is AIN3
#define ADX122_MUX_AIN2_AIN3   0X3000    //011 = AINP is AIN2 and AINN is AIN3
#define ADX122_MUX_AIN0        0X4000    //100 = AINP is AIN0 and AINN is GND
#define ADX122_MUX_AIN1        0X5000    //101 = AINP is AIN1 and AINN is GND
#define ADX122_MUX_AIN2        0X6000    //110 = AINP is AIN2 and AINN is GND
#define ADX122_MUX_AIN3        0X7000    //111 = AINP is AIN3 and AINN is GND

#define ADX122_PGA_6144        0X0000    //000 = FSR is ±6.144 V
#define ADX122_PGA_4096        0X0200    //001 = FSR is ±4.096 V
#define ADX122_PGA_2048        0X0400    //010 = FSR is ±2.048 V (default)
#define ADX122_PGA_1024        0X0600    //011 = FSR is ±1.024 V
#define ADX122_PGA_0512        0X0800    //100 = FSR is ±0.512 V
#define ADX122_PGA_0256        0X0A00    //101 = FSR is ±0.256 V

#define ADX122_Continuous_MODE 0X0000    //0->Continuous
#define ADX122_Sigle_SHOT_MODE 0X0100    //1->SIGNEL ADC

#define ADX122_DR_10SPS        0X0000    //000 = 10 SPS
#define ADX122_DR_20SPS        0X0020    //001 = 20 SPS
#define ADX122_DR_40SPS        0X0040    //010 = 40 SPS
#define ADX122_DR_158SPS       0X0060    //011 = 158 SPS
#define ADX122_DR_316SPS       0X0080    //100 = 316 SPS 
#define ADX122_DR_581SPS       0X00A0    //101 = 581 SPS
#define ADX122_DR_1761SPS      0X00C0    //110 = 1761 SPS
#define ADX122_DR_3571SPS      0X00E0    //111 = 3571 SPS

#define ADX122_PUUP_DIS        0X0000    //inside pullup disabled
#define ADX122_PUUP_EN         0x0008    //inside pullup enabled

#define ADX122_NOP_UPDATA      0X0002    //update the Config register
#define ADX122_NOP_UNUPDATA    0X0003    //do not update the Config register

#define ADX122_EN_FILT_50HZ    0x8000    //Enable FILT_50HZ
#define ADX122_EN_FILT_60HZ    0X4000    //Enable FILT_60HZ
#define ADX122_DIS_FILT        0X0000    //Disable FILT

#define ADX122_SDCS_Off        0X0000    //Sensor Current OFF
#define ADX122_SDCS_0_5ua      0X0010    //Sensor Current 0.5ua
#define ADX122_SDCS_2ua        0X0020    //Sensor Current 2ua
#define ADX122_SDCS_10ua       0x0030    //Sensor Current 10ua

#define ADX122_In_Short_Mux    0x0000    //Short input mode control Follow CONFIG REGISTER
#define ADX122_In_Short        0X0004    //Ainp and Ainn are shorted

uint8_t ADX122_Get_ID(void);
void ADX122_Sigle_SHOT_Init();
void ADX122_ADC_Continuous_Init(uint16_t channel,uint16_t PGA,uint16_t SPS,uint16_t FILT,uint16_t SDCS);
float ADX122_Get_ADC_SIGLE_SHOT_Data(uint16_t channel,uint16_t PGA,uint16_t SPS,uint16_t FILT,uint16_t SDCS);
float  ADX122_Get_ADC_Continuous_Data(uint16_t channel,uint16_t PGA,uint16_t SPS,uint16_t FILT,uint16_t SDCS);
#endif






