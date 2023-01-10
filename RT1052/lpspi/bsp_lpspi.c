#include "fsl_iomuxc.h"
#include "fsl_gpio.h" 
#include "fsl_lpspi.h"
#include "pad_config.h" 
#include "bsp_lpspi.h"


static void LPSPI_GPIO_Init(void);

static void LPSPI_GPIO_Init(void)
{
     IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B0_00_LPSPI3_SCK,        /* GPIO_AD_B0_00 is configured as LPSPI3_SCK */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B0_01_LPSPI3_SDO,        /* GPIO_AD_B0_01 is configured as LPSPI3_SDO */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B0_02_LPSPI3_SDI,        /* GPIO_AD_B0_02 is configured as LPSPI3_SDI */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B0_03_LPSPI3_PCS0,       /* GPIO_AD_B0_03 is configured as LPSPI3_PCS0 */
      0U);
}
void LPSPI_Init(void)
{
    //config Lpspi clock
    CLOCK_SetMux(kCLOCK_LpspiMux, 3);
    CLOCK_SetDiv(kCLOCK_LpspiDiv, 7U);
    //initial Gpio config
    LPSPI_GPIO_Init();
    //initial lpspi config
    lpspi_master_config_t config;

    LPSPI_MasterGetDefaultConfig(&config);
    //config lpspi cs pin
    config.whichPcs=kLPSPI_Pcs0;

    LPSPI_MasterInit(LPSPI3, &config, LPSPI3_CLOCK_FREQ);
}
void Lpspi_Write(uint8_t datasize,uint8_t *data)
{
    lpspi_transfer_t spi_tranxfer;
    spi_tranxfer.configFlags=kLPSPI_MasterPcs0|kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap;
    spi_tranxfer.txData=data; //要发送的数据
    spi_tranxfer.rxData=NULL;
    spi_tranxfer.dataSize=datasize; //数据长度
    LPSPI_MasterTransferBlocking(LPSPI3, &spi_tranxfer);
}
