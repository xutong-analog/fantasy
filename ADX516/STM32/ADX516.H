/*
    Analogysemi xutong
    2023/02/15
*/
#include "main.h"

#ifndef __ADX516_H
#define __ADX516_H
/*
    device 需要先写入SDTAC 启动寄存器写入才可以对寄存器进行操作
    在此之前需要检查PWDN以及Reset引脚的状态是否为 高
    在操作完寄存器后，需要发送RDATAC 才能连续 读取数据
    bsp_lpspi 的接口函数如下：
    Lpspi_Write(uint8_t datasize,uint8_t *data);
    Lpspi_Read(uint8_t datasize,uint8_t *data,uint8_t *Rxdata);


    注意：
        Lpspi的时序并不一定满足ADX516的配置，以下配置经过验证
        
        lpspi_master_config_t config;
        LPSPI_MasterGetDefaultConfig(&config);
        config.whichPcs=kLPSPI_Pcs0;
        config.baudRate=50000;
        config.betweenTransferDelayInNanoSec = 1000000000 /500;
        config.pcsToSckDelayInNanoSec=1000000000 /500;
        config.lastSckToPcsDelayInNanoSec=1000000000 /500;
        config.cpha=kLPSPI_ClockPhaseSecondEdge;
        LPSPI_MasterInit(LPSPI3, &config, LPSPI3_CLOCK_FREQ);

*/

/*command define*/
#define ADX516_REF 2.5
#define ADX516_PGA 1
#define ADX516_LSB (2*ADX516_REF)/(ADX516_PGA*8388607)

#define ADX516_WAKEUP 0x00
#define ADX516_RDATA   0x01
#define ADX516_RDATAC  0x03
#define ADX516_SDATAC  0x0F
#define ADX516_RREG    0x10
#define ADX516_WREG    0X50
#define ADX516_SELFCAL 0XF0
#define ADX516_SELFOCAL 0XF1
#define ADX516_SELFGCAL 0XF2
#define ADX516_SYSOCAL 0XF3
#define ADX516_SYSGCAL 0XF4
#define ADX516_SYNC     0XFC
#define ADX516_STANDBY 0xFD
#define ADX516_RESET   0xFE



//RREG Read n nnnn registers starting at address r rrrr 
//First Byte 001r rrrr (2xh)
//Second Byte 000n nnnn 
//n nnnn = number of registers to be read or written – 1. For example, to read or write three registers, set n nnnn = 0 (0010). r rrrr = the
//starting register address for read and write commands
//WREG 同上




/*
    寄存器定义
*/
#define  ADX516_STATUS 0x00
#define  ADX516_MUX 0x01
#define  ADX516_ADCON 0x02
#define  ADX516_DRATE 0x03
#define  ADX516_IO 0x04
#define  ADX516_OFC0 0x05
#define  ADX516_OFC1 0x06
#define  ADX516_OFC2 0x07
#define  ADX516_FSC0 0x08
#define  ADX516_FSC1 0x09
#define  ADX516_FSC2 0x0A
#define  ADX516_CFG0 0x0B
#define  ADX516_CFG1 0x0C
#define  ADX516_CFG2 0x0D
#define  ADX516_CFG3 0x0E
#define  ADX516_CFG4 0x0F
#define  ADX516_CFG5 0x10
#define  ADX516_DEV_CFG 0x11
#define  ADX516_MOD_STAT 0x12
#define  ADX516_DEV_STAT 0x13
#define  ADX516_CMD_STAT 0x14





#define ADX516_CLK_PORT GPIOB
#define ADX516_CLK_PIN GPIO_PIN_15

#define ADX516_REST_PORT GPIOD
#define ADX516_REST_PIN GPIO_PIN_12

//#define ADX516_SYN_PORT GPIOB
//#define ADX516_SYN_PIN GPIO_PIN_14

#define ADX516_CS_PORT GPIOB
#define ADX516_CS_PIN GPIO_PIN_14

#define ADX516_DIN_PORT GPIOD
#define ADX516_DIN_PIN GPIO_PIN_11

#define ADX516_DRDY_PORT GPIOA
#define ADX516_DRDY_PIN GPIO_PIN_11

#define ADX516_DO_PORT GPIOG
#define ADX516_DO_PIN GPIO_PIN_9

#define ADX516_SDO   (ADX516_DO_PORT->IDR & ADX516_DO_PIN)
#define ADX516_DRDY   HAL_GPIO_ReadPin(ADX516_DRDY_PORT,ADX516_DRDY_PIN)
#define ADX516_PWD_H  HAL_GPIO_WritePin(ADX516_SYN_PORT,ADX516_SYN_PIN,GPIO_PIN_SET)
#define ADX516_PWD_L  HAL_GPIO_WritePin(ADX516_SYN_PORT,ADX516_SYN_PIN,GPIO_PIN_SET)

#define ADX516_CS_H   HAL_GPIO_WritePin(ADX516_CS_PORT,ADX516_CS_PIN,GPIO_PIN_SET)
#define ADX516_CLK_H  HAL_GPIO_WritePin(ADX516_CLK_PORT,ADX516_CLK_PIN,GPIO_PIN_SET)
#define ADX516_SYN_H  HAL_GPIO_WritePin(ADX516_SYN_PORT,ADX516_SYN_PIN,GPIO_PIN_SET)
#define ADX516_DIN_H  HAL_GPIO_WritePin(ADX516_DIN_PORT,ADX516_DIN_PIN,GPIO_PIN_SET)
#define ADX516_REST_H HAL_GPIO_WritePin(ADX516_REST_PORT,ADX516_REST_PIN,GPIO_PIN_SET)

#define ADX516_CS_L   HAL_GPIO_WritePin(ADX516_CS_PORT,ADX516_CS_PIN,GPIO_PIN_RESET)
#define ADX516_CLK_L  HAL_GPIO_WritePin(ADX516_CLK_PORT,ADX516_CLK_PIN,GPIO_PIN_RESET)
#define ADX516_SYN_L  HAL_GPIO_WritePin(ADX516_SYN_PORT,ADX516_SYN_PIN,GPIO_PIN_RESET)
#define ADX516_DIN_L  HAL_GPIO_WritePin(ADX516_DIN_PORT,ADX516_DIN_PIN,GPIO_PIN_RESET)
#define ADX516_REST_L HAL_GPIO_WritePin(ADX516_REST_PORT,ADX516_REST_PIN,GPIO_PIN_RESET)
/*
  通道配置
  channel config
*/
#define ADX516_ADC_CH0
#pragma anon_unions
typedef  union
{
	uint32_t data;
	struct 
	{
		uint8_t BYTE;
		uint8_t B_W_R;
	  uint8_t ADDR;
		uint8_t A_W_R;
	};
}ADX516_RCOMMAND_TYPE;
typedef  union
{
	uint32_t data[2];
	struct 
	{
		uint16_t IO_DATA;
		uint16_t DATA;
		uint8_t BYTE;
		uint8_t B_W_R;
	  uint8_t ADDR;
		uint8_t A_W_R;
	};
}ADX516_WCOMMAND_TYPE;

//写命令
void ADX516_Command(uint8_t Com);
//获取芯片的ID号
extern uint8_t ADX516_GetChipID(void);

//获取寄存器值
uint8_t ADX516_GetReg(uint8_t Rreg);
//获取多个寄存器值
void ADX516_ReadMultiReg(uint8_t StartReg,uint8_t RegNum,uint8_t *Data);
//写入寄存器值
extern void ADX516_WriteReg(uint8_t Wreg,uint8_t Data);
//写多个寄存器的值
extern void ADX516_WriteMultiReg(uint8_t StartReg,uint8_t RegNum,uint8_t *Data);
//获取所有寄存器值
extern void ADX516_GetAllReg(void);
//设定通道并且获取ADC的值
extern void ADX516_GetADC_Value(uint8_t Ch, uint32_t *Rxdata,uint32_t times);
//初始化ADX516
extern void ADX516_Init(void);
#endif
