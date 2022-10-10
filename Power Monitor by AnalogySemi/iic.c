#include "IIC.h"

/*
	Setup1:
	determin iic gpio 
	Setup2:
	// gpio init
	IIC_GPIO_Init();
	Setup3:
	//IIC  Write
	IIC_Start();
	IIC_Write(ADDR);
	IIC_Write(DATA);
	IIC_Stop();
	Setup4:
	//IIC Read 
	IIC_Start();
	IIC_Write(ADDR);
	IIC_Read(DATA);
	IIC_Stop();
*/
void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.Pin=SDA_Pin;
	GPIOInitStruct.Pull=GPIO_NOPULL;
	GPIOInitStruct.Speed=GPIO_SPEED_MEDIUM;
	GPIOInitStruct.Mode=GPIO_MODE_OUTPUT_OD;
	HAL_GPIO_Init(SDA_Port,&GPIOInitStruct);
}
void SDA_IN(void)
{
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.Pin=SDA_Pin;
	GPIOInitStruct.Pull=GPIO_NOPULL;
	GPIOInitStruct.Speed=GPIO_SPEED_MEDIUM;
	GPIOInitStruct.Mode=GPIO_MODE_INPUT;
	HAL_GPIO_Init(SDA_Port,&GPIOInitStruct);
}
void IIC_Delay(void)
{
	uint16_t i;
	for(i=0;i<1000;i++)
	{
	__nop();
	__nop();
	__nop();
	__nop();
	}
	//HAL_Delay(1);

}
/*IIC GPIO Initial*/
void IIC_GPIO_Init(void)
{
		SCL_GPIO_CLK_EN;
		SDA_GPIO_CLK_EN;
		GPIO_InitTypeDef GPIOInitStruct;
		/*因为是IIC所以可以直接选择OD门可以直接读写但是要上拉电阻*/
		/*Because it is an IIC, you can directly select the OD gate,
			you can read and write directly, but you need a pull-up resistor.*/
		/* Initial SCL PIN */
		GPIOInitStruct.Mode=GPIO_MODE_OUTPUT_OD;
		GPIOInitStruct.Pin=SCL_Pin;
		GPIOInitStruct.Pull=GPIO_NOPULL;
		GPIOInitStruct.Speed=GPIO_SPEED_MEDIUM;
		HAL_GPIO_Init(SCL_Port,&GPIOInitStruct);
		/* Initial SDA PIN */
		GPIOInitStruct.Mode=GPIO_MODE_OUTPUT_OD;
		GPIOInitStruct.Pin=SDA_Pin;
		GPIOInitStruct.Pull=GPIO_NOPULL;
		GPIOInitStruct.Speed=GPIO_SPEED_MEDIUM;
		HAL_GPIO_Init(SDA_Port,&GPIOInitStruct);
}

void IIC_Start(void)
{	
		SDA_OUT();
    SDA_h;
    SCL_h;
		IIC_Delay();
    SDA_l;
}
void  IIC_Stop(void)
{
    SDA_OUT();
    SDA_l;
    SCL_h;
		IIC_Delay();
    SDA_h;
}
/*
 * IIC读取8bit数据
 */
u_int8_t IIC_Read(void)
{
    u_int8_t Data;
		/*easy to be pulled down*/
		SDA_h;
		SDA_IN();
    for (int i = 0; i < 8; ++i) {
        Data<<=1;
        SCL_l;
				IIC_Delay();
				SCL_h; 
        if(R_SDA==1)
            Data|=0X01;
        
				IIC_Delay();
			
    }
		SDA_OUT();
    // ACK Signal
    SCL_l;
		IIC_Delay();
    SDA_l;
		IIC_Delay();
    SCL_h;
		IIC_Delay();
		SCL_l;
		IIC_Delay();
    return Data;
}
/*
 * IIC 写8bit数据
 * 返回值ACK信号
 */
u_int8_t IIC_Write(u_int8_t Data)
{
		
    // 设置一个wait等待ack信号
	 SDA_OUT();
	 #ifdef ACK
    u_int8_t wait=0;
   #endif
    for (int i = 0; i < 8; ++i) {
        SCL_l;
				IIC_Delay();
        if((Data&0X80)==0X80)
            SDA_h;
        else
            SDA_l;
        //Data左移一位
        Data<<=1;
        SCL_h;
				IIC_Delay();
    }
    SCL_l;
		IIC_Delay();
    SDA_h;
		IIC_Delay();
    SCL_h;
		
		IIC_Delay();
		#ifdef ACK
		SDA_IN();
    while(R_SDA)
    {
				IIC_Delay();
        wait++;
        if(wait==255)
        {
            //超时无应答关闭本次传输
          //  IIC_Stop();
          
            return 1;
        }
    }
		
		#endif
    SCL_l;
    IIC_Delay(); 
    return 0;
}
/*
 *  IIC_DUT_W(u_int8_t DUT_ADDR,u_int8_t REG,u_int16_t Data)
 *  DUT ADDR 代表器件的地址 IIC总线上会有很多器件，如何确定他的地址通过
 *  DUT_ADDR 来锁定器件地址
 *  REG 代表CSD203的寄存器地址
 *  Data 代表要写入寄存器的数据
 */
void IIC_DUT_W(u_int8_t DUT_ADDR,u_int8_t REG,u_int16_t Data)
{
    u_int16_t DataH,DataL;
  
    //屏蔽掉高8位只保留低8位
    DataL=Data&0X00ff;
	  //将高8位向右移8位
    DataH=Data>>8;
    //将最后1个bit设置为0表示对
    //这个地址写数据
		DUT_ADDR<<=1;
    DUT_ADDR=DUT_ADDR&0XFE;
		//最高位要写1
	
    IIC_Start();
    IIC_Write(DUT_ADDR);
    IIC_Write(REG);
    IIC_Write(DataH);
    IIC_Write(DataL);
    IIC_Stop();
}
/*
 * IIC 根据地址读取16bit 数据
 */
u_int16_t IIC_DUT_R(u_int8_t DUT_ADDR,u_int8_t REG)
{
    u_int16_t Data;
    //将最后1个bit设置为1表示对
    //这个地址读数据
		DUT_ADDR<<=1;
    IIC_Start();
    IIC_Write(DUT_ADDR);
		IIC_Write(REG);
		
	
		IIC_Start();
		DUT_ADDR|=0x01;
		IIC_Write(DUT_ADDR);
	
    Data=IIC_Read();
    //将数据往上移8bit
    Data<<=8;
    Data|=IIC_Read();
    IIC_Stop();
    return Data;
}
