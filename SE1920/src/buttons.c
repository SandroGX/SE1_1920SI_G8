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

#define UPBUTTON_PIN 2
#define DOWNBUTTON_PIN 3
#define ENTERBUTTON_PIN 21

//mod 16 because they may be in different registers
#define UPBUTTON_PINCFG (UPBUTTON_PIN%16)*2
#define DOWNBUTTON_PINCFG (DOWNBUTTON_PIN%16)*2
#define ENTERBUTTON_PINCFG (ENTERBUTTON_PIN%16)*2

#define UPBUTTON 1<<UPBUTTON_PIN
#define DOWNBUTTON 1<<DOWNBUTTON_PIN
#define ENTERBUTTON 1<<ENTERBUTTON_PIN



/* Faz a iniciação do sistema para permitir o acesso aos botões */
void BUTTON_Init(void)
{
	LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0&~(PINMODECFG_PULLDOWN<<UPBUTTON_PINCFG)) | PINMODECFG_PULLUP<<UPBUTTON_PINCFG;
	LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0&~(PINMODECFG_PULLDOWN<<DOWNBUTTON_PINCFG)) | PINMODECFG_PULLUP<<DOWNBUTTON_PINCFG;
	LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1&~(PINMODECFG_PULLDOWN<<ENTERBUTTON_PINCFG)) | PINMODECFG_PULLUP<<ENTERBUTTON_PINCFG;

	LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0&~(PINMODECFG_PULLDOWN<<UPBUTTON_PINCFG)) | PINMODECFG_PULLUP<<UPBUTTON_PINCFG;
	LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0&~(PINMODECFG_PULLDOWN<<DOWNBUTTON_PINCFG)) | PINMODECFG_PULLUP<<DOWNBUTTON_PINCFG;
	LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1&~(PINMODECFG_PULLDOWN<<ENTERBUTTON_PINCFG)) | PINMODECFG_PULLUP<<ENTERBUTTON_PINCFG;

	LPC_GPIO0->FIODIR &= ~UPBUTTON; //in pins
	LPC_GPIO0->FIODIR &= ~DOWNBUTTON;
	LPC_GPIO0->FIODIR &= ~ENTERBUTTON;
}

/* Devolve o codigo (bitmap) do botão pressionado ou 0 no caso de não existir
qualquer botão pressionado. Não é bloqueante.*/
uint32_t BUTTON_Hit(void)
{
	return ~LPC_GPIO0->FIOPIN & (UPBUTTON | DOWNBUTTON | ENTERBUTTON);
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

/* Espera ate nenhum botao esteja pressionado*/
void BUTTON_WaitNoneHit(void){
	while(BUTTON_Hit() != 0);
}
