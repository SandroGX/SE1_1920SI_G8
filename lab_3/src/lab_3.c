/*
===============================================================================
 Name        : lab_3.c
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

#include "time.h"
#include "wait.h"
#include "lcd.h"
#include "led.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void)
{
	WAIT_Init();
	wait_init();


	LCDText_Init();

	LCD_Control(true, true, true);
	LCDText_WriteString("ABCDEFG123");
}
