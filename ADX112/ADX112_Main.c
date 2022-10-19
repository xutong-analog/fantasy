int main(void)
{
	
	ADX112_InitTypeDef ADX112_Init;
	uint16_t ADC_Value;
  HAL_Init();
  SystemClock_Config();

  ADX112_Init.MUX=MUX_PA0_NA3;
  ADX112_Init.PGA_GAIN=PGA_GAIN_6_144;
  ADX112_Init.DR= DR_16SPS;
  ADX112_Init.MODE=MODE_CONTIUOUS;
  ADX112_Init.PULL_UP_DOUT=PULL_UP_DOUT_PullupEn;
  ADX112_Init.Single_Conversion=Single_Conversion_DIS;
  ADX112_Init.TS_MODE=TS_MODE_ADC;
  while (1)
  {

    /* USER CODE END WHILE */
		ADC_Value=ADX112_Get_ADValue(&ADX112_Init);
		HAL_Delay(500);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
