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
#include "buttons.h"

void checkTime(struct tm* aux) {
	if (aux->tm_hour > 23)
		aux->tm_hour = 0;

	if (aux->tm_min > 59)
		aux->tm_min = 0;

	if (aux->tm_sec > 59)
		aux->tm_sec = 0;

	if (aux->tm_hour < 0)
		aux->tm_hour = 23;

	if (aux->tm_min < 0)
		aux->tm_min = 59;

	if (aux->tm_sec < 0)
		aux->tm_sec = 59;

	if (aux->tm_year < 0)
		aux->tm_mon = 4096;

	if (aux->tm_year > 4096)
		aux->tm_mon = 0;

	if (aux->tm_mday < 1)
		aux->tm_mday = 31;

	if (aux->tm_mday > 31)
		aux->tm_mday = 1;

	if (aux->tm_wday < 0)
		aux->tm_wday = 6;

	if (aux->tm_wday > 6)
		aux->tm_wday = 0;

	if (aux->tm_mon < 1)
		aux->tm_mon = 11;

	if (aux->tm_mon > 12)
		aux->tm_mon = 0;

	if (aux->tm_mon < 1)
		aux->tm_mon = 11;
}

void decrementValue(int col, int loc, struct tm* aux) {
	if (col == 0) {
		switch (loc) {
		case (0):
			(aux->tm_mday)--;
			(aux->tm_yday)--;
			(aux->tm_wday)--;
			break;
		case (3):
			(aux->tm_mon)--;
			break;
		case (6):
			(aux->tm_year)--;
			break;
		}
	} else {
		switch (loc) {
		case (0):
			(aux->tm_hour)--;
			break;
		case (3):
			(aux->tm_min)--;
			break;
		case (6):
			(aux->tm_sec)--;
			break;
		}
	}
}

void incrementValue(int col, int loc, struct tm* aux) {
	if (col == 0) {
		switch (loc) {
		case (0):
			(aux->tm_mday)++;
			(aux->tm_yday)++;
			(aux->tm_wday)++;
			break;
		case (3):
			(aux->tm_mon)++;
			break;
		case (6):
			(aux->tm_year)++;
			break;
		}
	} else {
		switch (loc) {
		case (0):
			(aux->tm_hour)++;
			break;
		case (3):
			(aux->tm_min)++;
			break;
		case (6):
			(aux->tm_sec)++;
			break;
		}
	}
}

int main(void) {

	WAIT_Init();
	wait_init();
	BUTTON_Init();
	LCDText_Init();
	RTC_Init(time(NULL));
	LCD_Control(true, true, true);

	struct tm dateTime;
	struct tm aux;

	while(true)
	{
		RTC_GetValue(&dateTime);
		aux = dateTime;
		if(BUTTON_Hit() & UPBUTTON){
			wait(200);
			int loc = 0;
			int col = 0;
			while(loc<7 & col < 2){
				if(BUTTON_Read() & ENTERBUTTON){
					wait(200);
					incrementValue(col, loc, &aux);
				}
				if(BUTTON_Read() & DOWNBUTTON){
					wait(200);
					loc = loc + 3;
					if(loc>6){
						loc = 0; col++;
					}
				}
				if(BUTTON_Read() & UPBUTTON){
					wait(200);
					decrementValue(col, loc, &aux);
				}
				checkTime(&aux);
				LCDText_Clear();
				LCDText_Locate(0, 0);
				LCDText_Printf("%d/%d/%d", aux.tm_mday, aux.tm_mon + 1, aux.tm_year + 1900);
				LCDText_Locate(1, 0);
				LCDText_Printf("%d:%d:%d W:%d", aux.tm_hour, aux.tm_min, aux.tm_sec, aux.tm_wday);
			}
			LCDText_Clear();
			RTC_SetValue(&aux);
		}
		LCDText_Locate(0, 0);
		LCDText_Printf("%d/%d/%d", dateTime.tm_mday, dateTime.tm_mon + 1, dateTime.tm_year + 1900);
		LCDText_Locate(1, 0);
		LCDText_Printf("%d:%d:%d W:%d", dateTime.tm_hour, dateTime.tm_min, dateTime.tm_sec, dateTime.tm_wday);
	}

}
