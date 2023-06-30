#ifndef ADX1XX_H_
#define ADX1XX_H_


#define CONVERSION_REG      0x00
#define CONFIG_REG          0x01
#define LO_THRESH_REG       0x02
#define HI_THRESH_REG       0x03

//CONFIG_REG
#define OS_STARTSINGLE      0x8000
#define OS_NO               0x0000

#define MUX_A0_A1           0x0000
#define MUX_A0_A3           0x1000
#define MUX_A1_A3           0x2000
#define MUX_A1_A3           0x3000
#define MUX_A0_GND          0x4000
#define MUX_A1_GND          0x5000
#define MUX_A2_GND          0x6000
#define MUX_A3_GND          0x7000


#define FSR_6_144V          0x0000
#define FSR_4_096V          0x0200
#define FSR_2_048V          0x0400
#define FSR_1_024V          0x0600
#define FSR_0_512V          0x0800
#define FSR_0_256V          0x0A00

#define MODE_CONTINUOUS     0x0000
#define MODE_SINGLE         0x0100

#define DR_8SPS             0x0000
#define DR_16SPS            0x0020
#define DR_32SPS            0x0040
#define DR_64SPS            0x0060
#define DR_128SPS           0x0080
#define DR_250SPS           0x00a0
#define DR_475PS            0x00c0
#define DR_860SPS           0x00e0

#define COMP_TRADITIONAL    0x0000
#define COMP_WINDOW         0x0010

#define COMP_POL_LOW        0x0000
#define COMP_POL_HIGH       0x0008

#define COMP_LAT            0x0000
#define COMP_LAT_NO         0x0004

#define COMP_QUE_ONE        0x0000
#define COMP_QUE_TWO        0x0001
#define COMP_QUE_FOUR       0x0002
#define COMP_QUE_NO         0x0003



typedef struct 
{
   uint16_t config;
   uint16_t loThresh;
   uint16_t hiThresh;

}adx1xx_InitTypeDef;


uint16_t adx1xx_i2c_set_reg(uint8_t reg, uint16_t pdata);
uint16_t adx1xx_i2c_read_reg(uint8_t reg, uint8_t *pdata);
uint16_t adx1xx_init(adx1xx_InitTypeDef *reg);

#endif
