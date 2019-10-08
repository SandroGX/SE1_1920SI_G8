/*
 * buttons.h
 *
 *  Created on: 03/10/2019
 *      Author: Saturn
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_


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
void BUTTON_Init(void);

/* Devolve o codigo (bitmap) do botão pressionado ou 0 no caso de não existir
qualquer botão pressionado. Não é bloqueante.*/
int BUTTON_Hit(void);

/* Devolve o código (bitmap) do botão pressionado. É bloqueante. */
int BUTTON_Read(void);

/* Devolve o código (bitmap) do estado do botão: pressionado (transição),
libertado (transição), repetição (mantém o estado anterior)*/
int BUTTON_GetButtonsEvents(void);

#endif /* BUTTONS_H_ */
