/**
* @file		timer.h
* @brief	Contains the LCD API.
* @version	1.0
* @date		31 Out 2019
* @author	SE1_1920_i_G8
*/

#ifndef TIMER_H_
#define TIMER_H_

/** @defgroup Timer Timer
 * This package provides the core capabilities for wait functions.
 * @{
 */

/** @defgroup Timer_Public_Functions Timer Public Functions
 * @{
 */

/**
 * @brief	Initialises the wait API for 1 ms resolution.
 * @note	This function must be called prior to any other WAIT functions.
 */
void wait_init();

/**
 * @brief	Returns the number of milliseconds since the this was initialized.
 */
uint32_t wait_ms();

/**
 * @brief	Returns the time elapsed since the time passed as parameter
 * @param	time: Point in time from which we wanna know how much time passed
 * @returns The time elapsed since the time passed as parameter
 */
uint32_t wait_elapsed(uint32_t time);

/**
 * @brief	Waits a number of milliseconds.
 * @param	milis: The whole number of milliseconds to wait.
 */
void wait(uint32_t milis);

/**
 * @}
 */


/**
 * @}
 */

#endif /* TIMER_H_ */
