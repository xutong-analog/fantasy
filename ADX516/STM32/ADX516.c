/*
    Analogysemi xutong
    2023/02/15
*/
#include "ADX516.h"
#include "cmsis_os2.h" 
static void ADX516_GPIO_Init(void);
void ADX516_READ(uint32_t len, uint8_t *wdata, uint8_t *rdata);
void ADX516_WRITE(uint32_t len, uint8_t *wdata);

// 初始化ADX516
void ADX516_Init(void)
{
//  ADX516_GPIO_Init();
  //    START_L;
  //    XTAL_H;
//    	ADX516_PWD_L;
     osDelay(1);	
//     ADX516_PWD_H;
     ADX516_REST_L;
     osDelay(150);
     ADX516_REST_H;
     osDelay(1);
     ADX516_REST_H;
}
static void ADX516_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10 | GPIO_PIN_11, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_15 | GPIO_PIN_14;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10 | GPIO_PIN_15 | GPIO_PIN_14, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = GPIO_PIN_7;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}
// 获取芯片的ID号
// Adx516 default Value 0x20
uint8_t ADX516_GetChipID(void)
{
  uint8_t ID;
  ID = ADX516_GetReg(ADX516_STATUS);
  return ID;
}
// 获取芯片寄存器值
uint8_t ADX516_GetReg(uint8_t Rreg)
{
  uint8_t TxData[3];
  uint8_t RxData[3];
  // 读取命令，
  TxData[0] = ADX516_RREG | Rreg;
  // 选择要读取的寄存器
  TxData[1] = 0x00;
  // 读取单个寄存器
  TxData[2] = 0X00;
  // 开始读取
  ADX516_READ(3, TxData, RxData);
  // 返回寄存器值
  return RxData[2];
}
// 写单个芯片寄存器值
void ADX516_WriteReg(uint8_t Wreg, uint8_t Data)
{
  uint8_t TxData[3];
  // 写入命令，
  TxData[0] = ADX516_WREG | Wreg;
  // 选择要写入的的寄存器
  TxData[1] = 0x00;
  // 读取写入寄存器
  TxData[2] = Data;
  ADX516_WRITE(3, TxData);
}
// 写多个芯片寄存器值
// StartReg 起始寄存器地址
// RegNum 要写的寄存器数量
//*Data  寄存器参数传入
void ADX516_WriteMultiReg(uint8_t StartReg, uint8_t RegNum, uint8_t *Data)
{
  uint8_t TxData[32];
  uint8_t i;
  // 写入命令，
  TxData[0] = ADX516_WREG | StartReg;
  // 选择要写入的的寄存器
  TxData[1] = RegNum - 1;
  for (i = 0; i < RegNum; i++)
  {
    // 将指针数据赋值给Txdata
    TxData[2 + i] = *Data;
    // 指向下个数据地址
    Data++;
  }
  // 最终发送多少个数据
  ADX516_WRITE(2 + RegNum, TxData);
}
// 读多个芯片寄存器值
// StartReg 起始寄存器地址
// RegNum 要写的寄存器数量
//*Data  寄存器参数传出
void ADX516_ReadMultiReg(uint8_t StartReg, uint8_t RegNum, uint8_t *Data)
{
  // 读取寄存器
  uint8_t TxData[3];
  // 读取命令，
  TxData[0] = ADX516_RREG | StartReg;
  // 选择要写入的的寄存器
  TxData[1] = RegNum - 1;
  // 最终接收多少个数据
  ADX516_READ(2 + RegNum, TxData, Data);
}
// 打印所有寄存器地址
void ADX516_GetAllReg(void)
{
  uint8_t i, j;
  for (i = 0; i < 20; i++)
  {
    j = ADX516_GetReg(i);
    // 打印所有寄存器值
    //    rt_kprintf("reg addr: %d reg default Value: %x\r\n",i,j);
  }
}
// 发送ADX516 数据指令 如SDATAC或者RDATAC
// 详情见头文件command define部分
void ADX516_Command(uint8_t Com)
{
  uint8_t TxData[] = {Com};
  ADX516_WRITE(1, TxData);
}
// 设定通道并且获取adc数据
// 获取ADC的值
void ADX516_GetADC_Value(uint8_t Ch, uint32_t *Rxdata,uint32_t times)
{
  uint8_t TxData[] = {ADX516_RDATA};
  ADX516_Command(ADX516_SDATAC);
  ADX516_WriteReg(ADX516_MUX, Ch << 4 | 0X0F);
  ADX516_Command(ADX516_SYNC);
  ADX516_Command(ADX516_WAKEUP);
  // rt_thread_mdelay(1);
	osDelay(1);
	for (uint32_t i =0;i<times;i++){
		ADX516_READ(4, TxData, (uint8_t *)&Rxdata[i]);
		Rxdata[i] &=0x00FFFFFF;
		HAL_Delay(3);
	}
}

void ADX516_READ(uint32_t len, uint8_t *wdata, uint8_t *rdata)
{
  uint8_t buff;
  uint16_t timeout = 10;
  uint8_t RES = 0;
  ADX516_CS_H;
  ADX516_CLK_L;
  HAL_Delay(1);
//  ADX516_CS_L;
//  while(ADX516_DRDY);
  ADX516_CS_L;
  while (timeout--)
    ;
  for (uint32_t Num = 0; Num < len; Num++)
  {
    buff = wdata[Num];
		RES = 0;
    for (int i = 7; i >= 0; i--)
    {
      ADX516_CLK_H;
      if (buff & (0x01 << i))
        ADX516_DIN_H;
      else
        ADX516_DIN_L;
			timeout = 2;
      while (timeout--)
        ;
			if(ADX516_SDO)
				RES |= (0x1 << i);
			timeout = 3;
      while (timeout--)
        ;			
      ADX516_CLK_L;
      timeout = 8;
      while (timeout--)
        ;
    }
			rdata[len-Num-1]=RES;
  }
}

void ADX516_WRITE(uint32_t len, uint8_t *wdata)
{
  uint8_t buff;
  uint16_t timeout = 10;
  uint32_t RES = 0;
  ADX516_CS_H;
  ADX516_CLK_L;
  HAL_Delay(1);
  ADX516_CS_L;
  // while(ADX516_SDO);
  // ADX516_CS_L;
  while (timeout--)
    ;
  for (uint32_t Num = 0; Num < len; Num++)
  {
    buff = wdata[Num];
    for (int i = 7; i >= 0; i--)
    {
			if (buff & (0x01 << i))
        ADX516_DIN_H;
      else
        ADX516_DIN_L;
      ADX516_CLK_H;
			timeout = 5;
      while (timeout--)
        ;     
      ADX516_CLK_L;
			timeout = 5;
      while (timeout--)
        ;
    }
  }
  HAL_Delay(1);
  ADX516_CS_H;
}
