/*
 * led.h
 *
 *  Created on: 03/10/2019
 *      Author: Saturn
 */

#ifndef LED_H_
#define LED_H_

/* Faz a iniciação do sistema para permitir a manipulação do estado LED que
existe na placa de prototipagem LPCXpresso LPC1769. Deixa o LED apagado quando
state toma o valor false ou aceso quando true. */
void LED_Init(bool state);

/* Devolve true se o LED está apagado e false se o LED estiver apagado. */
bool LED_GetState(void);

/* Acende o LED. */
void LED_On(void);

/* Apaga o LED. */
void LED_Off(void);

#endif /* LED_H_ */
