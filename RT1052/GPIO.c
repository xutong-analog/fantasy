void User_GPIO_Init(void)
{
  //选择为GPIO 不使用SION功能
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_GPIO1_IO10,0u);
  //先设置GPIO的引脚，再设置GPIO的电气属性,使用了野火的PAD参数，因为本身的库
  //写的参数让人看的不是很明白
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_10_GPIO1_IO10,LED_PAD_CONFIG_DATA);
  //配置输入输出模式
  gpio_pin_config_t gpio_cfg;
  gpio_cfg.direction=kGPIO_DigitalOutput;
  gpio_cfg.outputLogic=1;
  gpio_cfg.interruptMode=kGPIO_NoIntmode;
  //第一步先GPIO
  //第二步选PIN PIN Number 是多少就多少U
  //第三步 代入参数
  GPIO_PinInit(GPIO1,10u,&gpio_cfg);
}
