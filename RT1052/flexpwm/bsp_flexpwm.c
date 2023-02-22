#include "fsl_iomuxc.h"
#include "fsl_gpio.h" 
#include "fsl_pwm.h"
#include "pad_config.h" 
#include "bsp_flexpwm.h"
#include "fsl_xbara.h"
//初始化PWM 模块
void RT1052_PWM_Init(void)
{
    pwm_signal_param_t pwmSignal[2];
    //步骤3：设置pwm的时钟，pwm的时钟来自ipg
    //在这里设置ipg的分频 ，设置为0时候是12Mhz的ipg时钟
    //CLOCK_SetDiv(kCLOCK_IpgDiv, 0x03); // Set IPG 12Mhz 时钟
    XBARA_Init(XBARA1);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1Fault0);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1Fault1);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1234Fault2);
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1234Fault3);
    /* pwm default config
    * config->enableDebugMode = false;
    * config->enableWait = false;
    * config->reloadSelect = kPWM_LocalReload;
    * config->clockSource = kPWM_BusClock;
    * config->prescale = kPWM_Prescale_Divide_1;
    * config->initializationControl = kPWM_Initialize_LocalSync;
    * config->forceTrigger = kPWM_Force_Local;
    * config->reloadFrequency = kPWM_LoadEveryOportunity;
    * config->reloadLogic = kPWM_ReloadImmediate;
    * config->pairOperation = kPWM_Independent;
    */
    pwm_config_t config;
    //使用default的配置
    PWM_GetDefaultConfig(&config);
    /* 修改默认配置参数 */
    /*新值在上一个pwm周期输出结束之后加载到缓冲寄存器中*/
    config.reloadLogic = kPWM_ReloadPwmFullCycle;
    /*PwmA 和 PwmB 作为互补通道，PwmA 作为主通道*/
    // 独立通道设置 kPWM_Independent 
    // 主通道设置 kPWM_ComplementaryPwmA
    
    config.pairOperation = kPWM_Independent;
    config.prescale = kPWM_Prescale_Divide_128;
    config.enableDebugMode = true; // 使能DebugMode
    //配置PWM1
    PWM_Init(PWM1,kPWM_Module_0,&config);
    /*配置pwm 参数*/
    pwmSignal[0].pwmChannel = kPWM_PwmA; //指定pwm 通道
    pwmSignal[0].level = kPWM_HighTrue; //设置输出极性
    pwmSignal[0].dutyCyclePercent=0;//设置 pwm的占空比
    pwmSignal[0].deadtimeValue = 0; //设定死区值
    pwmSignal[1].pwmChannel = kPWM_PwmB;
    pwmSignal[1].level = kPWM_HighTrue;
    pwmSignal[1].dutyCyclePercent = 0;
    pwmSignal[1].deadtimeValue = 0;
    /*设置pwm 参数，包括pwm 的频率 占空比，死区时间等*/
    PWM_SetupPwm(PWM1, kPWM_Module_0, pwmSignal, 2,\
    kPWM_SignedEdgeAligned, AS_PWM_FREQ,PWM_SRC_CLK_FREQ);
    /*设置Set LDOK 位，将初始化参数加载到相应的寄存器*/
    PWM_SetPwmLdok(PWM1, kPWM_Control_Module_0 , true);
    //开始发波
    PWM_StartTimer(PWM1, kPWM_Control_Module_0 );
}
