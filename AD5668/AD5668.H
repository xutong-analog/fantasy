#ifndef __AD5668_H
#define __AD5668_H
#include "bsp_lpspi.h"
/*
	AD5668 COMMAND AND ADDRESS
	MSB
	31 30 29 28  27 26 25 24
	X   X  X  X  C3 C2 C1 C0
	23 22 21 20  19 		-> 		5 
	A3 A2 A1 A0  Data Msb-> DataLSB
	4 3 2 1
	X X X X
*/
/*
	COMMAND 
*/
#define  WriteToReg			        0X00
#define  UpdateDacReg				0X01
#define  WriteAndUpDateAll			0X02
#define  WriteAndUpDateCh		        0x03	
#define  PowerDownAndPowerUpDac		        0x04
#define  loadClearReg		                0x05
#define  loadLdacReg		                0x06
#define	 ResetDac				0x07
#define	 SetUpRef				0x80
/*
	ADDRESS  
*/
#define  ChannelA					0X00
#define  ChannelB					0X10
#define  ChannelC					0X20
#define  ChannelD					0X30
#define  ChannelE					0X40
#define  ChannelF					0X50
#define  ChannelG					0X60
#define  ChannelH					0X70
#define  ChannelAll					0XF0
/*
	Ctrl GPIO redefine
*/
#define  DAC_CS1_L			SF_NSS1_L
#define  DAC_CS1_H			SF_NSS1_H

#define  DAC_CLR_PIN		        GPIO_PIN_13
#define	 DAC_CLR_H			HAL_GPIO_WritePin(DAC_CLR_PORT,DAC_CLR_PIN,GPIO_PIN_SET)
#define	 DAC_CLR_L			HAL_GPIO_WritePin(DAC_CLR_PORT,DAC_CLR_PIN,GPIO_PIN_RESET)




/*
	Channel Selection Range 1~8
	Value Range 0~65535
*/
void DAC_Init(void);
void DAC_Write(uint8_t channel,uint16_t Value);
void DAC_Command_Write(uint8_t Command,uint8_t channel,uint16_t Value);
void DAC_Reset(void);
void SoftLdac(void);
//设置清除代码类型
void Clr_Code_sel(uint8_t CLR_CODE);
#endif
