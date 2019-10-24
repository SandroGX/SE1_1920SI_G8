/*
 * timer.c
 *
 *  Created on: 10/10/2019
 *      Author: Saturn
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>


void WAIT_Init(void)
{
	LPC_TIM0->CTCR = 0; //its timer
	LPC_TIM0->MCR = 1;//interrupt on match 0
	LPC_SC->PCLKSEL0 = 0b01<<2 | (LPC_SC->PCLKSEL0 & ~(0b11<<2)); //set PCLK equals to cpu clock
	LPC_TIM0->PR = 100;//prescale counter
}

/* Espera em microsegundos o valor passado no parâmetro. */
void WAIT_ChronoUs(uint32_t waitUs)
{
	LPC_TIM0->MR0 = waitUs; //set match

	LPC_TIM0->TCR = 0b10; //restart and enable timer
	LPC_TIM0->TCR = 0b01; //leave enabled bit

	while(!(LPC_TIM0->IR & 1)); //wait for interrupt

	LPC_TIM0->IR = 1; //clear interrupt
	LPC_TIM0->TCR = 0; //disable timer
}

