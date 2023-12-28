#ifndef __LB2032_H
#define __LB2032_H
#include "stc8h.h"
#include "spi.h"
#define  Interface_Configuration0     0x0000
#define  Interface_Configuration1     0x0001
#define  Device_Configuration     0x0002
#define  Chip_Type     0x0003
#define  Chip_ID_LowByte     0x8004
#define  Chip_ID_HighByte     0x8005
#define  Chip_Version     0x0006
#define  Manufacturer_ID_LowByte     0x000c
#define  Manufacturer_ID_HighByte     0x000d
#define  Register_Update     0x000f
#define  ADC_Configuration     0x0010 //SET ADC CONV RATE  ADC MODE  
#define  False_Alarm_Configuration     0x0011
#define  GPIO_Configuration    0x0012
#define  ADC_MUX_Configuration     0x0013	//ADC CHANNEL CYCLE CH7~CH0 bit=0 ignore bit=1 enable

#define  DAC_Clear_Enable0  0x0018 //DAC Clear enable dac 7 to 0
#define  DAC_Clear_Enable1  0x0019 // DAC Clear enable dac 15 to 8
#define  DAC_Clear_Source0  0x001a
#define  DAC_Clear_Source1     0x001b
#define  ALARMOUTSource0     0x001c
#define  ALARMOUTSource1     0x001d
#define  DAC_Range				0x0015 //SET DACOUT PUT RANGE  ***

#define  ADC_LowByte0     0x8020
#define  ADC_HighByte0     0x8021



#define  DAC_LowByteA0  0x0030
#define  DAC_HighByteA0  0x0031

#define  AlarmStatus0  0x0070
#define  AlarmStatus1  0x0071 //SET Alarm event Trigger Alarm source 
#define  GeneralStatus  0x0072
#define  GPIO  0x007A
#define  ADC_Upper_LowByte16  0x0080
#define  ADC_Upper_HighByte16  0x0081
#define  ADC_Lower_LowByte16  0x0082
#define  ADC_Lower_HighByte16  0x0083
#define  ADC_Upper_LowByte17  0x0084
#define  ADC_Upper_HighByte17  0x0085
#define  ADC_Lower_LowByte17  0x0086
#define  ADC_Lower_HighByte17  0x0087
#define  ADC_Upper_LowByte18  0x0088
#define  ADC_Upper_HighByte18  0x0089
#define  ADC_Lower_LowByte18  0x008a
#define  ADC_Lower_HighByte18  0x008b
#define  ADC_Upper_LowByte19  0x008c
#define  ADC_Upper_HighByte19  0x008d
#define  ADC_Lower_LowByte19  0x008e
#define  ADC_Lower_HighByte19  0x008f
#define  ADC_Upper_LowByte20  0x0090
#define  ADC_Upper_HighByte20  0x0091
#define  ADC_Lower_LowByte20  0x0092
#define  ADC_Lower_HighByte20  0x0093
#define  LT_Upper_LowByte  0x0094
#define  LT_Upper_HighByte  0x0095
#define  LT_Lower_LowByte  0x0096
#define  LT_Lower_HighByte  0x0097
#define  ADC_HySeresis16  0x00A0
#define  ADC_HySeresis17  0x00A1
#define  ADC_HySeresis18  0x00A2
#define  ADC_HySeresis19  0x00A3
#define  ADC_HySeresis20  0x00A4
#define  LT_HySeresis  0x00A5
#define  DAC_Clear0  0x00B0
#define  DAC_Clear1  0x00B1
#define  Power_Enable0  0x00B2		//Power DAC
#define  Power_Enable1  0x00B3		//Power DAC 
#define  Power_Enable2  0x00B4		//Power DAC 
#define  Power_Enable3  0x00B5		//Power DAC 
#define  Power_Enable4	0X00B6		// ADC Power AND  Temp Power
#define  ADC_Trigger  0x00C0
void Dac_Write(uint8_t DAC_CH,uint16_t DAC_Ranges,uint16_t Dac_Value);
void Dac_Clear(uint8_t DAC_CH);
void Dac_Clear_Reset(void);
void SoftReset(void);
uint16_t Adc_Read(uint8_t ADC_CH);
void alarm_event_alarmin(void);
#endif
