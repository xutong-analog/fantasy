#include "ADX112.h"
void ADX112_GPIO_Init(void)
{
  //初始化ADX112要用的GPIO
  static GPIO_InitTypeDef  GPIO_InitStruct = {0};
  //使能各个引脚的时钟
  CS_PORT_CLK_ENABLE;
  SCLK_PORT_CLK_ENABLE;
  MISO_PORT_CLK_ENABLE;
  MOSI_PORT_CLK_ENABLE;
  //配置各个引脚 
	
  //CS 引脚
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin = CS_PIN;
  HAL_GPIO_Init(CS_PORT, &GPIO_InitStruct);
  //MOSI 引脚
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin = MOSI_PIN;
  HAL_GPIO_Init(MOSI_PORT, &GPIO_InitStruct);
  //SCLK 引脚
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin = SCLK_PIN;
  HAL_GPIO_Init(SCLK_PORT, &GPIO_InitStruct);
  //MISO 引脚
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin = MISO_PIN;
  HAL_GPIO_Init(MISO_PORT, &GPIO_InitStruct);
  CS_H;
  SCLK_H;
  MOSI_L;

}
//配置ADX112 读写
uint16_t ADX112_Get_ADValue(ADX112_InitTypeDef* Config)
{
	uint16_t data,i,wdata;
	//将结构体指针的参数赋值给wdata
  wdata=(Config->MUX)|(Config->PGA_GAIN)|(Config->DR)|(Config->MODE)
  |(Config->TS_MODE)|(Config->Single_Conversion)|(Config->PULL_UP_DOUT)|(Config->NOP);
	
	//拉低时钟开始传输数据
  CS_L;
  for (i = 0; i < 16; i++)
  {
			SCLK_H;
			data<<=1;
      //如果最高位为1则写1否则写0
			if((wdata&0X8000)==0X8000)
			{
				MOSI_H;
			}
			else
			{
				MOSI_L;
			}
      //如果MISO 是高则最低位加1
      //如果MISO 是低则不加
      data=data+MISO;
			SCLK_L;
      //每次传输完一个数据 配置左移一位
			wdata<<=1;
      
  }
  CS_H;
	return data;
}
