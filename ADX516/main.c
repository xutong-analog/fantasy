
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_gpt.h"
#include "fsl_lpspi.h"
#include "fsl_iomuxc.h"
#include "pad_config.h"  
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_lpi2c.h"
#include "./bsp/nvic/bsp_nvic.h"
#include "./bsp/led/bsp_led.h"
#include "./bsp/key/bsp_key_it.h"
#include "ad5668.h"
#include "fsl_adc.h"

#include "rtthread.h"
#include "bsp_lpspi.h"
#include "bsp_lpi2c.h"
#include "AnalogysemiCSD.h"
//#include "ADX3208.h"
#include "ADX516.h"
#include "bsp_flexpwm.h"
// 添加adc的返回值用于打印
volatile uint16_t ADC_Value;

uint8_t datas[]={0x04,0x9A,0x04,0X9A};
uint8_t Rdatas[2];

/*******************************************************************kkokkkkkkkkkkk
 * Prototypes
 *******************************************************************/
/**
 * @brief 延时一段时间
 */


void delay(uint32_t count);

/*******************************************************************
 * Code
 *******************************************************************/
/**
 * @note 本函数在不同的优化模式下延时时间不同，
 *       如flexspi_nor_debug和flexspi_nor_release版本的程序中，
 *       flexspi_nor_release版本的延时要短得多  
 */ 
void delay(uint32_t count)
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



/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */

 
int main(void)
{
//  uint8_t BusVoltage[8]={0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10};
   uint8_t rxdatas[30];
//  uint8_t Rxdatass[300];
    uint8_t  ID;
   // uint16_t i=0;
    rt_kprintf("hello analogysemi \r\n");	
    User_GPIO_Init();
 
    LPSPI_Init();
    //初始化ADX516
    ADX516_Init();
    
    while(1)
    {  
          
        ID=ADX516_GetChipID();
        rt_kprintf("%d \r\n",ID);
        ADX516_GetAllReg();

        ADX516_GetADC_Value(0x00,rxdatas);
        ADX516_GetADC_Value(0x01,rxdatas);
        ADX516_GetADC_Value(0x02,rxdatas);
        

    }     
    

}


/*********************************************END OF FILE**********************/




