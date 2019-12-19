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
#include "ui.h"

//#define UPBUTTON BUTTON0
//#define DOWNBUTTON BUTTON1
//#define ENTERBUTTON BUTTON2

#define DATE_FORMAT "%04d/%02d/%02d %02d:%02d"
#define YEAR_C 0
#define MON_C 5
#define DAY_C 8
#define HOUR_C 11
#define MIN_C 14



int circleValue(int val, int min, int max)
{
	val = val > max ? min : val;
	val = val < min ? max : val;
	return val;
}

int UI_SelectOptions(char* options[], int count)
{
	int selected = 0;

	while(true)
	{
		LCDText_Clear();
		LCDText_Printf("%s <", options[selected]);

		LCDText_Locate(1, 0);
		LCDText_Printf("%s", options[circleValue(selected+1, 0, count-1)]);

		wait(200);
		int code = BUTTON_Read();

		if(code & UPBUTTON)
			++selected;
		else if(code & DOWNBUTTON)
			--selected;
		else if(code & ENTERBUTTON)
			return selected;

		selected = circleValue(selected, 0, count-1);
	}
}

void UI_SelectMenu(Menu menu[], int count)
{
	int selected = 0;

	while(true)
	{
		LCDText_Clear();
		LCDText_Printf("%s <", menu[selected].name);

		LCDText_Locate(1, 0);
		LCDText_Printf("%s", menu[circleValue(selected+1, 0, count-1)].name);

		wait(200);
		int code = BUTTON_Read();

		if(code & UPBUTTON)
			++selected;
		else if(code & DOWNBUTTON)
			--selected;
		else if(code & ENTERBUTTON) {
			menu[selected].menu();
			selected = 0;
		}

		selected = circleValue(selected, 0, count-1);
	}
}

void UI_StartMenu(Menu menu[], int count, int init)
{
	menu[init].menu();
	UI_SelectMenu(menu, count);
}

int UI_Digit(int l, int c, int min, int max, int initVal, int maxDigits)
{
	int digit = initVal;
	digit = circleValue(digit, min, max);

	LCDText_Locate(l, c);
	while(1){
		LCDText_Printf("%0*d", maxDigits, digit);
		LCDText_Locate(l, c);
		BUTTON_WaitNoneHit();

		wait(200);
		int code = BUTTON_Read();

		if(code == UPBUTTON)
			++digit;
		else if(code == DOWNBUTTON)
			--digit;
		else if(code == ENTERBUTTON)
			break;

		digit = circleValue(digit, min, max);
	}
	return digit;
}

int UI_Number(int l, int c, int min, int max, int initVal, int maxDigits) // @suppress("No return")
{
	initVal = circleValue(initVal, min, max);

	LCDText_Locate(l, c);
	LCDText_Printf("%0*d", maxDigits, initVal); //min: 4532 max: 8674

	int digit = 1;
	for(int i = 0; i < maxDigits-1; ++i)
		digit *= 10;

	int number = 0;
	int remainderMin = min;
	int remaindertMax = max;
	int remainderInit = initVal;
	bool allowMin = false, allowMax = false;

	for(int i = 0; i < maxDigits; ++i)
	{
		int d = UI_Digit(l, c+i, allowMin ? 0 : remainderMin/digit, allowMax ? 9 : remaindertMax/digit, remainderInit/digit, 1) * digit;
		number += d;

		if(allowMin == false && d/digit > remainderMin/digit)
			allowMin = true;
		if(allowMax == false && d/digit < remaindertMax/digit)
			allowMax = true;

		remainderMin %= digit;
		remaindertMax %= digit;
		remainderInit %= digit;
		digit /= 10;
	}
	return number;
}

void UI_DisplayTime(int l, int c)
{
	LCDText_Clear();
	struct tm dateTime;
	RTC_GetValue(&dateTime);
	LCDText_Locate(l, c);
	LCDText_Printf(DATE_FORMAT, dateTime.tm_year, dateTime.tm_mon, dateTime.tm_mday, dateTime.tm_hour, dateTime.tm_min);
}

void UI_SetTime(int l, int c)
{
	LCDText_Clear();
	struct tm dateTime;
	RTC_GetValue(&dateTime);
	LCDText_Locate(l, c);
	LCDText_Printf(DATE_FORMAT, dateTime.tm_year, dateTime.tm_mon, dateTime.tm_mday, dateTime.tm_hour, dateTime.tm_min);
	LCD_Control(true, true, false);
	dateTime.tm_year = UI_Number(l, c+YEAR_C, 0, 4095, dateTime.tm_year, 4);
	dateTime.tm_mon = UI_Number(l, c+MON_C, 1, 12, dateTime.tm_mon, 2);
	dateTime.tm_mday = UI_Number(l, c+DAY_C, 1, RTC_GetMonDays(dateTime.tm_year, dateTime.tm_mon), dateTime.tm_mday, 2);
	dateTime.tm_hour = UI_Number(l, c+HOUR_C, 0, 23, dateTime.tm_hour, 2);
	dateTime.tm_min = UI_Number(l, c+MIN_C, 0, 59, dateTime.tm_min, 2);

	RTC_SetValue(&dateTime);
	LCD_Control(true, false, false);
}
