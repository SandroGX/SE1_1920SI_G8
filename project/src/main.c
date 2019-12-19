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

}


bool tempUnit = true;
char* tempUnitOptions[2] = { "Fahrenheit", "Celsius" };


void changeTempUnit(void)
{
	tempUnit = UI_SelectOptions(tempUnitOptions, 2);
	FLASH_WriteData(tempUnitAddress, &tempUnit, sizeof(bool));
}

void setTime(void)
{
	UI_SetTime(0, 0);
}

void normalMode(void)
{
	int time = wait_ms();
	while(true)
	{
		UI_DisplayTime(0, 0);
		LCDText_Locate(1, 0);
		LCDText_Printf("%05.2f %c %04.0f Pa", BMP_getTemperature(tempUnit), tempUnit ? 'C' : 'F',BMP_getPressure());

		wait(200);
		int code = BUTTON_Hit();

		if(!(code & UPBUTTON && code & DOWNBUTTON))
			time = wait_ms();

		if(wait_elapsed(time) >= enterMenuTime)
			break;
	}
	LCDText_Clear();
	LCDText_Printf("Maintenance");
	wait(2000);
}

struct Menu menus[3] = { {"Set Time", &setTime}, { "Set Temp", &changeTempUnit }, { "Exit", &normalMode } };

int start(void)
{
	printf("Start\n");

	BUTTON_Init();
	SPI_Init();
	BMP_init();
	BMP_config(0b000, 0b1, 0, 0b11, 0b11, 0b11);
	wait_init();
	WAIT_Init();
	LCDText_Init();
	LCD_Control(true, false, false);
	RTC_Init(time(NULL));
	LED_Init(false);

	tempUnit = *tempUnitAddress;

	return 0;
}

int update(void)
{
	UI_StartMenu(menus, 3, 2);
	return 0;
}
