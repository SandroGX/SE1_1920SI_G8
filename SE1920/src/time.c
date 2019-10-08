/*
 * time.c
 *
 *  Created on: 26/09/2019
 *      Author: Sandro
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

volatile uint32_t ms;

void wait_init()
{
	ms = 0;
	SysTick_Config(SystemCoreClock / 1000);
}

uint32_t wait_ms()
{
	return ms;
}

uint32_t wait_elapsed(uint32_t time)
{
	return ms - time;
}

void wait(uint32_t milis)
{
	uint32_t start = ms;
	while(ms-start < milis);
}

//what to do on a interrupt
void SysTick_Handler()
{
	++ms;
}
