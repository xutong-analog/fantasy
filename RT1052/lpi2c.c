 #include "fsl_iomuxc.h"
#include "fsl_gpio.h" 
#include "fsl_lpi2c.h"
#include "pad_config.h" 
#include "bsp_lpi2c.h"


static void LPI2C_GPIO_Init(void);

static void LPI2C_GPIO_Init(void)
{
        IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL, /* GPIO_AD_B1_00 is configured as LPI2C1_SCL */
        1U);
        /* Software Input On Field: Input Path is determined by functionality */
        IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA, /* GPIO_AD_B1_01 is configured as LPI2C1_SDA */
        1U); /* Software Input On Field: Input Path is determined by functionality */
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL, 0x18B0U);
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA, 0x18B0U);
}
void LPI2C_Init(void)
{
    //config Lpi2c clock
    CLOCK_SetMux(kCLOCK_Lpi2cMux, 0u);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, 5u);
    //initial Gpio config
    LPI2C_GPIO_Init();
    lpi2c_master_config_t lpi2cConfig = {0};
    /*

    * lpi2cConfig.debugEnable = false;

    * lpi2cConfig.ignoreAck = false;

    * lpi2cConfig.pinConfig = kLPI2C_2PinOpenDrain;

    * lpi2cConfig.baudRate_Hz = 100000U;

    * lpi2cConfig.busIdleTimeout_ns = 0;

    * lpi2cConfig.pinLowTimeout_ns = 0;

    * lpi2cConfig.sdaGlitchFilterWidth_ns = 0;

    * lpi2cConfig.sclGlitchFilterWidth_ns = 0;

    */

    LPI2C_MasterGetDefaultConfig(&lpi2cConfig);
    LPI2C_MasterInit(LPI2C1, &lpi2cConfig, LPI2C1_CLOCK_FREQ);

}

bool Lpi2c_Write(uint8_t SlaveAdd,uint8_t subAdd,uint8_t subAddsize,uint8_t datasize,uint8_t *data)
{
    lpi2c_master_transfer_t trans;
    status_t reVal = kStatus_Fail;
    trans.data=data;
    trans.dataSize=datasize;
    trans.direction=kLPI2C_Write;
    trans.slaveAddress=(SlaveAdd>>1);
    trans.subaddress=subAdd;
    trans.subaddressSize=subAddsize;
    trans.flags=kLPI2C_TransferDefaultFlag;
    reVal = LPI2C_MasterTransferBlocking(LPI2C1,&trans);
    if (reVal != kStatus_Success)
    {
    return 1;
    }
    return 0;
}
