#ifndef _CSD206M_H_
#define _CSD206M_H_

#define CSD206M_CONFIG_REGISTER                         0X00
#define CSD206M_VSHUNT_REGISTER                         0X01
#define CSD206M_VBUS_REGISTER                           0X02
#define CSD206M_POWRE_REGISTER                          0X03
#define CSD206M_CURRENT_REGISTER                        0X04
#define CSD206M_CALIB_REGISTER                          0X05
#define CSD206M_MASK_EN_REGISTER                        0X06
#define CSD206M_ALERT_LIMIT_REGISTER                    0X07
#define CSD206M_CONFIG_TEMP_REGISTER                    0X10
#define CSD206M_DIETEMP_REGISTER                        0X11
#define CSD206M_TEMPCOCONFIG_REGISTER                   0X12
#define CSD206M_SOVL_TH_REGISTER                        0X13
#define CSD206M_SUVL_TH_REGISTER                        0X14
#define CSD206M_BOVL_TH_REGISTER                        0X15
#define CSD206M_BUVL_TH_REGISTER                        0X16
#define CSD206M_POWER_OL_TH_REGISTER                    0X17
#define CSD206M_TEMP_OL_TH_REGISTER                     0X18
#define CSD206M_DIAG_ALERT_REGISTER                     0X19
#define CSD206M_SMART_ALERT_REGISTER                    0X1A
#define CSD206M_ADV_CTRL_REGISTER                       0X1B
#define CSD206M_Manufacturer_ID_REGISTER                0XFE
#define CSD206M_Die_ID_REGISTER                         0XFF

//CSD206M_CONFIG_REGISTER
#define rst_Normal                                      0x0000
#define rst_SystemReset                                 0x8000

#define VSHUNT_range_81_92mv                            0x0000
#define VSHUNT_range_163_84mv                           0x2000

#define Temperature_Sensor_Dis                          0x0000
#define Temperature_Sensor_Enable                       0x0100

#define Averaging_1                                     0x0000
#define Averaging_4                                     0x0200
#define Averaging_16                                    0x0400
#define Averaging_64                                    0x0600
#define Averaging_128                                   0x0800
#define Averaging_256                                   0x0a00
#define Averaging_512                                   0x0c00
#define Averaging_1024                                  0x0e00

#define VBUS_Conversion_Time_148us                      0x0000                            
#define VBUS_Conversion_Time_212us                      0x0040 
#define VBUS_Conversion_Time_340us                      0x0080 
#define VBUS_Conversion_Time_596us                      0x00c0 
#define VBUS_Conversion_Time_1108us                     0x0100 
#define VBUS_Conversion_Time_2132us                     0x0140 
#define VBUS_Conversion_Time_4180us                     0x0180 
#define VBUS_Conversion_Time_8276us                     0x01c0 

#define VSHUNT_Conversion_Time_148us                    0x0000
#define VSHUNT_Conversion_Time_212us                    0x0008
#define VSHUNT_Conversion_Time_340us                    0x0010
#define VSHUNT_Conversion_Time_596us                    0x0018
#define VSHUNT_Conversion_Time_1108us                   0x0020
#define VSHUNT_Conversion_Time_2132us                   0x0028
#define VSHUNT_Conversion_Time_4180us                   0x0030
#define VSHUNT_Conversion_Time_8276us                   0x0038

#define Mode_Power_Down                                 0x0000
#define Mode_Shunt_Voltage_Triggered                    0x0001
#define Mode_Bus_Voltage_Triggered                      0x0002
#define Mode_Shunt_and_Bus_Triggered                    0x0003
#define Mode_Shutdown                                   0x0004
#define Mode_Shunt_Voltage_Continuous                   0x0005
#define Mode_Bus_Voltage_Continuous                     0x0006
#define Mode_Shunt_and_Bus_Continuous                   0x0007

//CSD206M_MASK_EN_REGISTER
#define VSHUNT_Over_Limit_Alert_dis                     0x0000
#define VSHUNT_Over_Limit_Alert_EN                      0x8000

#define VSHUNT_Under_Limit_Alert_dis                    0x0000
#define VSHUNT_Under_Limit_Alert_EN                     0x4000

#define VBUS_Over_Limit_Alert_dis                       0x0000
#define VBUS_Over_Limit_Alert_EN                        0x2000

#define VBUS_Under_Limit_Alert_dis                      0x0000
#define VBUS_Under_Limit_Alert_EN                       0x1000

#define POWER_Over_Limit_Alert_dis                      0x0000
#define POWER_Over_Limit_Alert_EN                       0x0800

#define Conversion_Ready                                0X0400

#define Slow_Alert_non_Averaged                         0x0000
#define Slow_Alert_Averaged                             0x0200

#define Alert_Function_Flag                             0x0010

//#define 

//CSD206M_CONFIG_TEMP_REGISTER
#define Temperature_Over_Limit                          0x8000

#define TEMPCO_dis                                      0x0000
#define TEMPCO_EN                                       0x4000

#define TEMP_Conversion_Time_148us                      0x0000
#define TEMP_Conversion_Time_212us                      0x0001
#define TEMP_Conversion_Time_340us                      0x0002
#define TEMP_Conversion_Time_596us                      0x0003
#define TEMP_Conversion_Time_1108us                     0x0004
#define TEMP_Conversion_Time_2132us                     0x0005
#define TEMP_Conversion_Time_4180us                     0x0006
#define TEMP_Conversion_Time_8276us                     0x0007

//CSD206M_DIAG_ALERT_REGISTER
#define VShunt_Over_Limit_Flag                          0x8000
#define VShunt_Under_Limit_Flag                         0x4000
#define VBus_Over_Limit_Flag                            0x2000
#define VBus_Under_Limit_Flag                           0x1000
#define Power_Over_Limit_Flag                           0x0800
#define Temp_Over_Limit_Flag                            0x0400
#define Math_Overflow_Flag                              0x0200
#define Conversion_Ready_Flag                           0x0100
#define ALERT_function_flag                             0x0080
#define CheckSum_Error_Flag                             0x0001


typedef struct
{
    uint16_t configReg;
    uint16_t calibrationReg;
    //uint16_t maskReg;
    uint16_t alertReg;
    uint16_t tempConfigReg;
    //uint16_t tempCorReg;
    uint16_t vshuntOLThrReg;
    uint16_t vshuntULThrReg;
    uint16_t vbusOLThrReg;
    uint16_t vbusULThrReg;
    uint16_t tempOLThrReg;
    uint16_t smartAlertReg;
    //uint16_t advancedDontrolReg;
}CSD206M_Handle;

void CSD206M_config(CSD206M_Handle *sensor);
float CSD206M_GetVshout_mV(CSD206M_Handle *sensor);
float CSD206M_GetVbus_V(void);
float CSD206M_GetPOWER(CSD206M_Handle *sensor);
float CSD206M_GetCURRENT(CSD206M_Handle *sensor);

#endif
