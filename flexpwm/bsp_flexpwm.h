
#ifndef __BSP_FLEXPWM_H
#define __BSP_FLEXPWM_H
#include "fsl_pwm.h"
/*
    PWM GPIO的配置
      // PWM_pin Config
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_FLEXPWM1_PWMA00, 0U); 
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_FLEXPWM1_PWMB00, 0U); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_01_FLEXPWM1_PWMB00, PWM_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_00_FLEXPWM1_PWMA00, PWM_PAD_CONFIG_DATA);
*/


// 发出PWM 波形的指令
//PWM_StartTimer(PWM1, kPWM_Control_Module_0 );
//设置PWM占空比 高精度设置，范围0~65535
/* 
  PWM_UpdatePwmDutycycleHighAccuracy(
  PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwmSignal, pwm_mode_t currPwmMode, uint16_t dutyCycle)

  example:
  
  PWM_UpdatePwmDutycycleHighAccuracy(
  PWM1,kPWM_Module_0, kPWM_PwmA,kPWM_SignedCenterAligned,1000);
  //更新duty cycle 后需要使用set pwm ldok加载
  PWM_SetPwmLdok(PWM1, kPWM_Control_Module_0, true);
*/
//PWM 源时钟 12000000 代表IPG时钟是12Mhz
#define PWM_SRC_CLK_FREQ CLOCK_GetFreq(kCLOCK_IpgClk)
//设置PWM频率
#define AS_PWM_FREQ 300UL
//初始化RT1052 PWM输出
void RT1052_PWM_Init(void);

#endif /* __BSP_LPSPI_H */

