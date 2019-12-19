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

#include "timer.h"
#include "wait.h"
#include "lcd.h"
#include "led.h"
#include "spi.h"
#include "bmp.h"

#include <stdbool.h>


int main(void)
{
	WAIT_Init();
	wait_init();
	LCDText_Init();
	LCD_Control(true, true, true);
	SPI_Init();
	//pre-BMP
	/*
	SPI_ConfigTransfer(10000000, 8, 0);

	unsigned short *txBuffer = malloc(2*sizeof(short));
	unsigned short *rxBuffer = malloc(2*sizeof(short));

	txBuffer[0] = (1<<7) | 0xD0; //read ID
	txBuffer[1] = (1<<7) | 0xD0;
	SPI_Transfer(txBuffer, rxBuffer, 2);

	printf("%x\n", rxBuffer[0]);
	printf("%x\n", rxBuffer[1]);

	free(txBuffer);
	free(rxBuffer);
	*/

	BMP_init();

	//         t_sb   filter spi3w_en osrs_t  osrs_p  mode
	BMP_config(0b000, 0b1, 0, 0b11, 0b11, 0b11);

	while(true) {
		LCDText_Clear();
		LCDText_Locate(0, 0);
		LCDText_Printf("%05.2f C", BMP_getTemperature(true));
		LCDText_Locate(1, 0);
		LCDText_Printf("%05.2f Pa", BMP_getPressure());
		wait(200);
	}
}
