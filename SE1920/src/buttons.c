/*
 * buttons.c
 *
 *  Created on: 03/10/2019
 *      Author: Saturn
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>


#define PINMODECFG_PULLUP 0
#define PINMODECFG_REPEATER 1
#define PINMODECFG_NOTHING 2
#define PINMODECFG_PULLDOWN 3

#define BUTTON0_PIN 2
#define BUTTON1_PIN 3
#define BUTTON2_PIN 21

//mod 16 because they may be in different registers
#define BUTTON0_PINCFG (BUTTON0_PIN%16)*2
#define BUTTON1_PINCFG (BUTTON1_PIN%16)*2
#define BUTTON2_PINCFG (BUTTON2_PIN%16)*2

#define BUTTON0 1<<BUTTON0_PIN
#define BUTTON1 1<<BUTTON1_PIN
#define BUTTON2 1<<BUTTON2_PIN



/* Faz a iniciação do sistema para permitir o acesso aos botões */
void BUTTON_Init(void)
{
	LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0&~(PINMODECFG_PULLDOWN<<BUTTON0_PINCFG)) | PINMODECFG_PULLUP<<BUTTON0_PINCFG;
	LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0&~(PINMODECFG_PULLDOWN<<BUTTON1_PINCFG)) | PINMODECFG_PULLUP<<BUTTON1_PINCFG;
	LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1&~(PINMODECFG_PULLDOWN<<BUTTON2_PINCFG)) | PINMODECFG_PULLUP<<BUTTON2_PINCFG;

	LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0&~(PINMODECFG_PULLDOWN<<BUTTON0_PINCFG)) | PINMODECFG_PULLUP<<BUTTON0_PINCFG;
	LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0&~(PINMODECFG_PULLDOWN<<BUTTON1_PINCFG)) | PINMODECFG_PULLUP<<BUTTON1_PINCFG;
	LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1&~(PINMODECFG_PULLDOWN<<BUTTON2_PINCFG)) | PINMODECFG_PULLUP<<BUTTON2_PINCFG;

	LPC_GPIO0->FIODIR &= ~BUTTON0; //in pins
	LPC_GPIO0->FIODIR &= ~BUTTON1;
	LPC_GPIO0->FIODIR &= ~BUTTON2;
}

/* Devolve o codigo (bitmap) do botão pressionado ou 0 no caso de não existir
qualquer botão pressionado. Não é bloqueante.*/
uint32_t BUTTON_Hit(void)
{
	return ~LPC_GPIO0->FIOPIN & (BUTTON0 | BUTTON1 | BUTTON2);
}

/* Devolve o código (bitmap) do botão pressionado. É bloqueante. */
uint32_t BUTTON_Read(void)
{
	uint32_t bitmap;
	do
	{
		bitmap = BUTTON_Hit();
	}while(!bitmap);
	return bitmap;
}

/* Devolve o código (bitmap) do estado do botão: pressionado (transição),
libertado (transição), repetição (mantém o estado anterior)*/
uint32_t BUTTON_GetButtonsEvents(void)
{
	return 0;
}
