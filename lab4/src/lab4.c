/*
===============================================================================
 Name        : lab4.c
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

#include "lcd.h"
#include "rtc.h"
#include "timer.h"
#include "wait.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

	WAIT_Init();
	wait_init();
	LCDText_Init();
	RTC_Init(time(NULL));
	LCD_Control(true, true, true);

	struct tm dateTime;

	while(true)
	{
		RTC_GetValue(&dateTime);
		LCDText_Locate(0, 0);
		LCDText_Printf("%d/%d/%d", dateTime.tm_mday, dateTime.tm_mon + 1, dateTime.tm_year + 1900);
		LCDText_Locate(1, 0);
		LCDText_Printf("%d:%d:%d W:%d", dateTime.tm_hour, dateTime.tm_min, dateTime.tm_sec, dateTime.tm_wday);
	}

}
