/*
 * ui.c
 *
 *  Created on: 10/12/2019
 *      Author: Saturn
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdbool.h>
#include <stdio.h>
#include <time.h>


#include "buttons.h"
#include "lcd.h"
#include "timer.h"
#include "rtc.h"

#define UPBUTTON BUTTON0
#define DOWNBUTTON BUTTON1
#define ENTERBUTTON BUTTON2

#define DATE_FORMAT "%04d/%02d/%02d %02d:%02d"
#define YEAR_C 0
#define MON_C 5
#define DAY_C 8
#define HOUR_C 11
#define MIN_C 14


int UI_Digit(int l, int c, int min, int max, int initVal,int maxDigits)
{
	int digit = initVal;
	digit = digit > max ? min : digit;
	digit = digit < min ? max : digit;

	LCDText_Locate(l, c);
	while(1){
		LCDText_Printf("%0*d", maxDigits, digit);
		LCDText_Locate(l, c);
		BUTTON_WaitNoneHit();

		int code = BUTTON_Read();

		if(code == UPBUTTON){
			++digit;
			digit = digit > max ? min : digit;
		}
		else if(code == DOWNBUTTON){
			--digit;
			digit = digit < min ? max : digit;
		}
		else if(code == ENTERBUTTON)
			break;

		wait(200);
	}
	return digit;
}

void UI_DisplayTime(int l, int c)
{
	struct tm dateTime;
	RTC_GetValue(&dateTime);
	LCDText_Locate(l, c);
	LCDText_Printf(DATE_FORMAT, dateTime.tm_year, dateTime.tm_mon, dateTime.tm_mday, dateTime.tm_hour, dateTime.tm_min);
}


void UI_SetTime(int l, int c)
{
	struct tm dateTime;
	RTC_GetValue(&dateTime);
	LCDText_Locate(l, c);
	LCDText_Printf(DATE_FORMAT, dateTime.tm_year, dateTime.tm_mon, dateTime.tm_mday, dateTime.tm_hour, dateTime.tm_min);

	dateTime.tm_year = UI_Digit(l, c+YEAR_C, 0, 9999, dateTime.tm_year, 4);
	dateTime.tm_mon = UI_Digit(l, c+MON_C, 1, 12, dateTime.tm_mon, 2);
	dateTime.tm_mday = UI_Digit(l, c+DAY_C, 1, 31, dateTime.tm_mday, 2);
	dateTime.tm_hour = UI_Digit(l, c+HOUR_C, 0, 23, dateTime.tm_hour, 2);
	dateTime.tm_min = UI_Digit(l, c+MIN_C, 0, 59, dateTime.tm_min, 2);

	RTC_SetValue(&dateTime);
}
