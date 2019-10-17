/*
 * wait.h
 *
 *  Created on: 10/10/2019
 *      Author: Saturn
 */

#ifndef WAIT_H_
#define WAIT_H_

void WAIT_Init(void);

/* Espera em microsegundos o valor passado no parâmetro. */
void WAIT_ChronoUs(uint32_t waitUs);

#endif /* WAIT_H_ */
