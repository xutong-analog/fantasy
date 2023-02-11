#ifndef __BSP_LPSPI_H
#define __BSP_LPSPI_H

#include "fsl_common.h"



#define LPSPI3_CLOCK_FREQ 6000000UL


void LPSPI_Init(void);
//xue
void Lpspi_Write(uint8_t datasize,uint8_t *data);
void Lpspi_Read(uint8_t datasize,uint8_t *data,uint8_t *Rxdata);

#endif /* __BSP_LPSPI_H */

