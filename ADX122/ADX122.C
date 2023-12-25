#include "adx122.h"
//ADX122 supply voltage 2 - 5.5V
//analog input voltage max VDD+0.3V.    VIN<VDD!!!!!
//(VDD-->3v3,PGA-->4096,)无法获得满量程ADC输出代码,这种意味着一些动态范围的丢失.
/***************************************************************************************************
 * 函 数 名 称：ADX122_ADC_Continuous_Init
 * 函 数 说 明：初始化ADX122
 * 函 数 形 参：channel = ADC外部通道选择,PGA = ADC满量程选择,SPS = ADC数据传输率选择
 * 函 数 返 回：无
 * 作       者：gugugu
 * 备       注：连续模式使用前，调用此函数完成初始化，之后调用ADX122_Get_ADC_Continuous_Data()连续读取数据
***************************************************************************************************/
void ADX122_ADC_Continuous_Init(uint16_t channel,uint16_t PGA,uint16_t SPS,uint16_t FILT,uint16_t SDCS)
{
	//MySPI_Init();
	uint32_t Txdata;
	LPSPI_Init();//初始化SPI
	ADX122_ENABLE;//拉低CS开始通信
	Txdata = (ADX122_SS_START|channel|PGA|ADX122_Continuous_MODE|SPS|ADX122_PUUP_EN|ADX122_NOP_UPDATA);//16BIT SET CONFIG REGISTER
	Txdata = (Txdata<<4)|((FILT|SDCS)>>12);//(16BIT << 4)|CONFIG_EXTRA = 20BIT
	Lpspi_Write(1,(uint8_t)(Txdata>>12));//发送20位数据高8位数据
	Lpspi_Write(1,(uint8_t)(Txdata>>4));//发送20位中8位数据
	Lpspi_Write(1,(uint8_t)(Txdata<<4));//发送20位低4位数据
	Spi_delay(30);
	Lpspi_Stop();//拉高CS复位ADX122结束通信
	Spi_delay(30);
}
/***************************************************************************************************
 * 函 数 名 称：ADX122_ADC_Continuous_Init
 * 函 数 说 明：初始化ADX122
 * 函 数 形 参：channel = ADC外部通道选择,PGA = ADC满量程选择,SPS = ADC数据传输率选择
 * 函 数 返 回：无
 * 作       者：gugugu
 * 备       注：连续模式使用前，调用此函数完成初始化，之后调用ADX122_Get_ADC_Continuous_Data()连续读取数据
***************************************************************************************************/
void ADX122_Sigle_SHOT_Init()
{
	LPSPI_Init();//初始化SPI
}
/******************************************************************
 * 函 数 名 称：ADX122_Get_ADC_SIGLE_SHOT_Data
 * 函 数 说 明：单次获取AD电压值(mv)
 * 函 数 形 参：channel = ADC外部通道选择,PGA = ADC满量程选择,SPS = ADC数据传输率选择
 * 函 数 返 回：AD电压值(mv)
 * 作       者：gugugu
 * 备       注：
******************************************************************/
float ADX122_Get_ADC_SIGLE_SHOT_Data(uint16_t channel,uint16_t PGA,uint16_t SPS,uint16_t FILT,uint16_t SDCS)
{
	uint8_t Adc_Data_H=0;
	uint8_t Adc_Data_M=0;
	uint8_t Adc_Data_L=0;
	uint32_t Adc_Data=0;
	uint32_t TXdata=0;
	float Tempture_data=0;
	ADX122_ENABLE;//拉低CS开始通信
	Spi_delay(30);
	TXdata = (ADX122_SS_START|channel|PGA|ADX122_Sigle_SHOT_MODE|SPS|ADX122_PUUP_EN|ADX122_NOP_UPDATA);//16BIT SET CONFIG REGISTER
	TXdata = (TXdata<<4)|((FILT|SDCS)>>12);//(16BIT << 4)|CONFIG_EXTRA = 20BIT
	Lpspi_Write(1,(uint8_t)(TXdata>>12));//发送20位数据高8位数据
	Lpspi_Write(1,(uint8_t)(TXdata>>4));//发送20位中8位数据
	Lpspi_Write(1,(uint8_t)(TXdata<<4));//发送20位低4位数据
	Spi_delay(30);
	ADX122_DISABLE;//拉高CS复位ADX122结束通信
	Spi_delay(30);
	ADX122_ENABLE;//拉低CS开始通信
	Spi_delay(30);
	//while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6));//DOUT拉低ADC1118数据更新准备完毕
    while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6));//DOUT拉低ADC1118数据更新准备完毕
    TXdata = (ADX122_SS_START|channel|PGA|ADX122_Sigle_SHOT_MODE|SPS|ADX122_PUUP_EN|ADX122_NOP_UPDATA);//16BIT SET CONFIG REGISTER
	TXdata = (TXdata<<4)|((FILT|SDCS)>>12);//(16BIT << 4)|(CONFIG_EXTRA>>12) = 20BIT 
	Adc_Data_H = Lpspi_Read(1,(uint8_t)(TXdata>>12));
	Adc_Data_M = Lpspi_Read(1,(uint8_t)(TXdata>>4));
	Adc_Data_L= Lpspi_Read(1,(uint8_t)(TXdata<<4));
	Spi_delay(30);
    ADX122_DISABLE;//拉高CS复位ADX122结束通信
	Adc_Data = (((Adc_Data_H<<16)|(Adc_Data_M<<8)|(Adc_Data_M))>>4);//读24bit数据转换20位adc数据
	if(Adc_Data&0X80000)//MSB=1-->负数需要转换
	{
		Adc_Data = (~Adc_Data);
		Adc_Data = Adc_Data&0x7ffff;
		if(PGA == ADX122_PGA_6144)Tempture_data=Adc_Data*0.01171875;
		else if(PGA == ADX122_PGA_4096)Tempture_data=Adc_Data*0.0078125;
		else if(PGA == ADX122_PGA_2048)Tempture_data=Adc_Data*0.000390625;
		else if(PGA == ADX122_PGA_1024)Tempture_data=Adc_Data*0.0001953125;
		else if(PGA == ADX122_PGA_0512)Tempture_data=Adc_Data*0.00009765625;
		else Tempture_data=Adc_Data*0.000048828125;
		return -(Tempture_data);
	}
	else
	{
		if(PGA == ADX122_PGA_6144)Tempture_data=Adc_Data*0.01171875;
		else if(PGA == ADX122_PGA_4096)Tempture_data=Adc_Data*0.0078125;
		else if(PGA == ADX122_PGA_2048)Tempture_data=Adc_Data*0.00390625;
		else if(PGA == ADX122_PGA_1024)Tempture_data=Adc_Data*0.0001953125;
		else if(PGA == ADX122_PGA_0512)Tempture_data=Adc_Data*0.00009765625;
		else Tempture_data=Adc_Data*0.000048828125;
		return Tempture_data;	
	}
		
}
/***************************************************************************************
 * 函 数 名 称：ADX122_Get_ADC_Continuous_Data
 * 函 数 说 明：连续获取AD电压值
 * 函 数 形 参：channel = ADC外部通道选择,PGA = ADC满量程选择,SPS = ADC数据传输率选择
 * 函 数 返 回：AD电压值(mv)
 * 作       者：gugugu
 * 备       注：使用此函数前调用ADX122_ADC_Continuous_Init()
****************************************************************************************/
float  ADX122_Get_ADC_Continuous_Data(uint16_t channel,uint16_t PGA,uint16_t SPS,uint16_t FILT,uint16_t SDCS)
{
	uint8_t Adc_Data_H=0;
	uint8_t Adc_Data_M=0;
	uint8_t Adc_Data_L=0;
	uint32_t Adc_Data=0;
	uint32_t TXdata=0;
	float Tempture_data;
    ADX122_ENABLE;//拉低CS开始通信
	Spi_delay(3);
	while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6));//DOUT拉低ADC1118数据更新准备完毕
    while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6));//DOUT拉低ADC1118数据更新准备完毕
    TXdata = (ADX122_SS_START|channel|PGA|ADX122_Continuous_MODE|SPS|ADX122_PUUP_EN|ADX122_NOP_UNUPDATA);//16BIT SET CONFIG REGISTER
	TXdata = (TXdata<<4)|((FILT|SDCS)>>12);//(16BIT << 4)|(CONFIG_EXTRA>>12) = 20BIT 
	Adc_Data_H = Lpspi_Read(1,(uint8_t)(TXdata>>12));
	Adc_Data_M = Lpspi_Read(1,(uint8_t)(TXdata>>4));
	Adc_Data_L= Lpspi_Read(1,(uint8_t)(TXdata<<4));
    Spi_delay(30);
    ADX122_DISABLE;//拉高CS复位ADX122结束通信
	Adc_Data = (((Adc_Data_H<<16)|(Adc_Data_M<<8)|(Adc_Data_M))>>4);//读24bit数据转换20位adc数据
	if(Adc_Data&0X80000)//MSB=1-->负数需要转换
	{
		Adc_Data = (~Adc_Data);
		Adc_Data = Adc_Data&0x7ffff;
		if(PGA == ADX122_PGA_6144)Tempture_data=Adc_Data*0.01171875;
		else if(PGA == ADX122_PGA_4096)Tempture_data=Adc_Data*0.0078125;
		else if(PGA == ADX122_PGA_2048)Tempture_data=Adc_Data*0.000390625;
		else if(PGA == ADX122_PGA_1024)Tempture_data=Adc_Data*0.0001953125;
		else if(PGA == ADX122_PGA_0512)Tempture_data=Adc_Data*0.00009765625;
		else Tempture_data=Adc_Data*0.000048828125;
		return -(Tempture_data);
	}
	else
	{
		if(PGA == ADX122_PGA_6144)Tempture_data=Adc_Data*0.01171875;
		else if(PGA == ADX122_PGA_4096)Tempture_data=Adc_Data*0.0078125;
		else if(PGA == ADX122_PGA_2048)Tempture_data=Adc_Data*0.00390625;
		else if(PGA == ADX122_PGA_1024)Tempture_data=Adc_Data*0.0001953125;
		else if(PGA == ADX122_PGA_0512)Tempture_data=Adc_Data*0.00009765625;
		else Tempture_data=Adc_Data*0.000048828125;
		return Tempture_data; 
	}
		
} 
/***************************************************************************************
 * 函 数 名 称：ADX122_Get_ID
 * 函 数 说 明：读取ADX122ID,测试通信
 * 函 数 形 参：无
 * 函 数 返 回：ADX122_Device_ID
 * 作       者：gugugu
 * 备       注：80位数据传输,Device_ID_Register-->16bit,[15-8]-->Device_ID_Value
****************************************************************************************/
uint8_t ADX122_Get_ID(void)
{
	uint16_t Txdata_1;//CONFIG DATA
	uint16_t Txdata_2;//CONFIG_EXTRA DATA
	uint8_t Adx_122_ID=0; 
    ADX122_ENABLE;//拉低CS开始通信
    Spi_delay(30);
    Txdata_1 = (ADX122_SS_START|ADX122_MUX_AIN0|ADX122_PGA_6144|ADX122_Sigle_SHOT_MODE|ADX122_DR_10SPS|ADX122_PUUP_EN|ADX122_NOP_UPDATA);
	Txdata_2 = (ADX122_EN_FILT_50HZ|ADX122_SDCS_Off|ADX122_In_Short_Mux);//16bit
	Lpspi_Write(1,(uint8_t)(Txdata_1>>8));//send 36 bit
	Lpspi_Write(1,(uint8_t)Txdata_1);
	Lpspi_Write(1,(uint8_t)(Txdata_2>>8));
	Lpspi_Write(1,(uint8_t)Txdata_2);
	for(int i=0;i<6;i++)//DIN拉低
	{
		Lpspi_Write(1,(uint8_t)0x00);
	}
	//Spi_delay(30);
	//ADX122_DISABLE;//拉高CS复位ADX122结束通信
	//Spi_delay(30);
	//ADX122_ENABLE;//拉低CS开始通信
	//Spi_delay(30);
	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6));//DOUT拉低ADX122数据更新准备完毕
	Lpspi_Write(1,(uint8_t)(Txdata_1>>8));//send 36 bit
	Lpspi_Write(1,(uint8_t)Txdata_1);
	Lpspi_Write(1,(uint8_t)(Txdata_2>>8));
	Lpspi_Write(1,(uint8_t)Txdata_2);
	for(int i=0;i<6;i++)//DIN拉低
	{
		if(i<4)
		{
			Lpspi_Write(1,(uint8_t)0x00);
		}
		else if(i==4)
		{
			
			Adx_122_ID = Lpspi_Read(1,(uint8_t)0x00);
			Lpspi_Write(1,(uint8_t)0x00);
		}	
	}
	Spi_delay(30);
	ADX122_DISABLE;//拉高CS复位ADX122结束通信
	return Adx_122_ID;
}
