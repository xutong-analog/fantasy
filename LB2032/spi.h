#ifndef __SPI_H
#define __SPI_H

#include "stc8h.h"

#define uint16_t unsigned int
#define	uint8_t unsigned char

sbit CS 	= P1^2;
sbit SDIO = P1^3;
sbit SDI 	= P1^4;
sbit SCLK	= P1^5;


#define SCLK_H	SCLK=1
#define SCLK_L	SCLK=0

#define MOSI_H	SDIO=1
#define MOSI_L	SDIO=0

#define CS_H		CS=1
#define CS_L		CS=0

#define MISO	SDIO

void SPI_Write(uint16_t addr,uint8_t date);
uint8_t SPI_Read(uint16_t addr);
void HAL_Delay(uint8_t i);
#endif
