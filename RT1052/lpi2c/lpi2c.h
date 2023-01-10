#ifndef __BSP_LPI2C_H
#define __BSP_LPI2C_H

#include "fsl_common.h"



#define LPI2C1_CLOCK_FREQ 3000000UL


void LPI2C_Init(void);
bool Lpi2c_Write(uint8_t SlaveAdd,uint8_t subAdd,uint8_t subAddsize,uint8_t datasize,uint8_t *data);

#endif /* __BSP_LPSPI_H */

