/*
 * led.c
 *
 *  Created on: 03/10/2019
 *      Author: Saturn
 */


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <stdbool.h>

#define LED_PIN 22
#define LED 1<<LED_PIN

bool LEDstate;

/* Faz a iniciação do sistema para permitir a manipulação do estado LED que
existe na placa de prototipagem LPCXpresso LPC1769. Deixa o LED apagado quando
state toma o valor false ou aceso quando true. */

/* Acende o LED. */
void LED_On(void)
{
	LEDstate = true;
	LPC_GPIO0->FIOSET = LED;
}

/* Apaga o LED. */
void LED_Off(void)
{
	LEDstate = false;
	LPC_GPIO0->FIOCLR = LED;
}

void LED_Init(bool state)
{
	LEDstate = state;
	LPC_GPIO0->FIODIR |= LED; //set out pin

	if(LEDstate)
		LED_On();
	else LED_Off();
}

/* Devolve true se o LED está apagado e false se o LED estiver apagado. */
bool LED_GetState(void)
{
	return LEDstate;
}

<<<<<<< HEAD
/* Acende o LED. */
void LED_On(void)
{
	LEDstate = true;
	LPC_GPIO0->FIOSET = LED;
}

/* Apaga o LED. */
void LED_Off(void)
{
	LEDstate = false;
	LPC_GPIO0->FIOCLR = LED;

	LPC_TIM0->
}
=======
>>>>>>> c79ee9352456d04affea2217a590ce48efa3c230
