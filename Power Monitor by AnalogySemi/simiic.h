#ifndef __IIC_H
#define __IIC_H

/* include mcu lib*/
#include "stm32f4xx_hal.h"

/*define whether to ack */

#define ACK

/*define direction*/
/*重定向定义*/
#define u_int8_t 		uint8_t
#define u_int16_t 	uint16_t

/*define control gpio*/
/*定义控制的GPIO*/
#define SCL_GPIO_CLK_EN   __HAL_RCC_GPIOC_CLK_ENABLE()
#define SCL_Port  GPIOC
#define SCL_Pin		GPIO_PIN_10
#define SDA_GPIO_CLK_EN   __HAL_RCC_GPIOC_CLK_ENABLE()
#define SDA_Port  GPIOC
#define SDA_Pin		GPIO_PIN_11

/* IIC Control pin*/
/* IIC 控制引脚 */
#define SCL_h 			HAL_GPIO_WritePin(SCL_Port,SCL_Pin,GPIO_PIN_SET)
#define SCL_l 			HAL_GPIO_WritePin(SCL_Port,SCL_Pin,GPIO_PIN_RESET)
#define SDA_h 			HAL_GPIO_WritePin(SDA_Port,SDA_Pin,GPIO_PIN_SET)
#define SDA_l 			HAL_GPIO_WritePin(SDA_Port,SDA_Pin,GPIO_PIN_RESET)

#define R_SDA 			HAL_GPIO_ReadPin(SDA_Port,SDA_Pin)

void IIC_GPIO_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
//返回值是ACK信号，
//若是有ACK信号则返回0,若是没有ACK信号则返回1
u_int8_t IIC_Write(u_int8_t Data);
void IIC_DUT_W(u_int8_t DUT_ADDR,u_int8_t REG,u_int16_t Data);
u_int16_t IIC_DUT_R(u_int8_t DUT_ADDR,u_int8_t REG);
u_int8_t IIC_Read(void);

#endif

