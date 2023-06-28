#include "adx923q.h"
#define PI 3.1415926
uint8_t FIFO_Depth = 10;
Ac_Loff_Data_Format ADX92XQ_Acloff_Data = {0};
Data_Format ADX92XQ_Data_Buff = {0};
extern SPI_HandleTypeDef hspi1;
uint16_t lead_count = 1, sin_flag = 0, cos_flag = 0, adc_flag = 0;
extern uint8_t Pace_Mode_Flag;

#pragma - O0
void Delayus(uint16_t a)
{
	a = a * 5;
	while (a--)
		;
}
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	uint64_t CH1_IQDEM_AMP = 0, CH2_IQDEM_AMP = 0;

	Delayus(4);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	ADX92XQ_ReadData_fifo();
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
}
void ADX92XQ_AC_Leadoff_Init(uint32_t threshold)
{
	uint8_t hold_buf[3] = {0x00, 0x00, 0x00};
	hold_buf[0] = threshold & 0xff;
	hold_buf[1] = (threshold & 0xff00) >> 8;
	hold_buf[2] = (threshold & 0xff0000) >> 16;
	ADX92XQ_REG(ADX92XQ_WREG | LOFF, FLEAD_OFF_AC);
	ADX92XQ_REG(ADX92XQ_WREG | GPIO, AC_AMP_SCALE_DIV8);
	ADX92XQ_REG(ADX92XQ_WREG | CONFIG3, AC_MODE_HARD);
	ADX92XQ_REG(ADX92XQ_WREG | LOFF_RLD, EMUX2_VDD_CON_P | EMUX2_VSS_CON_N);
	ADX92XQ_REG(ADX92XQ_WREG | LOFF_AC1, SQUARE_WAVE_SIN | ACDIV_FACTOR | ACDIV_FRQ4KHz);
	ADX92XQ_REG(ADX92XQ_WREG | LON_CFG, DEBOUNCE_117 | AC_EXCT_THD_20nA); //
	ADX92XQ_REG(ADX92XQ_WREG | EPMIX_CFG, AC_CMP_CFG_AC_24 | FSEL_1024K); //
	ADX92XQ_REG_Stream(ADX92XQ_WREG, AC_CMP_THD0, 3, hold_buf);
}
uint8_t ADX92XQ_Init(void)
{
	uint8_t device_id;
	DVDD_EN(GPIO_PIN_SET);
	AVCC_EN(GPIO_PIN_SET);
	XTAL_DIS;
	InternalCLK;
	NSS_H;
	PWDN_H;
	START_L;
	HAL_Delay(10);
	PWDN_L;
	HAL_Delay(30);
	PWDN_H;
	HAL_Delay(30);
	ADX92XQ_CMD(ADX92XQ_SDATAC);
	device_id = ADX92XQ_REG(ADX92XQ_RREG | ECG_ID, 0X00);
	AUTO_Printf(" device_id = 0X%02X \r\n", device_id);
	while (device_id != 0xF3)
	{
		device_id = ADX92XQ_REG(ADX92XQ_RREG | ECG_ID, 0X00);
		HAL_Delay(20);
	}
	return device_id;
}
void ADX92XQ_Config(void)
{
	uint8_t reg_data[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, RESP_CLK_HALF_DIV2};//呼吸时钟减半

	ADX92XQ_CMD(ADX92XQ_SDATAC);
	/********SYSTEM********/
	ADX92XQ_REG_Stream(ADX92XQ_WREG, AC_CMP_THD0, 10, reg_data); //流写入后10个寄存器
	ADX92XQ_REG(ADX92XQ_WREG | CONFIG2, 0X80 | PDB_REFBUF_EN | PDB_LOFF_COMP_EN);
	ADX92XQ_REG(ADX92XQ_WREG | GPIO, GPIO2_IN | GPIO1_IN);
	ADX92XQ_REG(ADX92XQ_WREG | LON_CFG, DEBOUNCE_117);//LEAD OFF开启 117ms滤波器
	ADX92XQ_REG(ADX92XQ_WREG | ERM_CFG, WMODE);
	ADX92XQ_REG(ADX92XQ_WREG | EPMIX_CFG, FSEL_1024K);//配置系统时钟为1024K
	/********ADC********/
	ADX92XQ_REG(ADX92XQ_WREG | CONFIG1, DR_250); // 1024K时钟下的500sps
	ADX92XQ_REG(ADX92XQ_WREG | CH1SET, PD_EN | GAIN6 | MUX_NORMAL);
	ADX92XQ_REG(ADX92XQ_WREG | CH2SET, PD_EN | GAIN6 | MUX_NORMAL);
	ADX92XQ_REG(ADX92XQ_WREG | RLD_SENS, PDB_RLD_EN | RLD1N_CON | RLD1P_CON); //RLD打开并连接至CH1
	/********LEAD OFF********/
	ADX92XQ_REG(ADX92XQ_WREG | LOFF, 0xfd & (COMP_TH_70 | 0x10));// DC LEAD OFF比较器阈值
	ADX92XQ_REG(ADX92XQ_WREG | LOFF_SENSE, EMUX1_VSS_CON_P | EMUX1_VDD_CON_N);
	ADX92XQ_REG(ADX92XQ_WREG | LOFF_RLD, EMUX2_VSS_CON_P | EMUX2_VDD_CON_N);
	ADX92XQ_REG(ADX92XQ_WREG | LOFF_ISETP, CUR_LEVEL_EN | ISTEP_nA(4.4));//4.4nA LEAD OFF电流
	/********RES********/
	ADX92XQ_REG(ADX92XQ_WREG | RESP1, RESP_DEMOD_ON | RESP_MOD_ON | RESP_PH_112 | 0x02);
	ADX92XQ_REG(ADX92XQ_WREG | RESP2, CALIB_ON | RESP_FREQ_DIV2 | RLDREF_INT | 0x01);
	/********FIFO********/
	ADX92XQ_REG(ADX92XQ_WREG | FIFO_CFG1, FRAME_CFG_2CH_ECG | FIFO_EN);
	ADX92XQ_REG(ADX92XQ_WREG | FIFO_CFG2, STATUS_SEL_GPIO1_2 | DEPTH(FIFO_Depth));
	/********PACE********/
	ADX92XQ_REG(ADX92XQ_WREG | CONFIG4, RLDIN2RAMPP_CON);
	ADX92XQ_REG(ADX92XQ_WREG | PACE_CFG, PACE_MUX_IN2 | PACE_GAIN_4 | PACEOUT_ON_EN | PACE_EN);
	/********************/
	START_H;
	ADX92XQ_CMD(ADX92XQ_OFFSETCAL); //自矫正
	HAL_Delay(200);
	START_L;

	__HAL_GPIO_EXTI_CLEAR_FALLING_IT(GPIO_PIN_9);
	HAL_Delay(10);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}
void ADX92XQ_CMD(uint8_t cmd)
{
	NSS_L;
	Delayus(4);
	ADX92XQ_SPI_RW(cmd, 1);
	Delayus(4);
	NSS_H;
	Delayus(4);
}
uint8_t ADX92XQ_SPI_RW(uint8_t data, uint8_t len)
{
	uint8_t rx_data = 0;
	HAL_SPI_TransmitReceive(&hspi1, &data, &rx_data, len, 10);
	Delayus(4);
	return rx_data;
}
void ADX92XQ_ReadReg(uint8_t *cmd, uint8_t *data, uint8_t size)
{
	uint8_t i = 0;
	NSS_L;
	Delayus(4);
	ADX92XQ_SPI_RW(cmd[0], 1);
	ADX92XQ_SPI_RW(cmd[1], 1);
	for (i = 0; i < size; i++)
		HAL_SPI_TransmitReceive(&hspi1, &cmd[2] + i, data + i, 1, 10);
	Delayus(4);
	NSS_H;
}
uint8_t ADX92XQ_REG(uint8_t cmd, uint8_t data)
{
	uint8_t rx_data = 0;
	NSS_L;
	ADX92XQ_SPI_RW(cmd, 1);
	ADX92XQ_SPI_RW(0X00, 1);
	if ((cmd & 0x20) == 0x20)
		rx_data = ADX92XQ_SPI_RW(0X00, 1);
	else
		rx_data = ADX92XQ_SPI_RW(data, 1);
	NSS_H;
	return rx_data;
}
uint8_t ADX92XQ_REG_Stream(uint8_t CMD, uint8_t StartAddr, uint8_t StopAddrNum, uint8_t *data)
{
	static uint8_t rx_data[33] = {0};
	uint8_t j = 0, Size = 1, i = 0;
	NSS_L;
	ADX92XQ_SPI_RW(CMD | StartAddr, 1);
	ADX92XQ_SPI_RW(0x1f & (StopAddrNum - 1), 1);
	if ((CMD & 0x20) == 0x20)
	{
		if (hspi1.State != HAL_SPI_STATE_BUSY_RX)
		{
			hspi1.State = HAL_SPI_STATE_BUSY_TX_RX;
		}
		for (j = 0; j < StopAddrNum; j++)
		{
			hspi1.ErrorCode = HAL_SPI_ERROR_NONE;
			hspi1.pRxBuffPtr = &data[j];
			hspi1.RxXferCount = Size;
			hspi1.RxXferSize = Size;
			hspi1.pTxBuffPtr = &i;
			hspi1.TxXferCount = Size;
			hspi1.TxXferSize = Size;
			*((__IO uint8_t *)&hspi1.Instance->DR) = (*hspi1.pTxBuffPtr);
			while (1)
			{
				if ((__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE)) && (hspi1.RxXferCount > 0U))
				{
					(*(uint8_t *)hspi1.pRxBuffPtr) = *(__IO uint8_t *)&hspi1.Instance->DR;
					break;
				}
			}
			hspi1.State = HAL_SPI_STATE_READY;
			Delayus(2);
		}
	}
	else
		i = HAL_SPI_TransmitReceive(&hspi1, data, rx_data, StopAddrNum, 10); //д�Ĵ���
	NSS_H;
	return i;
}
void ADX92XQ_ReadData(void)
{
	__disable_irq();
	uint8_t tempread[9] = {0}, tempbuff[11] = {0};
	tempbuff[9] = 0x0D;
	tempbuff[10] = 0x0A;
	NSS_L;
	HAL_SPI_TransmitReceive(&hspi1, tempbuff, tempbuff, 9, 10);
	ADX92XQ_Data_Buff.Header = (0XF0 & tempbuff[0]) >> 4;
	ADX92XQ_Data_Buff.LEAD_OFF = ((0X0F & tempbuff[0]) << 1) | ((0x80 & tempbuff[1]) >> 7);
	ADX92XQ_Data_Buff.A92X_GPIO = (0X60 & tempbuff[1]) >> 5;
	ADX92XQ_Data_Buff.DATA_1CH = s24tos32((tempbuff[3] << 16) | (tempbuff[4] << 8) | tempbuff[5]);
	ADX92XQ_Data_Buff.DATA_2CH = s24tos32((tempbuff[6] << 16) | (tempbuff[7] << 8) | tempbuff[8]);
	NSS_H;
	AUTO_Printf_DATA(tempbuff, 11);
	__enable_irq();
}
void ADX92XQ_ReadData_fifo(void)
{
	static uint8_t tempbuff[111] = {0};
	uint8_t reg_data[32] = {0};

	uint8_t *tdata;
	uint8_t j = 0, Size = 1, i = 0;
	NSS_L;
	ADX92XQ_SPI_RW(ADX92XQ_RFIFO, 1);
	ADX92XQ_SPI_RW(ADX92XQ_RFIFO_Item(FIFO_Depth) - 1, 1);
	if (hspi1.State != HAL_SPI_STATE_BUSY_RX)
	{
		hspi1.State = HAL_SPI_STATE_BUSY_TX_RX;
	}
	for (j = 0; j < FIFO_Depth * 7; j++)
	{
		hspi1.ErrorCode = HAL_SPI_ERROR_NONE;
		hspi1.pRxBuffPtr = &tempbuff[j];
		hspi1.RxXferCount = Size;
		hspi1.RxXferSize = Size;
		hspi1.pTxBuffPtr = &i;
		hspi1.TxXferCount = Size;
		hspi1.TxXferSize = Size;
		*((__IO uint8_t *)&hspi1.Instance->DR) = (*hspi1.pTxBuffPtr);
		while (1)
		{
			if ((__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE)) && (hspi1.RxXferCount > 0U))
			{
				(*(uint8_t *)hspi1.pRxBuffPtr) = *(__IO uint8_t *)&hspi1.Instance->DR;
				break;
			}
		}
		hspi1.State = HAL_SPI_STATE_READY;
		Delayus(2);
	}
	NSS_H;
	tdata = FIFO_data_transposition(tempbuff, FIFO_Depth);
	AUTO_Printf_DATA(tdata, FIFO_Depth * 11);
}
uint8_t *FIFO_data_transposition(uint8_t *pRxData, uint8_t Item)
{
	static uint8_t buff[111] = {0};
	uint8_t j = 0, i = 0, pace_puls = 0;
	if (Pace_Mode_Flag == ENABLE)
	{
		if (GPIO2 == ENABLE) //当pace_puls为高时
		{
			pace_puls = 1;
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
			GPIO1_H; //复位RS触发器
			Delayus(10);
			GPIO1_L;
		}
		else
		{
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
		}
		for (j = 0; j < Item; j++)
		{
			i = j * 11;
			buff[0 + i] = 0xc0 | (((*pRxData) & 0xf0) >> 4);
			buff[1 + i] = (((*pRxData) & 0x08) << 4) | (((*pRxData & 0x01) | (pace_puls << 1)) << 5);
			buff[2 + i] = 0x00;
			buff[3 + i] = *++pRxData;
			buff[4 + i] = *++pRxData;
			buff[5 + i] = *++pRxData;
			buff[6 + i] = *++pRxData;
			buff[7 + i] = *++pRxData;
			buff[8 + i] = *++pRxData;
			buff[9 + i] = 0x0D;
			buff[10 + i] = 0x0A;
			pRxData++;
		}
	}
	else
	{
		for (j = 0; j < Item; j++)
		{
			i = j * 11;
			buff[0 + i] = 0xc0 | (((*pRxData) & 0xf0) >> 4);
			buff[1 + i] = (((*pRxData) & 0x08) << 4) | (((*pRxData) & 0x03) << 5);
			buff[2 + i] = 0x00;
			buff[3 + i] = *++pRxData;
			buff[4 + i] = *++pRxData;
			buff[5 + i] = *++pRxData;
			buff[6 + i] = *++pRxData;
			buff[7 + i] = *++pRxData;
			buff[8 + i] = *++pRxData;
			buff[9 + i] = 0x0D;
			buff[10 + i] = 0x0A;
			pRxData++;
		}
	}
	return buff;
}
void ShellSort(uint16_t *arr, uint16_t size)
{
	int i = 0, j = 0, tmp = 0, increment = 0;
	for (increment = size / 2; increment > 0; increment /= 2)
	{
		for (i = increment; i < size; i++)
		{
			tmp = arr[i];
			for (j = i - increment; j >= 0 && tmp < arr[j]; j -= increment)
			{
				arr[j + increment] = arr[j];
			}
			arr[j + increment] = tmp;
		}
	}
}
int32_t s24tos32(uint32_t data)
{
	if ((data & 0x800000) == 0x800000)
	{
		data |= 0xff000000;
	}
	return data;
}
