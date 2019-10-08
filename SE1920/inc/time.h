/*
 * time.h
 *
 *  Created on: 26/09/2019
 *      Author: Sandro
 */

#ifndef TIME_H_
#define TIME_H_

void wait_init();
uint32_t wait_ms();
uint32_t wait_elapsed(uint32_t time);
void wait(uint32_t milis);

#endif /* TIME_H_ */
