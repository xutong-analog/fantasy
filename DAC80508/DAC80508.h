/*
    Analogysemi xutong
    2023/02/21
*/
#ifndef __DAC80508_H
#define __DAC80508_H
#include "bsp_lpspi.h"

/*
    bsp_lpspi 的接口函数如下：
    Lpspi_Write(uint8_t datasize,uint8_t *data);
    Lpspi_Read(uint8_t datasize,uint8_t *data,uint8_t *Rxdata);
*/
#define     DAC80508_ID     0X01
#define     DAC80508_SYNC            0X02
#define     DAC80508_CONFIG          0X03
#define     DAC80508_GAIN            0X04
#define     DAC80508_TRIGGER         0X05
#define     DAC80508_BRDCAST         0X06
#define     DAC80508_STATUS          0X07
#define     DAC80508_DAC0            0X08
#define     DAC80508_DAC1            0X09
#define     DAC80508_DAC2            0X0A
#define     DAC80508_DAC3            0X0B
#define     DAC80508_DAC4            0X0C
#define     DAC80508_DAC5            0X0D
#define     DAC80508_DAC6            0X0E
#define     DAC80508_DAC7            0X0F

//获取DAC80508 ID值
uint8_t* DAC80508_GetChipID(void);
//获取DAC80508状态
uint8_t* DAC80508_GetChipSatus(void);
//写入DAC 值
void DAC80508_WriteDac(uint8_t DAC_CH,uint16_t DAC_Value);
//DAC80508 初始化
void DAC80508_Init(uint16_t CONFIG);
#endif
