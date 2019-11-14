/*
===============================================================================
 Name        : lab5.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <stdlib.h>

#include "spi.h"

int main(void)
{
	SPI_Init();
	SPI_ConfigTransfer(10000000, 8, 2);

	unsigned short *txBuffer = malloc(2*sizeof(short));
	unsigned short *rxBuffer = malloc(2*sizeof(short));

	txBuffer[0] = 1<<8 & 0xD0;
	SPI_Transfer(txBuffer, rxBuffer, 2);

	printf("%x\n", rxBuffer[0]);
	printf("%x\n", rxBuffer[1]);

	free(txBuffer);
	free(rxBuffer);
}
