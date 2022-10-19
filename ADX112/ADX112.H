//定义头文件名字
#ifndef __ADX112_H
#define __ADX112_H

//用的MCU什么型号写啥 我这里用的是G0 所以拷贝这个
#include "stm32g0xx_hal.h"

//宏定义 将MOSI的PIN指定到那个PIN 
#define MOSI_PIN    GPIO_PIN_0
#define MISO_PIN    GPIO_PIN_1
#define SCLK_PIN    GPIO_PIN_2
#define CS_PIN      GPIO_PIN_3
//定义SPI所使用的端口 
//换MCU或者改端口时候直接改宏定义就好了
#define MOSI_PORT   GPIOA
#define MISO_PORT   GPIOA
#define SCLK_PORT   GPIOA
#define CS_PORT     GPIOA
//定义各个引脚的时钟
#define CS_PORT_CLK_ENABLE	 __HAL_RCC_GPIOC_CLK_ENABLE()
#define SCLK_PORT_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE()
#define MISO_PORT_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE()
#define MOSI_PORT_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE()
//定义引脚输出输入代号 可以少打点字
#define CS_H		HAL_GPIO_WritePin(CS_PORT,CS_PIN,GPIO_PIN_SET)
#define CS_L		HAL_GPIO_WritePin(CS_PORT,CS_PIN,GPIO_PIN_RESET)
#define MOSI_H		HAL_GPIO_WritePin(MOSI_PORT,MOSI_PIN,GPIO_PIN_SET)
#define MOSI_L		HAL_GPIO_WritePin(MOSI_PORT,MOSI_PIN,GPIO_PIN_RESET)
#define SCLK_H		HAL_GPIO_WritePin(SCLK_PORT,SCLK_PIN,GPIO_PIN_SET)
#define SCLK_L		HAL_GPIO_WritePin(SCLK_PORT,SCLK_PIN,GPIO_PIN_RESET)
#define MISO		HAL_GPIO_ReadPin(MISO_PORT,MISO_PIN)

//定义ADX112的配置
#define DR_8SPS 		0x0000
#define DR_16SPS 		0x0020
#define DR_32SPS 		0x0040
#define DR_64SPS 		0x0060
#define DR_128SPS 	    0x0080
#define DR_250SPS 	    0x00a0
#define DR_475SPS 	    0x00c0
#define DR_860SPS 	    0x00e0

#define MUX_PA0_NA1 		0x0000
#define MUX_PA0_NA3 		0x1000
#define MUX_PA1_NA3 		0x2000
#define MUX_PA2_NA3 		0x3000
#define MUX_PA0_NGND 	0x4000
#define MUX_PA1_NGND 	0x5000
#define MUX_PA2_NGND 	0x6000
#define MUX_PA3_NGND 	0x7000

#define MODE_CONTIUOUS      0x0000
#define MODE_POWERDOWN    0x0100

#define Single_Conversion_DIS 0x0000
#define Single_Conversion_SSC    0x8000

#define PGA_GAIN_6_144 		0x0000
#define PGA_GAIN_4_096 		0x0200
#define PGA_GAIN_2_048 		0x0400
#define PGA_GAIN_0_024		0x0600
#define PGA_GAIN_0_512 	  0x0800
#define PGA_GAIN_0_256 	  0x0a00

#define TS_MODE_ADC 	    0x0000
#define TS_MODE_TS	        0x0010

#define PULL_UP_DOUT_PullupDis        0x0000
#define PULL_UP_DOUT_PullupEn         0x0008

#define NOP_Pdata_NPConfig          0x0000
#define NOP_Pdata_PConfig           0x0002
//ADX112结构体
typedef struct
{
		uint16_t MUX;
		uint16_t PGA_GAIN;
		uint16_t DR;
		uint16_t MODE;
		uint16_t TS_MODE;
		uint16_t Single_Conversion;
		uint16_t PULL_UP_DOUT;
		uint16_t NOP;
} ADX112_InitTypeDef;

//将ADX112 各个bit 信息拷贝至此
/**************************************
 *    ADX112 Register CONFIG
 **************************************
 *    Bit 15    /   Single Conversion
 *    Bit 14    /   MUX
 *    Bit 13    /   MUX
 *    Bit 12    /   MUX

 *    Bit 11    /   PGA
 *    Bit 10    /   PGA
 *    Bit 9      /   PGA
 *    Bit 8      /   MODE

 *    Bit 7      /   DR
 *    Bit6       /   DR
 *    Bit5       /   DR
 *    Bit4       /   TS_MODE

 *    Bit3       /   PULL_UP_DOUT
 *    Bit2       /   NOP
 *    Bit1       /   NOP
 *    Bit 0      /   Reserved
 * |15-12  |11-8  |7-4 |3-0|
 *    8421  8421  8421 8421
 *    0~~~  0100  1000 0010
 *   				
 *************************************/
 /************************************
	MUX=100 AINP = AIN0 	0x4
	MUX=101 AINP = AIN1		0x5
	MUX=110 AINP = AIN2		0x6
	MUX=111 AINP = AIN3		0x7

	FULL SCALE RANGE =>	 2.048 V
	DATE RATE		 =>	 860 SPS
	
 ************************************/
/* ADX112 初始化 */
void ADX112_GPIO_Init(void);
uint16_t ADX112_Get_ADValue(ADX112_InitTypeDef * Config);

#endif
