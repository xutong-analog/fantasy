#ifndef _I2C_H_
#define _I2C_H_

#define SCL_L					
#define SCL_H					
#define SDA_L					
#define SDA_H					
#define SDA_READ			
#define ALERT_READ		


void I2C_Initializes(void);
uint16_t IIC_WriteByte(uint8_t chipAddess,uint16_t writeAddr, uint8_t *pbuff,uint16_t size);
uint16_t IIC_ReadByte(uint8_t chipAddess,uint8_t readAddess,uint8_t *pbuff,uint16_t size);
void I2C_OpenHighspeed(void);

#endif
