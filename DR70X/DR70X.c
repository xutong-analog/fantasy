#include "main.h"
#include "thread.h"
#include "GPIO.H"
#include "DR70X.h"
#include "Drive_time.h"
#include "drive_spi.h"

void delay(uint16_t n)
{
	uint32_t i = 25;
	while(i --);
}

void DR70x_Init(void)
{
	SLEEP_LOW;
	delay(1000);
	SLEEP_HIGH;           //nSleep high to power on DR70xQ
	MODE_LOW;             //Control Interface: Mode_0: PH/EN;  Mode_1:Independent PWM Control Interface; Mode_2 Hiz: Standard PWM
	TimePwm.Instance = 14;//PC12 IN2_EN
	TimePwm.Period = 0x5dc0; 
	TimePwm.Pulse = 0x32;
	Timex_Init(TimePwm.Instance);//24khz 50%pulse
	TimePwm.Instance = 16;//PB8 IN1_PH
	Timex_Init(TimePwm.Instance);//24khz
}

/*Mode_0: Take PH/EN control (MODE_LOW) as an example. other mode, pleaes refer to Table 14/15 in datasheet*/
//////////////////////////////////////////////////////
void DR70x_Mode0_Brake(void)
{
	TimePwm.Instance = 16;//PC12 IN2_EN
	TimePwm.Pulse = 0;
	Timex_Start(TimePwm.Instance);
}

void DR70x_Mode0_Reverse(uint8_t pulse)
{
	TimePwm.Instance = 14;//PB8 IN1_EN
	TimePwm.Pulse = 0;
	Timex_Start(TimePwm.Instance);
	
	TimePwm.Instance = 16;//PC12 IN2_EN
	TimePwm.Pulse = pulse;
	Timex_Start(TimePwm.Instance);
}

void DR70x_Mode0_Forward(uint8_t pulse)
{
	TimePwm.Instance = 14;//PB8 IN1_EN
	TimePwm.Pulse = 100;
	Timex_Start(TimePwm.Instance);
	
	TimePwm.Instance = 16;//PC12 IN2_EN
	TimePwm.Pulse = pulse;
	Timex_Start(TimePwm.Instance);
}

//////////////////////////////////////////////////////


void DR70x_Transmit(uint8_t addess, uint8_t data)
{
		uint8_t buff[2] = {0,0},buff1[2];

		buff[0] = (addess << 3);
		buff[1] = data;
		DR703_SPI_TransmitReceive(buff,buff1,2);
}

uint8_t DR70x_Recive(uint8_t addess)
{
		uint8_t buff[2] = {0,0},buff1[2];

		buff[0] = (addess << 3) + 0x80;
		DR703_SPI_TransmitReceive(buff,buff1,2);
		return buff1[1];
}

