/*
    Analogysemi xutong
    2023/02/15
*/
#ifndef __ADX3208_H
#define __ADX3208_H
#include "bsp_lpspi.h"
/*
    device 需要先写入SDTAC 启动寄存器写入才可以对寄存器进行操作
    在此之前需要检查PWDN以及Reset引脚的状态是否为 高
    在操作完寄存器后，需要发送RDATAC 才能连续 读取数据
    bsp_lpspi 的接口函数如下：
    Lpspi_Write(uint8_t datasize,uint8_t *data);
    Lpspi_Read(uint8_t datasize,uint8_t *data,uint8_t *Rxdata);


    注意：
        Lpspi的时序并不一定满足ADX3208的配置，以下配置经过验证
        
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

#define ADX3208_WAKEUP 0x20
#define ADX3208_STANDBY 0x04
#define ADX3208_RESET   0x06
#define ADX3208_START   0x08
#define ADX3208_STOP    0x0a
#define ADX3208_OFFSETCAL   0x1a
#define ADX3208_RDATAC  0x10
#define ADX3208_SDATAC  0x11
#define ADX3208_RDATA   0x12
//RREG Read n nnnn registers starting at address r rrrr 
//First Byte 001r rrrr (2xh)
//Second Byte 000n nnnn 
//n nnnn = number of registers to be read or written – 1. For example, to read or write three registers, set n nnnn = 0 (0010). r rrrr = the
//starting register address for read and write commands
//WREG 同上
#define ADX3208_RREG    0x20
#define ADX3208_WREG    0X40


/*
    寄存器定义
*/
#define  ADX3208_ID 0x00
#define  ADX3208_CONFIG1 0x01
#define  ADX3208_CONFIG2 0x02
#define  ADX3208_CONFIG3 0x03
#define  ADX3208_LOFF 0x04
#define  ADX3208_CH1SET 0x05
#define  ADX3208_CH2SET 0x06
#define  ADX3208_CH3SET 0x07
#define  ADX3208_CH4SET 0x08
#define  ADX3208_CH5SET 0x09
#define  ADX3208_CH6SET 0x0A
#define  ADX3208_CH7SET 0x0B
#define  ADX3208_CH8SET 0x0C
#define  ADX3208_OPAMP_SENSP 0x0D
#define  ADX3208_OPAMP_SENSN 0x0E
#define  ADX3208_LOFF_SENSP 0x0F
#define  ADX3208_LOFF_SENSN 0x10
#define  ADX3208_LOFF_FLIP 0x11
#define  ADX3208_LOFF_STATP 0x12
#define  ADX3208_LOFF_STATN 0x13
#define  ADX3208_GPIO 0x14

/*
  寄存器Deafult 值
  寄存器地址10进制：  寄存器值16进制：
  reg addr: 0 reg default Value: 0e
  reg addr: 1 reg default Value: 91
  reg addr: 2 reg default Value: e0
  reg addr: 3 reg default Value: 40
  reg addr: 4 reg default Value: 00
  reg addr: 5 reg default Value: 10
  reg addr: 6 reg default Value: 10
  reg addr: 7 reg default Value: 10
  reg addr: 8 reg default Value: 10
  reg addr: 9 reg default Value: 10
  reg addr: 10 reg default Value: 10
  reg addr: 11 reg default Value: 10
  reg addr: 12 reg default Value: 10
  reg addr: 13 reg default Value: 00
  reg addr: 14 reg default Value: 00
  reg addr: 15 reg default Value: 00
  reg addr: 16 reg default Value: 00
  reg addr: 17 reg default Value: 00
  reg addr: 18 reg default Value: 00
  reg addr: 19 reg default Value: 00
  reg addr: 20 reg default Value: 0f
  reg addr: 21 reg default Value: 00
  reg addr: 22 reg default Value: 00
  reg addr: 23 reg default Value: 00
*/

#define ADX3208_ADC_Resolution_16 16
#define ADX3208_ADC_Resolution_24 24




//写命令
void ADX3208_Command(uint8_t Com);
//获取芯片的ID号
uint8_t ADX3208_GetChipID(void);
//获取寄存器值
uint8_t ADX3208_GetReg(uint8_t Rreg);
//获取多个寄存器值
void ADX3208_ReadMultiReg(uint8_t StartReg,uint8_t RegNum,uint8_t *Data);
//写入寄存器值
void ADX3208_WriteReg(uint8_t Wreg,uint8_t Data);
//写多个寄存器的值
void ADX3208_WriteMultiReg(uint8_t StartReg,uint8_t RegNum,uint8_t *Data);
//获取所有寄存器值
void ADX3208_GetAllReg(void);
//获取ADC的值
void ADX3208_GetADC_Value(uint8_t ADC_Resolution,uint8_t *Rxdata);
//初始化ADX3208
void ADX3208_Init(void);
#endif
