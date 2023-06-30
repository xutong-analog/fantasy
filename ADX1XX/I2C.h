#include "include.h"
#include "i2c.h"

void I2C_delay(void)
{
    //uint16_t t = 10;
    //while(t--);
    //return;
}
uint16_t I2C_Start(void)
{
    //I2C_SDA_OUT();
    I2C_delay();
    SDA_H;
	  I2C_delay();
    SCL_H;
    I2C_delay();
    SDA_L;
		I2C_delay();
    SCL_L;
    return SUCCESS;
}
void I2C_Stop(void)
{
    //I2C_SDA_OUT();
    SCL_L;
		I2C_delay();
    SDA_L;
		I2C_delay();	
    SCL_H;
	  I2C_delay();
    SDA_H;
    I2C_delay();
}
 
static void I2C_Ack()
{
    //I2C_SDA_OUT();
    SCL_L;
		I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
}
 
void I2C_NoAck()
{
    //I2C_SDA_OUT();
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
}
uint8_t I2C_GetAck(void)
{
    uint8_t time = 0;
    //I2C_SDA_IN();
		SDA_IN();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    while(SDA_read)
    {
      time++;
      if(time > 250)
      {			
        SCL_L;
				SDA_OUT();
        return ERROR;
      }
    }
    SCL_L;
    //I2C_SDA_OUT();
		SDA_OUT();
    return SUCCESS;
}
void I2C_SendByte(uint8_t Data)
{
    uint8_t cnt;
    //I2C_SDA_OUT();
    for(cnt=0; cnt<8; cnt++)
    {
      SCL_L;                              
      I2C_delay();
  
      if(Data & 0x80)
      {
        SDA_H;
        I2C_delay();                         
      }
      else
      {
        SDA_L;  
        I2C_delay();                       
      }
      Data <<= 1;
			I2C_delay();
      SCL_H;                              
      I2C_delay();
    }
    SCL_L;  
    I2C_delay();		
}
 
 
uint8_t I2C_ReadByte(uint8_t ack)
{
    uint8_t cnt;
    uint16_t data = 0;
    //I2C_SDA_IN();
		SDA_IN();
    for(cnt=0; cnt<8; cnt++)
    {
      SCL_L; 
      I2C_delay();                               
      SCL_H;                             
      data <<= 1;
      if(SDA_read)
      {
        data |= 0x01;  
        I2C_delay();                           
      }
      I2C_delay();
    }
		 //I2C_SDA_OUT();
		SDA_OUT();
    if(ack == 1)
    {
			I2C_delay();
      I2C_NoAck();
			I2C_delay(); 
    }
    else
    {
			I2C_delay();
      I2C_Ack();
			I2C_delay(); 
    }
   
    return data;                                  
}
 
void I2C_Initializes(void)
{
    SCL_H; 
    SDA_H;
}
uint16_t IIC_WriteByte(uint8_t chipAddess,uint16_t writeAddr, uint8_t *pbuff,uint16_t size)
{
    uint8_t *p = pbuff;
    uint16_t i = 0;
	  //I2C_delay();
    I2C_Start();
    I2C_SendByte(chipAddess & 0xfe);
    if(I2C_GetAck() == ERROR)
    {
      I2C_Stop();
      return ERROR;
    }
    I2C_SendByte(writeAddr);   
    I2C_GetAck();
    for(i = 0;i < size;i ++)
    {
        I2C_SendByte(*p);
			
        if(I2C_GetAck() == ERROR)
        {
          I2C_Stop();
          return ERROR;
        }
        p ++;
    }
		I2C_Stop();
    return SUCCESS;
}
 
uint16_t IIC_ReadByte(uint8_t chipAddess,uint8_t readAddess,uint8_t *pbuff,uint16_t size)
{
    uint16_t i = 0;
    uint8_t *p = pbuff;
    I2C_Start(); 
    I2C_SendByte(chipAddess & 0xfe);
    if(I2C_GetAck() == ERROR)
    {
        I2C_Stop();
        return ERROR;
    }
    I2C_SendByte(readAddess); 
    if(I2C_GetAck() == ERROR)
    {
        I2C_Stop();
        return ERROR;
    }
    I2C_Stop();
    I2C_Start();
    I2C_SendByte(chipAddess | 0x01);
    if(I2C_GetAck() == ERROR)
    {
        I2C_Stop();
        return ERROR;
    }
    for(i = 0;i < size;i ++)
    {  
        //if (i==(size -1))
        {
          //*p = I2C_ReadByte(1);
        }
        //else
        {	
          *p = I2C_ReadByte(0);
        }
        p ++;
    } 
    I2C_Stop();
    return SUCCESS;
}
