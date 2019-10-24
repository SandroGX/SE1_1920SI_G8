/*
 * time.h
 *
 *  Created on: 26/09/2019
 *      Author: Sandro
 */

#ifndef TIMER_H_
#define TIMER_H_

void wait_init();
uint32_t wait_ms();
uint32_t wait_elapsed(uint32_t time);
void wait(uint32_t milis);

#endif /* TIMER_H_ */
