/*
===============================================================================
 Name        : labUI.c
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

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "buttons.h"
#include "timer.h"
#include "wait.h"
#include "rtc.h"
#include "lcd.h"
#include "led.h"
#include "ui.h"

int main(void) {

	WAIT_Init();
	wait_init();
	LCDText_Init();
	LCD_Control(true, true, false);
	BUTTON_Init();
	RTC_Init(time(NULL));


	//int c = UI_Digit(0, 0, 0, 59, 0, 2);
	//int c = UI_Number(0, 0, 1923, 3341, 2391, 4);

	//LCDText_Locate(0, 0);
	//LCDText_Printf("You chose %04d", c);

	UI_SetTime(0, 0);
	while(1)
		UI_DisplayTime(0, 0);

}
