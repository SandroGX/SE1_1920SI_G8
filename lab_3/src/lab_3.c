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

#include "wait.h"
#include "lcd.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void)
{
	LCDText_Init();

	LCDText_WriteChar('a');
}
