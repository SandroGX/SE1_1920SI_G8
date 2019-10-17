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
	LPC_TIM0->CTCR = 0; //e timer
	LPC_TIM0->MCR = 1;//interrupt no match 0
}

/* Espera em microsegundos o valor passado no parâmetro. */
void WAIT_ChronoUs(uint32_t waitUs)
{
	LPC_TIM0->MR0 = waitUs * 100; //set match

	LPC_TIM0->TCR = 1; //reiniciar timer

	while(!(LPC_TIM0->IR & 1)); //esperar ate interrupt

	LPC_TIM0->IR = 0; //clear
}

