#ifndef _DR70X_H_
#define _DR70X_H_

// Register Define
//status registers
#define REG_FaultStatus							0
#define REG_VDSAndSDFStatus					1
//control registers
#define REG_MainControl							2
#define REG_IDRIVEAndWDControl			3
#define REG_VDSControl							4
#define	REG_ConfigControl						5

//REG_FaultStatus
#define BIT_FAULT										0x80
#define BIT_WDFLT										0x40
#define BIT_GDF											0x20
#define BIT_OCP											0x10
#define BIT_VM_UVFL									0x08
#define BIT_VCP_UVFL								0x04
#define BIT_OTSD										0x02
#define BIT_OTW											0x01
//REG_VDSAndSDFStatus
#define BIT_H2_GDF									0x80
#define BIT_L2_GDF									0x40
#define BIT_H1_GDF									0x20
#define BIT_L1_GDF									0x10
#define BIT_H2_VDS									0x08
#define BIT_L2_VDS									0x04
#define BIT_H1_VDS									0x02
#define BIT_L1_VDS									0x01
//REG_MainControl
#define LOCK												0X30
#define UNLOCK											0x18			

//REG_IDRIVEAndWDControl	
#define TDEAD_120ns									0x00
#define TDEAD_240ns									0x40			
#define TDEAD_480ns									0x80
#define TDEAD_960ns									0xc0
#define WD_EN												0x20
#define WD_DIS											0x00
#define WD_DLY_10ms									0x00
#define WD_DLY_20ms									0x08
#define WD_DLY_50ms									0x10
#define WD_DLY_100ms								0x18
#define IDRIVE_000									0x00
#define IDRIVE_001									0x01
#define IDRIVE_010									0x02
#define IDRIVE_011									0x03
#define IDRIVE_100									0x04
#define IDRIVE_101									0x05
#define IDRIVE_110									0x06
#define IDRIVE_111									0x07
//REG_VDSControl
#define SO_LIM_DEF									0x00
#define SO_LIM_3_6V									0x80
#define VDS_0_06V										0x00  //0.06V
#define VDS_0_145V									0x10
#define VDS_0_17V										0x20
#define VDS_0_2V										0x30
#define VDS_0_12V										0x40
#define VDS_0_24V										0x50
#define VDS_0_48V										0x60
#define VDS_0_96V										0x70
#define DIS_H2_VDS									0x00
#define EN_H2_VDS										0x08
#define DIS_L2_VDS									0x00
#define EN_L2_VDS										0x04
#define DIS_H1_VDS									0x00
#define EN_H1_VDS										0x02
#define DIS_L1_VDS									0x00
#define EN_L1_VDS										0x01
//REG_ConfigControl
#define TOFF_25us										0x00
#define TOFF_50us										0x40
#define TOFF_100us									0x80
#define TOFF_200us									0xc0
#define CHOP_IDS_DIS								0x00
#define CHOP_IDS_EN									0x20
#define VREF_SCL_100								0x00
#define VREF_SCL_75									0x08
#define VREF_SCL_50									0x10
#define VREF_SCL_25									0x18
#define SH_DIS											0x00
#define SH_EN												0x04
#define GAIN_CS_10									0x00
#define GAIN_CS_19_8								0x01
#define GAIN_CS_39_4								0x02
#define GAIN_CS_78									0x03

void DR70x_Init(void);
void DR70x_Mode0_Brake(void);
void DR70x_Mode0_Reverse(uint8_t pulse);
void DR70x_Mode0_Forward(uint8_t pulse);
void DR70x_Transmit(uint8_t addess, uint8_t data);
uint8_t DR70x_Recive(uint8_t addess);

#endif
