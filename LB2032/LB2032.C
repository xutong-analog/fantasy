#include"LB2032.H"
void Dac_Write(uint8_t DAC_CH,uint16_t DAC_Ranges,uint16_t Dac_Value)
{
		// DAC CH 0~15 DAC_Range -5,5,-10,10 
		uint8_t Dac_ValueHigh,Dac_ValueLow,Dac_Part_H,Dac_Part_L;
		if (DAC_CH==0)
		{
			Dac_Part_H=0X00;
			Dac_Part_L=0X01;
		}
		if ((DAC_CH-8)>0)
		{
			Dac_Part_H=0X01<<(DAC_CH%8);
			Dac_Part_L=0X00;
		}
		Dac_Part_H=0X00;
		Dac_Part_L=0X01<<DAC_CH;
		
		if(Dac_Value>4095) 
		//DAC MAX Value Clamp
		{
			Dac_Value=4095;
		}
		Dac_ValueHigh=Dac_Value>>8;
		Dac_ValueLow=Dac_Value&0X00FF;
		
		
		SPI_Write(Power_Enable0,Dac_Part_L); //Power DAC 1 ON / 0 OFF
		SPI_Write(Power_Enable1,Dac_Part_H); //Power DAC 1 ON / 0 OFF
		if (DAC_Ranges>0)
		{
			if(DAC_Ranges==5)
			{
				SPI_Write(DAC_Range,0x77); //Poewer DAC RANGE 0~5V
			}
			else
			{
			SPI_Write(DAC_Range,0x66); //Poewer DAC RANGE 0~10V
			}
		}
		if (DAC_Ranges<0)
		{
			if(DAC_Ranges==-5)
			{
				SPI_Write(DAC_Range,0x55); //Poewer DAC RANGE 0~-5V	
			}	
			else
			{
			SPI_Write(DAC_Range,0x44); //Poewer DAC RANGE 0~-5V
			}
		}
	//	SPI_Write(Power_Enable2,0x03); //Poewer DAC PREF 
		

		SPI_Write(DAC_HighByteA0+DAC_CH*2,Dac_ValueHigh);
		SPI_Write(DAC_LowByteA0+DAC_CH*2,Dac_ValueLow);
		//Write DAC Value
		SPI_Write(Register_Update,0x01);		
}
void Dac_Clear(uint8_t DAC_CH)
{
	uint8_t Dac_Clear_H,Dac_Clear_L;
	if (DAC_CH==0)
	{
		Dac_Clear_H=0X00;
		Dac_Clear_L=0X01;
	}
	if ((DAC_CH-8)>0)
	{
		Dac_Clear_H=0X01<<(DAC_CH%8);
		Dac_Clear_L=0X00;
	}
	Dac_Clear_H=0X00;
	Dac_Clear_L=0X01<<DAC_CH;
	SPI_Write(DAC_Clear0,Dac_Clear_L);
	SPI_Write(DAC_Clear1,Dac_Clear_H);
}
void Dac_Clear_Reset(void)
{
	SPI_Write(DAC_Clear0,0x00);
	SPI_Write(DAC_Clear1,0x00);
}
void SoftReset(void)
{
	SPI_Write(DAC_Clear0,0xB0);
}
uint16_t Adc_Read(uint8_t ADC_CH)
{
		uint8_t Adc_Part_H,Adc_Part_L,Adc_LowByte,Adc_HighByte;
		uint16_t ADC_Value;
		if (ADC_CH==0)
		{
			Adc_Part_H=0X00;
			Adc_Part_L=0X01;
		}
		if ((ADC_CH-8)>0)
		{
			Adc_Part_H=0X01<<(ADC_CH%8);
			Adc_Part_L=0X00;
		}
		Adc_Part_H=0X00;
		Adc_Part_L=0X01<<ADC_CH;
		SPI_Write(Power_Enable4,0x01); 
		// Enable Power Adc Power Ref 
		
		SPI_Write(ADC_MUX_Configuration,0X1F); 
		// Set ADC Channel Mux
		
		SPI_Write(ADC_Configuration,0X00);
		//config adc auto mode
		SPI_Write(ADC_Trigger,0X01);
		//Set this bit to 1 to start the ADC conversion internally.
		HAL_Delay(1);
		Adc_LowByte=SPI_Read(ADC_LowByte0+ADC_CH*2);
		Adc_HighByte=SPI_Read(ADC_HighByte0+ADC_CH*2);
		//Set adc regsiter shift
		//Read Adc Value
		ADC_Value=Adc_HighByte<<8;
		ADC_Value=ADC_Value|Adc_LowByte;

		return	ADC_Value;
}	
void alarm_event_alarmin(void)
{
	SPI_Write(GPIO_Configuration,0x03);
	//Enable EN_ALARMOUT and EN_ALARMIN
	SPI_Write(DAC_Clear_Source1,0X08);
	//selection dac clear source alarmin
	//SPI_Write(AlarmStatus1,0x08);
	//set Alarm alarmin trigger
//	SPI_Write(ALARMOUTSource1,0x08);
	// select alrin as trigger source
	SPI_Write(DAC_Clear_Enable0,0XFF);
	SPI_Write(DAC_Clear_Enable1,0XFF);
	//clear all dac option
}

