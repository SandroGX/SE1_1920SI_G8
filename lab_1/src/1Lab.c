/*
===============================================================================
 Name        : 1Lab.c
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
#include "led.h"


int main(void) {

    //printf("Hello World\n");

    LED_Init(false);
    wait_init();

    for(;;)
    {
		LED_On();
		wait(500);
		LED_Off();
		wait(500);
    }

    return 0;
}
