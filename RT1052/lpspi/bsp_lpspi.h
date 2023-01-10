#ifndef __BSP_LPSPI_H
#define __BSP_LPSPI_H

#include "fsl_common.h"



#define LPSPI3_CLOCK_FREQ 6000000UL


void LPSPI_Init(void);
void DAC_Write(uint8_t channel,uint16_t Value);

#endif /* __BSP_LPSPI_H */

