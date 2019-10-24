/*
===============================================================================
 Name        : lab_2.c
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

#include "buttons.h"
#include "timer.h"
#include "led.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void)
{
	wait_init();
	BUTTON_Init();
	LED_Init(false);

	int time = 0;
    for(;;)
    {
    	if(BUTTON_Hit() & BUTTON0)
    		time = 500;
    	else if(BUTTON_Hit() & BUTTON1)
    		time = 1000;
    	else if(BUTTON_Hit() & BUTTON2)
    		time = 1500;

    	if(time <= 0)
    		continue;

    	LED_On();
    	wait(time);
    	LED_Off();
    	time = 0;
    }
}
