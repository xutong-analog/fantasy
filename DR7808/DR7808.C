#include "DR7808.h"


void DR7808_delay(uint32_t count)
{ 
    volatile uint32_t i = 0;
    for (i = 0; i < count; ++i)
    {
        __asm("NOP"); /* 调用nop空指令 */
         __asm("NOP"); /* 调用nop空指令 */
          __asm("NOP"); /* 调用nop空指令 */
           __asm("NOP"); /* 调用nop空指令 */
            __asm("NOP"); /* 调用nop空指令 */
    }
}
//获取寄存器信息
void DR7808_Read_Reg(uint8_t Reg,uint8_t *RData)
{
  uint8_t TxData[3]={0X00,0X00,0X00};
  //读取寄存器
  TxData[0]=(Reg<<1)|0xC0;
  Lpspi_Read(3,TxData,RData);
}
//读取与清除寄存器信息
void DR7808_Read_Clear_Reg(uint8_t Reg,uint8_t *RData)
{
  uint8_t TxData[3]={0X00,0X00,0X00};
  //读取寄存器
  TxData[0]=(Reg<<1)|0xC1;
  Lpspi_Read(3,TxData,RData);
}
//写寄存器信息
void DR7808_Write_Reg(uint8_t Reg,uint16_t WData,uint8_t *RData)
{
  uint8_t TxData[3]={0X00,0X00,0X00};
  //读取寄存器&写入寄存器
  TxData[0]=(Reg<<1)|0xC1;
  TxData[1]=WData>>8;
  TxData[2]=WData&0x00FF;
  Lpspi_Read(3,TxData,RData);
}
// dr7808 退出FS Mode
void DR7808_Quit_FS(void)
{
  uint8_t Data[3]={0X00,0X00,0X00};
  //读取并且清除Gensata
  DR7808_Read_Clear_Reg(DR7808_GENSTAT,Data);
  DR7808_delay(2000);
  //看门狗位置1
  DR7808_Write_Reg(DR7808_GENCTRL1,0x0027,Data);
  DR7808_delay(2000);
  //看门狗位置0
  DR7808_Write_Reg(DR7808_GENCTRL1,0x0000,Data);
  DR7808_delay(2000);
}
// dr7808 禁用看门狗
void DR7808_Dis_WD(void)
{
  uint8_t Data[3];
  DR7808_delay(2000);
  //看门狗Unlock 置1
  DR7808_Write_Reg(DR7808_GENCTRL1,0x00A7,Data);
  DR7808_delay(2000);
  //禁用看门狗
  DR7808_Write_Reg(DR7808_GENCTRL2,0x4380,Data);
}
// dr7808桥壁配置
void DR7808_Half_Bridge_Mode(HBMODE_InitTypeDef* config,uint8_t *RData)
{
  uint16_t WData=0;
  WData|=(config->HB8_Mode)<<14;
  WData|=(config->HB7_Mode)<<12;
  WData|=(config->HB6_Mode)<<10;
  WData|=(config->HB5_Mode)<<8;
  WData|=(config->HB4_Mode)<<6;
  WData|=(config->HB3_Mode)<<4;
  WData|=(config->HB2_Mode)<<2;
  WData|=(config->HB1_Mode);
  DR7808_Write_Reg(DR7808_HBMODE,WData,RData);
}
// 未测试
// dr7808 PWM 通道配置
void DR7808_PWMSET_Channel(PWMSET_InitTypeDef* config,uint8_t *RData)
{
  uint16_t WData=0;
  WData|=(config->PWM1_HB)<<1;
  WData|=(config->PWM2_HB)<<5;
  WData|=(config->PWM3_HB)<<9;
  WData|=(config->PWM1_EN);
  WData|=(config->PWM2_EN)<<4;
  WData|=(config->PWM3_EN)<<8;
  WData|=(config->PASS_VDS)<<14;
  WData|=(config->PASS_Mode)<<12;
  DR7808_Write_Reg(DR7808_PWMSET,WData,RData);
  
}
//未测试
//VDS Monitor threshold setting HB1~HB4
void DR7808_VDS_Monitoring_1_4(VDS_Vth_InitTypeDef* config,uint8_t *RData)
{
  uint16_t WData=0;
  WData|=(config->HB1_VDSTh);
  WData|=(config->HB2_VDSTh)<<3;
  WData|=(config->HB3_VDSTh)<<6;
  WData|=(config->HB4_VDSTh)<<9;
  DR7808_Write_Reg(DR7808_VDS1,WData,RData);
}
//未测试
//VDS Monitor threshold setting HB5~HB8
void DR7808_VDS_Monitoring_5_8(VDS_Vth_InitTypeDef* config,uint8_t *RData)
{
  uint16_t WData=0;
  WData|=(config->HB5_VDSTh);
  WData|=(config->HB6_VDSTh)<<3;
  WData|=(config->HB7_VDSTh)<<6;
  WData|=(config->HB8_VDSTh)<<9;
  DR7808_Write_Reg(DR7808_VDS2,WData,RData);
}
// dr7808喂狗操作
void DR7808_Feed_Dog(uint8_t *RData)
{
  uint16_t WData=0;
  uint8_t Data[3];
  //读取看门狗位
  DR7808_Read_Reg(DR7808_GENCTRL1,Data);
  DR7808_delay(20);
  //如果看门狗位为1
  if((Data[2]&0x01)==1)
  {
    //看门狗位置0并写入
    Data[2]&=0XFE;
    WData|=Data[1]<<8;
    WData|=Data[2];
    DR7808_Write_Reg(DR7808_GENCTRL1,WData,RData);
  }
  else
  {
    //看门狗位置1并写入
    Data[2]|=0X01;
    WData|=Data[1]<<8;
    WData|=Data[2];
    DR7808_Write_Reg(DR7808_GENCTRL1,WData,RData);
  }
}
// dr7808 csa相关配置
void DR7808_CSA_Conifg(CSA_InitTypeDef* config,uint8_t *RData)
{
  uint16_t WData=0;
  uint8_t Data[3];
  //读取GENCTRL1配置
  DR7808_Read_Reg(DR7808_GENCTRL1,Data);
  WData|=(config->CSA2_Direction)<<15;
  WData|=(config->CSA2_Gain)<<13;
  WData|=(config->CSA1_Direction)<<12;
  WData|=(config->CSA1_Gain)<<10;
  //接收值后十位不变
  WData|=(Data[1]&0x03)<<8;
  WData|=Data[2];
  DR7808_Write_Reg(DR7808_GENCTRL1,WData,RData);
  //清空WData
  WData=0;
  DR7808_delay(20);
  DR7808_Read_Reg(DR7808_HBIDIAG,Data);
  WData|=Data[2];
  WData|=(config->CSA2_Level)<<15;
  WData|=(config->CSA1_Level)<<14;
  WData|=(config->OC2FILT)<<12;
  WData|=(config->OC1FILT)<<10;
  WData|=(config->CSA2_OFF)<<9;
  WData|=(config->CSA1_OFF)<<8;
  DR7808_Write_Reg(DR7808_HBIDIAG,WData,RData);
    //清空WData
  WData=0;
  DR7808_delay(20);
   //读取GENCTRL2配置
  DR7808_Read_Reg(DR7808_GENCTRL2,Data);
  //清空后四位
  Data[2]&=0XF0;
  //高8位不变
  WData|=Data[1]<<8;
  WData|=Data[2];
  WData|=(config->OCTH2)<<2;
  WData|=(config->OCTH1);
  DR7808_Write_Reg(DR7808_GENCTRL2,WData,RData);
  //清空WData
  WData=0;
  DR7808_delay(20);
  //读取GENCTRL2配置
  DR7808_Read_Reg(DR7808_CSA_OC_SH,Data);
  WData=0;
  //最高位PWM不变
  WData=(Data[1]&0X80)<<8;
  WData|=(config->CSA_BLK_SEL)<<9;
  WData|=(config->CSA2_SH_EN)<<8;
  WData|=(config->CSA1_SH_EN)<<7;
  WData|=(config->OC_SEP_EN)<<6;
  WData|=(config->CSA2_SEL)<<3;
  WData|=(config->CSA1_SEL);
  //写入过流数据
  DR7808_Write_Reg(DR7808_CSA_OC_SH,WData,RData);
}
// 需要配置Reg Bank
// 静态充放电电流设置
void DR7808_ST_ICHG_Conifg(ST_ICHG_InitTypeDef* config,uint8_t *RData)
{
  uint16_t WData=0;
  uint8_t Data[3];
 // 读取DR7808_GENCTRL1配置 并将REG BANK 其配置为0
  DR7808_Read_Reg(DR7808_GENCTRL1,Data);
  Data[1]=Data[1]&0xfd;
  WData=Data[1]<<8;
  WData|=Data[2];
  //写入reg bank
  DR7808_Write_Reg(DR7808_GENCTRL1,WData,RData);
  DR7808_delay(20);
  WData=0;
  //设置是电流1还是电流2
  WData|=(config->HB8_ICHG)<<15;
  WData|=(config->HB7_ICHG)<<14;
  WData|=(config->HB6_ICHG)<<13;
  WData|=(config->HB5_ICHG)<<12;
  WData|=(config->HB4_ICHG)<<11;
  WData|=(config->HB3_ICHG)<<10;
  WData|=(config->HB2_ICHG)<<9;
  WData|=(config->HB1_ICHG)<<8;
  //设置电流挡位2
  WData|=(config->ICHGST_2)<<4;
  //设置电流挡位1
  WData|=(config->ICHGST_1);
  //写入电流挡位
  DR7808_Write_Reg(DR7808_ST_ICHG,WData,RData);
}
// dr7808 ID获取
uint8_t DR7808_GetChipID(void)
{
  uint8_t Data[3];
  DR7808_Read_Reg(DR7808_DEVID,Data);
  return Data[2];
}
//读取所有寄存器
void Get_All_Reg(uint8_t* RData)
{
  uint8_t i=0;
  for(i=0;i<0x1f;i++)
  {
    DR7808_Read_Reg(i,RData);
    RData++;
    DR7808_delay(330);
  }
  
}




