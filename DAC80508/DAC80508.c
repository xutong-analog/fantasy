/*
    Analogysemi xutong
    2023/02/21
*/
#include "DAC80508.h"
#include "board.h"
#include "bsp_lpspi.h"
#include "rtthread.h"
//获取DAC80508 ID
uint8_t* DAC80508_GetChipID(void)
{
    uint8_t Txdata[3]={DAC80508_ID,0x00,0x00};
    uint8_t Rxdata[3];
    Lpspi_Write(3,Txdata);
    Txdata[1]=0x00;
    Lpspi_Read(3,Txdata,Rxdata);
    return Rxdata;
}
//获取DAC80508 状态
uint8_t* DAC80508_GetChipSatus(void)
{
    uint8_t Txdata[3]={STATUS,0x00,0x00};
    uint8_t Rxdata[3];
    Lpspi_Write(3,Txdata);
    Txdata[1]=0x00;
    Lpspi_Read(3,Txdata,Rxdata);
    return Rxdata;
}
//写DAC80508 DAC值
void DAC80508_WriteDac(uint8_t DAC_CH,uint16_t DAC_Value)
{   
    uint8_t Txdata[3];
    Txdata[1]=DAC_CH;
    Txdata[2]=DAC_Value>>8;
    Txdata[3]=DAC_Value&0X00FF;
    Lpspi_Write(3,Txdata);
}
//写DAC80508 初始化
void DAC80508_Init(uint16_t CONFIG)
{
    uint8_t Txdata[3];
    Txdata[1]=DAC80508_CONFIG;
    Txdata[2]=CONFIG>>8;
    Txdata[3]=CONFIG&0X00FF;
    Lpspi_Write(3,Txdata);
}
