#include "SPI.H"
void HAL_Delay(uint8_t i)
{
		uint8_t j;
		for(j=100;j>0;j--)
			for(;i<100;i++);
}
void SPI_Write(uint16_t addr,uint8_t date)
{
	uint8_t i;
	CS_H;
	SCLK_L;
	MOSI_L;
	HAL_Delay(1);
	CS_L;
	HAL_Delay(1);
	
	//24 bit in total
	//write addr
	
	for(i=0;i<16;i++)
	{
			//if the highhest bit is 1 mosi set high
			SCLK_L;
			HAL_Delay(1);
			if((addr&0x8000)==0x8000)
			{
				MOSI_H;
			}
			else
			{
				MOSI_L;
			}
			HAL_Delay(1);
			SCLK_H;
			HAL_Delay(1);
			
			//move the highhest bit to left
			addr<<=1;
	}
	for(i=0;i<8;i++)
	{
			//if the highhest bit is 1 mosi set high
			SCLK_L;
			HAL_Delay(1);
			if((date&0x80)==0x80)
			{
				MOSI_H;
			}
			else
			{
				MOSI_L;
			}
					//move the highhest bit to left
			HAL_Delay(1);
			SCLK_H;
			HAL_Delay(1);
			date<<=1;
	}
	HAL_Delay(1);
	CS_H;

}
uint8_t SPI_Read(uint16_t addr)
{
	uint8_t i,Data;
	SCLK_L;
	MOSI_L;
	CS_L;
	Data=0x00;
	addr|=0x8000;
	//SPI Write Addr=0x00xx
	//SPI Read	Addr=0x80xx
	for(i=0;i<16;i++)
	{
			//if the highhest bit is 1 mosi set high
			SCLK_L;
			HAL_Delay(1);
			if((addr&0x8000)==0x8000)
			{
				MOSI_H;
			}
			else
			{
				MOSI_L;
			}
			HAL_Delay(1);
			SCLK_H;
			HAL_Delay(1);
			//move the highhest bit to left
			addr<<=1;
	}
	for(i=0;i<8;i++)
	{
			SCLK_L;
			HAL_Delay(1);
			if(MISO==1)
			{
				Data|=0x01;
			}
			else
				Data&=~0x01;
			
			SCLK_H;
		//	HAL_Delay(1);
			Data<<=1;
	}
	HAL_Delay(1);
	CS_H;
	return Data;
}




