#include "AD5668.h"
#include "board.h"
#include "bsp_lpspi.h"
/*
	Channel Selection Range 1~16
	Value Range 0~65535
*/
void DAC_Write(uint8_t channel,uint16_t Value)
{
    uint8_t data[4];
     //command modify
    data[0]=WriteAndUpDateCh;
    //WriteAndUpDateCh
    // command modify
    data[1]=(Value>>12)|channel;
    data[2]=(Value>>4)&0x00ff;
    data[3]=(Value&0x000f)<<4;
    
    Lpspi_Write(4,data);

}
void DAC_Command_Write(uint8_t Command,uint8_t channel,uint16_t Value)
{
    uint8_t data[4];
     //command modify
    data[0]=Command;
    //WriteAndUpDateCh
    // command modify
    data[1]=(Value>>12)|channel;
    data[2]=(Value>>4)&0x00ff;
    data[3]=(Value&0x000f)<<4;
    
    Lpspi_Write(4,data);

}
/*
	Initial DAC GPIO
*/
void DAC_Init(void)
{

    //DAC_CLR_L;                                                                                                                                                                                                                                                                                                                                                                                                                       
    /* OPEN INTERANL REFERENCE */
    uint8_t data[4]={0x08,0xf0,0x00,0x01};
    Lpspi_Write(4,data);

}
void DAC_Reset(void)
{
    // no significance data
    uint8_t data[4]={0x00,0xf0,0x00,0x01};
     //command modify
    data[0]=ResetDac;
    Lpspi_Write(4,data);

}
//软件LDAC所有通道
//默认LDAC引脚都是0
void SoftLdac(void)
{
    uint8_t data[4]={0x06,0x00,0x00,0xFF};
    Lpspi_Write(4,data);
}
//设置CLR 清除代码
//三个选项 123 对应 0，32768，65535
void Clr_Code_sel(uint8_t CLR_CODE)
{
   switch(CLR_CODE)
   {
      //CLR CODE 等于全0x0000
      case 1:
        {
         DAC_Command_Write(loadClearReg,0x00,0x0000);
         break;
        }
     //CLR CODE 等于0x8000
      case 2:
        {
         DAC_Command_Write(loadClearReg,0x00,0x0001);
         break;
        }
      //CLR CODE 等于0xFFFF
      case 3:
         {
         DAC_Command_Write(loadClearReg,0x00,0x0002);
         break;
        }
      // CLR CODE  NO operation
      default :
         {
         DAC_Command_Write(loadClearReg,0x00,0x0003);
         break;
        }
       
   }
  
}
