/*
===============================================================================
 Name        : project.c
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
#include <stdbool.h>
#include <time.h>

#include "buttons.h"
#include "spi.h"
#include "bmp.h"
#include "flash.h"
#include "timer.h"
#include "wait.h"
#include "lcd.h"
#include "rtc.h"
#include "ui.h"
#include "led.h"

#define sectorAddress 0x78000
#define tempUnitAddress (bool*)(sectorAddress+0)
#define enterMenuTime 2000

int main(void) {

    printf("Hello World\n");

    return 0 ;
}


bool tempUnit = true;
char* tempUnitOptions[2] = { "Celsius", "Fahrenheit" };


void changeTempUnit()
{
	tempUnit = UI_SelectOptions(tempUnitOptions, 2);
	FLASH_WriteData(tempUnitAddress, &tempUnit, sizeof(bool));
}

void setTime()
{
	UI_SetTime(0, 0);
}

void normalMode()
{
	int time = wait_ms();
	while(true)
	{
		UI_DisplayTime(0, 0);
		LCDText_Locate(1, 0);
		LCDText_Printf("%05.2f %c", BMP_getTemperature(tempUnit), tempUnit ? 'C' : 'F');

		wait_ms(200);
		int code = BUTTON_Hit();

		if(!(code & UPBUTTON && code & DOWNBUTTON))
			time = wait_ms();

		if(wait_elapsed(time) >= enterMenuTime)
			break;
	}
}

struct Menu menus[3] = { {"Set Time", &setTime}, { "Set Temp", &changeTempUnit }, { "Exit", &normalMode } };

int start(void)
{
	printf("Start\n");

	BUTTON_Init();
	SPI_Init();
	BMP_init();
	wait_init();
	WAIT_Init();
	LCDText_Init();
	RTC_Init(time(NULL));
	LED_Init(false);

	tempUnit = *tempUnitAddress;

	return 0;
}

int update(void)
{
	printf("Update\n");

	UI_StartMenu(menus, 3, 2);

	return 0;
}
