/*
    Analogysemi xutong
    2023/02/15
*/
#include "ADX516.h"
#include "board.h"
#include "bsp_lpspi.h"
#include "rtthread.h"
//初始化ADX516
void ADX516_Init(void)
{
//    START_L;
//    XTAL_H;
//    PWDN_H;
//    RST_H;
//    rt_thread_mdelay(150);
//    RST_L;
//    rt_thread_mdelay(1);
//    RST_H;
  
}
//获取芯片的ID号
//Adx516 default Value 0x20
uint8_t ADX516_GetChipID(void)
{
    uint8_t ID;
    ID=ADX516_GetReg(ADX516_STATUS);
    return ID;
}
//获取芯片寄存器值
uint8_t ADX516_GetReg(uint8_t Rreg)
{
   uint8_t TxData[3];
   uint8_t RxData[3];
    //读取命令，
    TxData[0]=ADX516_RREG|Rreg;
    //选择要读取的寄存器
    TxData[1]=0x00;
    //读取单个寄存器
    TxData[2]=0X00;
    //开始读取
    Lpspi_Read(3,TxData,RxData);
    //返回寄存器值
    return RxData[2];
}
//写单个芯片寄存器值
void ADX516_WriteReg(uint8_t Wreg,uint8_t Data)
{
    uint8_t TxData[3];
    //写入命令，
    TxData[0]=ADX516_WREG|Wreg;
    //选择要写入的的寄存器
    TxData[1]=0x00;
    //读取写入寄存器
    TxData[2]=Data;
    Lpspi_Write(3,TxData);
}
//写多个芯片寄存器值
//StartReg 起始寄存器地址
//RegNum 要写的寄存器数量
//*Data  寄存器参数传入
void ADX516_WriteMultiReg(uint8_t StartReg,uint8_t RegNum,uint8_t *Data)
{
    uint8_t TxData[32];
    uint8_t i;
    //写入命令，
    TxData[0]=ADX516_WREG|StartReg;
    //选择要写入的的寄存器
    TxData[1]=RegNum-1;
    for(i=0;i<RegNum;i++)
    {
       //将指针数据赋值给Txdata
       TxData[2+i]=*Data;
       //指向下个数据地址
       Data++;
    }
    //最终发送多少个数据
    Lpspi_Write(2+RegNum,TxData);
}
//读多个芯片寄存器值
//StartReg 起始寄存器地址
//RegNum 要写的寄存器数量
//*Data  寄存器参数传出
void ADX516_ReadMultiReg(uint8_t StartReg,uint8_t RegNum,uint8_t *Data)
{
    //读取寄存器
    uint8_t TxData[3];
    //读取命令，
    TxData[0]=ADX516_RREG|StartReg;
    //选择要写入的的寄存器
    TxData[1]=RegNum-1;
    //最终接收多少个数据
     Lpspi_Read(2+RegNum,TxData,Data);
}
//打印所有寄存器地址
void ADX516_GetAllReg(void)
{
  uint8_t i,j;
  for(i=0;i<20;i++)
  { 
    j=ADX516_GetReg(i);
    //打印所有寄存器值
    rt_kprintf("reg addr: %d reg default Value: %x\r\n",i,j);
  }
}
//发送ADX516 数据指令 如SDATAC或者RDATAC
//详情见头文件command define部分
void ADX516_Command(uint8_t Com)
{
    uint8_t TxData[]={Com};
    Lpspi_Write(1,TxData);
}
//设定通道并且获取adc数据
//获取ADC的值 
void ADX516_GetADC_Value(uint8_t Ch,uint8_t *Rxdata)
{
    uint8_t TxData[]={ADX516_RDATA};
    ADX516_Command(ADX516_SDATAC);
    ADX516_WriteReg(ADX516_MUX,Ch<<4|0X0F);
    ADX516_Command(ADX516_SYNC);
    ADX516_Command(ADX516_WAKEUP);
    //rt_thread_mdelay(1);
    Lpspi_Read(4,TxData,Rxdata);
    
}
