#ifndef __ADX923Q_H
#define __ADX923Q_H
#include "stm32g0xx_hal.h"
#include "main.h"
#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c,"
#define D_TO_B_INT8(i)            \
	(((i)&0x80) ? '1' : '0'),     \
		(((i)&0x40) ? '1' : '0'), \
		(((i)&0x20) ? '1' : '0'), \
		(((i)&0x10) ? '1' : '0'), \
		(((i)&0x08) ? '1' : '0'), \
		(((i)&0x04) ? '1' : '0'), \
		(((i)&0x02) ? '1' : '0'), \
		(((i)&0x01) ? '1' : '0')

//#define CRC_OPEN
#define ADX92XQ_WAKEUP 0X02			
#define ADX92XQ_STANDBY 0X04		
#define ADX92XQ_ADSRESET 0X06		
#define ADX92XQ_START 0X08			
#define ADX92XQ_STOP 0X0A			
#define ADX92XQ_OFFSETCAL 0X1A		
#define ADX92XQ_InvalidCommand 0XFF 

#define ADX92XQ_RDATAC 0X10 
#define ADX92XQ_SDATAC 0X11 
#define ADX92XQ_RDATA 0X12	
#define ADX92XQ_RFIFO 0X60	

#define ADX92XQ_RREG 0X20 
#define ADX92XQ_WREG 0X40 
#define ADX92XQ_RFIFO_Item(n) (0x1f & n)

#define ECG_ID 0X00
#define CONFIG1 0X01
#define CONFIG2 0X02
#define CONFIG3 0X0C
#define CONFIG4 0X0D
#define CONFIG5 0X0E
#define LOFF 0X03
#define CH1SET 0X04
#define CH2SET 0X05
#define RLD_SENS 0X06
#define LOFF_SENSE 0X07
#define LOFF_RLD 0X10
#define LOFF_AC1 0x11 // config ac freq using default mode
#define LON_CFG 0X12
#define LOFF_STAT 0X08
#define ERM_CFG 0x13
#define EPMIX_CFG 0X14
#define RESP1 0X09
#define RESP2 0X0A
#define GPIO 0X0B
#define LOFF_ISETP 0x0F
#define FIFO_CFG1 0X16
#define FIFO_CFG2 0X17
#define PACE_CFG 0X15

#define AC_CMP_THD0 0X1F
#define AC_CMP_THD1 0X20
#define AC_CMP_THD2 0X21
#define FIFO_STAT 0X18
#define MOD_STAT1 0X19
#define MOD_STAT2 0X1A

/****************************************************************/
/*******CONFIG1*******/
/****************************************************************/
#define SINGLE_SHOT_Continuous 0x00
#define SINGLE_SHOT_Single 0x80
#define DR_125 0x00
#define DR_250 0x01
#define DR_500 0x02
#define DR_1000 0x03
#define DR_2000 0x04
#define DR_4000 0x05
#define DR_8000 0x06
#define DR_125_D2 0x00
#define DR_250_D2 0x01
#define DR_500_D2 0x02
#define DR_1000_D2 0x03
#define DR_2000_D2 0x04
#define DR_4000_D2 0x05
#define DR_8000_D2 0x06
#define DR_125_D4 0x00
#define DR_250_D4 0x01
#define DR_500_D4 0x02
#define DR_1000_D4 0x03
#define DR_2000_D4 0x04
#define DR_4000_D4 0x05
#define DR_8000_D4 0x06
/****************************************************************/
/*******CONFIG2*******/
/****************************************************************/
#define PDB_LOFF_COMP_DIS 0x00
#define PDB_LOFF_COMP_EN 0x40
#define PDB_REFBUF_PD 0x00
#define PDB_REFBUF_EN 0x20
#define VREF_2V 0x00
#define VREF_4V 0x10
#define CLK_EN_DIS 0x00
#define CLK_EN_EN 0x08
#define INT_TEST_OFF 0x00
#define INT_TEST_ON 0x02
#define TEST_FREQ_DC 0x00
#define TEST_FREQ_1HZ 0x01
/****************************************************************/
/*******LOFF*******/
/****************************************************************/
#define COMP_TH_95 0x00
#define COMP_TH_92 0x20
#define COMP_TH_90 0x40
#define COMP_TH_87 0x60
#define COMP_TH_85 0x80
#define COMP_TH_80 0xa0
#define COMP_TH_75 0xc0
#define COMP_TH_70 0xe0
#define ILEAD_OFF_5nA 0x00
#define ILEAD_OFF_22nA 0x04
#define FLEAD_OFF_DC 0x00
#define FLEAD_OFF_AC 0x01
/****************************************************************/
/*******CH1SET*******/ /*******CH2SET*******/
/****************************************************************/
#define PD_EN 0x00
#define PD_PD 0x80
#define GAIN6 0x00
#define GAIN1 0x10
#define GAIN2 0x20
#define GAIN3 0x30
#define GAIN4 0x40
#define GAIN8 0x50
#define GAIN12 0x60
#define MUX_NORMAL 0x00
#define MUX_INPUT_SHORT 0x01
#define MUX_RLD_MEASURE 0x02
#define MUX_VDD_MEASURE 0x03
#define MUX_TEMP_SENSOR 0x04
#define MUX_TEST_SIGNAL 0x05
#define MUX_RLD_DRP 0x06
#define MUX_RLD_DRM 0x07
#define MUX_RLD_DRPM 0x08
#define MUX_IN3P_IN3N 0x09
#define MUX1_RLD_OUT 0x0b
#define MUX1_ERM 0x0F
/****************************************************************/
/*******RLD_SENS*******/
/****************************************************************/
#define PDB_RLD_PD 0x00
#define PDB_RLD_EN 0x20
#define RLD_LOFF_SENSE_DIS 0x00
#define RLD_LOFF_SENSE_EN 0x10
#define RLD2N_NOT 0x00
#define RLD2N_CON 0x08
#define RLD2P_NOT 0x00
#define RLD2P_CON 0x04
#define RLD1N_NOT 0x00
#define RLD1N_CON 0x02
#define RLD1P_NOT 0x00
#define RLD1P_CON 0x01
/****************************************************************/
/*******LOFF_SENS*******/
/****************************************************************/
#define CPFS_H 0x00
#define CPFS_L 0x40
#define FLIP2_SYNC 0x00
#define FLIP2_ASYNC 0x20
#define FLIP1_SYNC 0x00
#define FLIP1_ASYNC 0x10
#define EMUX1_VDD_DIS_P 0x00
#define EMUX1_VDD_CON_P 0x01
#define EMUX1_VSS_DIS_N 0x00
#define EMUX1_VSS_CON_N 0x02
#define EMUX1_VDD_DIS_N 0x00
#define EMUX1_VDD_CON_N 0x04
#define EMUX1_VSS_DIS_P 0x00
#define EMUX1_VSS_CON_P 0x08
/****************************************************************/
/*******LOFF_STAT*******/
/****************************************************************/
#if (WMODE != Low_Power_2_mode) 
#define CLK_DIV_4 0x00
#define CLK_DIV_16 0x80
#else 
#define CLK_DIV_4 0x00
#define CLK_DIV_8 0x80
#endif
#define RLD_STAT_CON 0x00
#define RLD_STAT_NOT 0x10
#define IN2N_OFF_CON 0x00
#define IN2N_OFF_NOT 0x08
#define IN2P_OFF_CON 0x00
#define IN2P_OFF_NOT 0x04
#define IN1N_OFF_CON 0x00
#define IN1N_OFF_NOT 0x02
#define IN1P_OFF_CON 0x00
#define IN1P_OFF_NOT 0x01
/****************************************************************/
/*******RESP1*******/
/****************************************************************/
#define RESP_DEMOD_OFF 0x00
#define RESP_DEMOD_ON 0x80
#define RESP_MOD_OFF 0x00
#define RESP_MOD_ON 0x40
#define RESP_PH_0 0x00
#define RESP_PH_11 0x04
#define RESP_PH_22 0x08
#define RESP_PH_33 0x0c
#define RESP_PH_45 0x10
#define RESP_PH_56 0x14
#define RESP_PH_67 0x18
#define RESP_PH_78 0x1c
#define RESP_PH_90 0x20
#define RESP_PH_101 0x24
#define RESP_PH_112 0x28
#define RESP_PH_123 0x2c
#define RESP_PH_135 0x30
#define RESP_PH_146 0x34
#define RESP_PH_157 0x38
#define RESP_PH_168 0x3c
#define RESP_CTRL_INT 0x00
#define RESP_CTRL_EXT 0x01
/****************************************************************/
/*******RESP2*******/
/****************************************************************/
#define CALIB_OFF 0x00
#define CALIB_ON 0x80
#define MOD_CLK_DIV1 0x00
#define MOD_CLK_DIV2 0x40
#define RESP_FREQ_DIV2 0x00
#define RESP_FREQ_DIV1 0x04
#define RLDREF_EXT 0x00
#define RLDREF_INT 0x02
/****************************************************************/
/*******GPIO*******/
/****************************************************************/
#define AC_AMP_SCALE_DIV1 0x00
#define AC_AMP_SCALE_DIV2 0x20
#define AC_AMP_SCALE_DIV4 0x40
#define AC_AMP_SCALE_DIV8 0x60
#define AC_AMP_SCALE_DIV16 0x80
#define GPIO2_OUT 0x00
#define GPIO2_IN 0x08
#define GPIO1_OUT 0x00
#define GPIO1_IN 0x04
#define GPIO1_DIS 0x00
#define GPIO1_EN 0x01
#define GPIO2_DIS 0x02
#define GPIO2_EN 0x03
/****************************************************************/
/*******CONFIG3*******/
/****************************************************************/
#define AC_MODE_SOFT 0x00
#define AC_MODE_HARD 0x80
#define P5VREF_OFF 0x00
#define P5VREF_ON 0x40
#define DIN_CRC_DIS 0x00
#define DIN_CRC_EN 0x08
#define DOUT_CRC_DIS 0x00
#define DOUT_CRC_EN 0x04
#define SPI_TIMEOUT_DIS 0x00
#define SPI_TIMEOUT_255 0x01
#define SPI_TIMEOUT_1023 0x02
#define SPI_TIMEOUT_4095 0x03
/****************************************************************/
/*******CONFIG4*******/
/****************************************************************/
#define DR_INT_DIS 0x00
#define DR_INT_EN 0x80
//#define                ADC_DAT_THD_d0              0x00
//#define                ADC_DAT_THD_d1              0x20
//#define                ADC_DAT_THD_d2              0x40
//#define                ADC_DAT_THD_d3              0x60
#define CLK_MISS_INT_DIS 0x00
#define CLK_MISS_INT_EN 0x08
#define RLDIN2RAMPP_DIS 0x00
#define RLDIN2RAMPP_CON 0x02
#define RAMPOUT2RAMPN_DIS 0x00
#define RAMPOUT2RAMPN_CON 0x01
/****************************************************************/
/*******CONFIG5*******/
/****************************************************************/
#define OSC_2M_DIS 0x00
#define OSC_2M_EN 0x80
/****************************************************************/
/**Interrupt Output to GPIO, including LOFF interrupt INT1,******/
/**ADC data out of range interrupt INT2, FIFO interrupt INT3,****/
/*CLK missing interrupt INT4,invalid SPI command interrupt INT5**/
/****************************************************************/
#define INT2GPIO_D0 0x00 // INT1, INT2, INT3, INT4, INT5 output to external with GPIO1.
#define INT2GPIO_D1 0x10 // INT1, INT2, INT3, INT4, INT5 output to external with GPIO2.
#define INT2GPIO_D2 0x20 // INT1, INT2, INT3, INT5 output to external with GPIO1, INT4 output to external with GPIO2.
#define INT2GPIO_D3 0x30 // INT1, INT2, INT4, INT5 output to external with GPIO1, INT3 output to external with GPIO2.
#define INT2GPIO_D4 0x40 // INT1, INT3, INT4, INT5 output to external with GPIO1, INT2 output to external with GPIO2.
#define INT2GPIO_D5 0x50 // INT2, INT3, INT4, INT5 output to external with GPIO1, INT1 output to external with GPIO2.
#define INT2GPIO_D6 0x60 // INT1, INT2, INT3, INT4 output to external with GPIO1, INT5 output to external with GPIO2.
#define INT2GPIO_NO 0x70 // NO interrupt output to GPIO pin.
#define INV_CMD_INT_DIS 0x00
#define INV_CMD_INT_EN 0x08
#define FRAME_CHK_DIS 0x00
#define FRAME_CHK_EN 0x04
#define IO_3MA_DIS 0x00
#define IO_3MA_EN 0x02
#define IO_SRM_DIS 0x00
#define IO_SRM_EN 0x01
/****************************************************************/
/*******LOFF_ISTEP*******/
/****************************************************************/
#define LOFF_INT_EN 0x00
#define LOFF_INT_DIS 0x80
#define CUR_LEVEL_DIS 0x00
#define CUR_LEVEL_EN 0x40
#define ISTEP_nA(a) (((uint8_t)((a+0.01) / 2.2f)) & 0x3f)
/****************************************************************/
/*******LOFF_RLD*******/
/****************************************************************/
#define EMUX2_VDD_DIS_P 0x00
#define EMUX2_VDD_CON_P 0x10
#define EMUX2_VSS_DIS_N 0x00
#define EMUX2_VSS_CON_N 0x20
#define EMUX2_VDD_DIS_N 0x00
#define EMUX2_VDD_CON_N 0x40
#define EMUX2_VSS_DIS_P 0x00
#define EMUX2_VSS_CON_P 0x80
#define RCOMP_TH_95 0x00
#define RCOMP_TH_92 0x02
#define RCOMP_TH_90 0x04
#define RCOMP_TH_87 0x06
#define RCOMP_TH_85 0x08
#define RCOMP_TH_80 0x0a
#define RCOMP_TH_75 0x0c
#define RCOMP_TH_70 0x0e
#define RLD_DEC_SHARE 0x00 // RLD shares the threshold comparator with the RA, LA, and LL pins
#define RLD_DEC_STAND 0x01 // RLD uses standalone comparator and needs configure RCOMP_TH[2:0] for threshold setting
/****************************************************************/
/*******LOFF_AC1*******/
/****************************************************************/
#define SQUARE_WAVE_SIN 0x00
#define SQUARE_WAVE_SQW 0x80
#define ACDIV_FACTOR ACDIV_FACTOR_DIV1
#define ACDIV_FACTOR_DIV1 0x00
#define ACDIV_FACTOR_DIV8 0x40
#if (ACDIV_FACTOR == ACDIV_FACTOR_DIV1)				  // If ACDIV_FACTOR_DIV1, step=1000Hz. ACDIV_FREQ odd configuration number is suggested
#define ACDIV_FRQ(a) ((uint8_t)(a / 1000) - 1) & 0x07 // 1000HZ~8000HZ
#define ACDIV_FRQ4KHz 0x03
#else											 // If ACDIV_FACTOR_DIV8, step=125Hz. ACDIV_FREQ odd configuration number is suggested
#define ACDIV_FRQ(a) ((uint8_t)(a / 125)) & 0x1F // 125HZ-4000HZ
#define ACDIV_FRQ4KHz 0x1f
#define ACDIV_FRQ500Hz 0x03
#endif
/****************************************************************/
/*******LON_CFG*******/
/****************************************************************/
#define HPF_DIS 0x00
#define HPF_EN 0x80
#define PF_05Hz 0x00
#define PF_067Hz 0x20
#define PF_7Hz 0x40
#define DEBOUNCE_DIS 0x00
#define DEBOUNCE_117 0x08
#define DEBOUNCE_335 0x10
// Function Offset calibration enable
#define OFC_DIS 0x00
#define OFC_EN 0x04
// AC Excitation amplitude selection
#define AC_EXCT_THD_160nA 0x00
#define AC_EXCT_THD_80nA 0x01
#define AC_EXCT_THD_40nA 0x02
#define AC_EXCT_THD_20nA 0x03
/****************************************************************/
/*******ERM_CFG*******/
/****************************************************************/
#define WMODE Speed_mode
#define Speed_mode 0x00		 
#define Resolution_mode 0x40  
#define Low_Power_1_mode 0x80 
#define Low_Power_2_mode 0xc0 
#define AC_DATA_OUT_DIS 0x00
#define AC_DATA_OUT_EN 0x20
#define AC_DATA_OUT_SEL_SIN 0x00
#define AC_DATA_OUT_SEL_COS 0x10
#if (ACDIV_FACTOR == ACDIV_FACTOR_DIV1) // AC Lead-off data output frequency selection
#define AC_DATA_FREQ_4K 0x00
#define AC_DATA_FREQ_16K 0x08
#else
#define AC_DATA_FREQ_500 0x00
#define AC_DATA_FREQ_2K 0x08
#endif
#define ERM_MUX_DIS 0x00
#define ERM_MUX_D1 0x01 // RLD2RA,LL2IN2P,LA2IN2N
#define ERM_MUX_D2 0x02 // RLD2RA,LA2IN2P,LL2IN2N
#define ERM_MUX_D3 0x03 // RLD2LA,RA2IN2P,LL2IN2N
#define ERM_MUX_D4 0x04 // RLD2LA,LL2IN2P,RA2IN2N
#define ERM_MUX_D5 0x05 // RLD2LL,LA2IN2P,RA2IN2N
#define ERM_MUX_D6 0x06 // RLD2LL,RA2IN2P,LA2IN2N
/****************************************************************/
/*******EPMIX_CONFIG*******/
/****************************************************************/
#define PACE_CHOP_DIS 0x00
#define PACE_CHOP_EN 0x80
#define PACE_COMP_DIS 0x00
#define PACE_COMP_EN 0x40
#define SHORT_PROTECT_DIS 0x00
#define SHORT_PROTECT_EN 0x20
#define FSEL_1024K 0x08
#define FSEL_512K 0x10
#define FSEL_256K 0x18
#define DOUT_DO3MA_STRONG 0x00
#define DOUT_DO3MA_LOW 0x04
#define AC_CMP_CFG_AC_24 0x00
#define AC_CMP_CFG_AC_12_H 0x01 // Channel 1 uses the low 12 bits of comparator threshold, and channel 2 uses the high 12 bits of comparator threshold to compare with the high 12-bit AC lead-off result
#define AC_CMP_CFG_AC_12_L 0x02 // Channel 1 uses the low 12 bits of comparator threshold, and channel 2 uses the high 12 bits of comparator threshold to compare with the low 12-bit AC lead-off result.
/****************************************************************/
/*******PACE_CFG*******/
/****************************************************************/
#define PACE_MUX_IN1 0x00
#define PACE_MUX_IN2 0x20
#define PACE_GAIN_4 0x00
#define PACE_GAIN_2_3 0x04
#define PACE_GAIN_4_3 0x08
#define PACE_GAIN_2 0x0c
#define PACE_GAIN_8_3 0x10
#define PACE_GAIN_16_3 0x14
#define PACE_GAIN_8 0x18
#define PACEOUT_ON_DIS 0x00
#define PACEOUT_ON_EN 0x02
#define PACE_DIS 0x00
#define PACE_EN 0x01
/****************************************************************/
/*******FIFO_CFG1*******/
/****************************************************************/
#define FIFO_INT_DIS 0x00
#define FIFO_INT_EN 0x80
#define FIFO_RST_DIS 0x00
#define FIFO_RST_EN 0x10
#define FRAME_CFG_1CH_ECG 0x00
#define FRAME_CFG_ECG_RES 0x02
#define FRAME_CFG_2CH_ECG 0x04
#define FIFO_DIS 0x00
#define FIFO_EN 0x01
/****************************************************************/
/*******FIFO_CFG2*******/
/****************************************************************/
#define STATUS_SEL_NO 0x00
#define STATUS_SEL_GPIO1 0x20
#define STATUS_SEL_GPIO2 0x40
#define STATUS_SEL_GPIO1_2 0x60
#define STATUS_SEL_PACE 0x80
#define DEPTH(a) (a - 1) & 0x0f
/****************************************************************/
/*******DEV_CONFIG1*******/
/****************************************************************/
#define RESP_CLK_HALF_DIV1 0x00
#define RESP_CLK_HALF_DIV2 0x80
#define CP_EN 0x00
#define CP_PD 0x40
#define PGA_CHOP_DIV16 0x00
#define PGA_CHOP_DIV32 0x10
#define PGA_CHOP_DIV64 0x20
#define PGA_CHOP_DIV4 0x30
#define MOD_CHOP_DIV16 0x00
#define MOD_CHOP_DIV2 0x04
#define MOD_CHOP_DIV4 0x08
#define MOD_CHOP_DIV8 0x0c
#define DITHER_NO 0x00
#define DITHER_EN 0x01
//			ECG PIN DEFINE
//			ADC_DRDY 					_> PA0		
//			CLK_SEL	 					_> PC3
//			POWERDOWN/RESET		_> PC2
//			START							_> PC1
//			RCLK/GPIO2				_> PC15
//			RCLK/GPIO1				_> PC14
//			XTAL_EN						_> PA8
//			AVCC_EN						_> PC12
//			DVDD_EN						_> PC10
#define NSSPORT GPIOA
#define NSS_PIN GPIO_PIN_4
#define ADC_DRDY_Port GPIOC
#define ADC_DRDY_Pin GPIO_PIN_9
#define XTAL_EN_Port GPIOA
#define XTAL_EN_Pin GPIO_PIN_7
#define CLK_SEL_Port GPIOC
#define CLK_SEL_Pin GPIO_PIN_3
#define PWDN_Port GPIOC
#define PWDN_Pin GPIO_PIN_2
#define START_Port GPIOC
#define START_Pin GPIO_PIN_1
#define GPIO2_Port GPIOC
#define GPIO2_Pin GPIO_PIN_15
#define GPIO1_Port GPIOC
#define GPIO1_Pin GPIO_PIN_14
#define PIN_ON GPIO_PIN_SET
#define PIN_OFF GPIO_PIN_RESET
#define AVCC_EN_Port GPIOC
#define AVCC_EN_Pin GPIO_PIN_12
#define DVDD_EN_Port GPIOC
#define DVDD_EN_Pin GPIO_PIN_10

#define ADC_DRDY HAL_GPIO_ReadPin(ADC_DRDY_Port, ADC_DRDY_Pin) //

#define NSS_H HAL_GPIO_WritePin(NSSPORT, NSS_PIN, GPIO_PIN_SET)
#define NSS_L HAL_GPIO_WritePin(NSSPORT, NSS_PIN, GPIO_PIN_RESET)

#define XTAL_EN HAL_GPIO_WritePin(XTAL_EN_Port, XTAL_EN_Pin, GPIO_PIN_SET)
#define XTAL_DIS HAL_GPIO_WritePin(XTAL_EN_Port, XTAL_EN_Pin, GPIO_PIN_RESET)

#define ExternalCLK HAL_GPIO_WritePin(CLK_SEL_Port, CLK_SEL_Pin, GPIO_PIN_RESET)
#define InternalCLK HAL_GPIO_WritePin(CLK_SEL_Port, CLK_SEL_Pin, GPIO_PIN_SET)

#define PWDN_L HAL_GPIO_WritePin(PWDN_Port, PWDN_Pin, GPIO_PIN_RESET)
#define PWDN_H HAL_GPIO_WritePin(PWDN_Port, PWDN_Pin, GPIO_PIN_SET)

#define START_L HAL_GPIO_WritePin(START_Port, GPIO_PIN_1, GPIO_PIN_RESET)
#define START_H HAL_GPIO_WritePin(START_Port, GPIO_PIN_1, GPIO_PIN_SET)


#define GPIO2_L HAL_GPIO_WritePin(GPIO2_Port, GPIO2_Pin, GPIO_PIN_RESET)
#define GPIO2_H HAL_GPIO_WritePin(GPIO2_Port, GPIO2_Pin, GPIO_PIN_SET)
#define GPIO2 HAL_GPIO_ReadPin(GPIO2_Port, GPIO2_Pin) //

#define GPIO1_L HAL_GPIO_WritePin(GPIO1_Port, GPIO1_Pin, GPIO_PIN_RESET)
#define GPIO1_H HAL_GPIO_WritePin(GPIO1_Port, GPIO1_Pin, GPIO_PIN_SET)
#define GPIO1 HAL_GPIO_ReadPin(GPIO1_Port, GPIO1_Pin) //

#define AVCC_EN(X) HAL_GPIO_WritePin(AVCC_EN_Port, AVCC_EN_Pin, (X))
#define DVDD_EN(X) HAL_GPIO_WritePin(DVDD_EN_Port, DVDD_EN_Pin, (X))
#define ADX92XQ_GPIO1_H ADX92XQ_REG(ADX92XQ_WREG | GPIO, 0x02);
#define ADX92XQ_GPIO1_L ADX92XQ_REG(ADX92XQ_WREG | GPIO, 0x00);

#define ADX92XQ_GPIO2_H ADX92XQ_REG(ADX92XQ_WREG | GPIO, 0x01);
#define ADX92XQ_GPIO2_L ADX92XQ_REG(ADX92XQ_WREG | GPIO, 0x00);

typedef struct __Data_Format
{
#ifdef CRC_OPEN
	uint8_t Header;
	uint8_t LEAD_OFF;
	uint8_t A92X_GPIO;
	uint8_t CRC_WORD;
	int32_t DATA_1ch;
	int32_t DATA_2ch;
#else
	uint8_t Header;
	uint8_t LEAD_OFF;
	uint8_t A92X_GPIO;
	int32_t DATA_1CH;
	int32_t DATA_2CH;
#endif

} Data_Format;
typedef struct __Ac_Loff_Data_Format
{
	int32_t STATUS;
	int32_t CH1;
	int32_t CH2;
	int32_t CH1SIN;
	int32_t CH1COS;
	int32_t CH2SIN;
	int32_t CH2COS;
	int32_t CH1AMP;
	int32_t CH1PHA;
	int32_t CH2AMP;
	int32_t CH2PHA;
} Ac_Loff_Data_Format;

extern Data_Format ADX92XQ_Data_Buff;
extern Ac_Loff_Data_Format ADX92XQ_Acloff_Data;
int32_t s24tos32(uint32_t data);
uint8_t ADX92XQ_Init(void);
void ADX92XQ_Config(void);
void ADX92XQ_ReadData(void);
void ADX92XQ_ReadData_fifo(void);
void ADX92XQ_Read_AC_LOFF_Data(void);
void ADX92XQ_Read_AC_LOFF_Mode(uint8_t mode);

void ADX92XQ_CMD(uint8_t cmd);
uint8_t ADX92XQ_SPI_RW(uint8_t data, uint8_t len);
uint8_t ADX92XQ_REG(uint8_t cmd, uint8_t data); 
uint8_t ADX92XQ_REG_Stream(uint8_t CMD, uint8_t StartAddr, uint8_t StopAddrNum, uint8_t *data);
uint8_t *FIFO_data_transposition(uint8_t *pRxData, uint8_t Item);
void ADX92XQ_ReadReg(uint8_t *cmd, uint8_t *data, uint8_t size);
void ADX92XQ_AC_LOFF_Data_Out(uint8_t mode);
void ShellSort(uint16_t *arr, uint16_t size); 

#endif
