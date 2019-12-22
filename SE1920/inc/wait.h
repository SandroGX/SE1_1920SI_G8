/**
* @file		wait.h
* @brief	Contains the timer API.
* @version	1.1
* @date		31 Out 2019
* @author	SE1_1920_i_G8
*/

#ifndef WAIT_H_
#define WAIT_H_

/** @defgroup WAIT Wait
 * This package provides the core capabilities for wait functions.
 * @{
 */


/** @defgroup WAIT_Public_Functions Wait Public Functions
 * @{
 */

/**
 * @brief	Initialises the wait API for 1 microseconds resolution.
 * @note	This function must be called prior to any other Timer functions.
 */
void WAIT_Init(void);

/**
 * @brief	Waits a number of microseconds.
 * @param	waitUs: The whole number of microseconds to wait.
 */
void WAIT_ChronoUs(uint32_t waitUs);

/**
 * @}
 */


/**
 * @}
 */

#endif /* WAIT_H_ */
