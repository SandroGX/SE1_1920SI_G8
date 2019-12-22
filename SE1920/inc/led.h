/**
* @file		led.h
* @brief	Contains the LED API.
* @version	1.0
* @date		31 Out 2019
* @author	SE1_1920_i_G8
*/

#ifndef LED_H_
#define LED_H_

#include <stdbool.h>


/** @defgroup LED LED
 * This package provides the core capabilities such as on / off the LED in
 * port P0.22 of the LPC1769 from NXP.
 * @{
 */

/** @defgroup LED_Public_Functions LED Public Functions
 * @{
 */

/**
 * @brief	Initializes the LED API
 * @param	state: State of the LED. The 0 indicate led off and 1 LED on.
 * @return	Nothing
 * @note	This function must be called prior to any other LED functions. The
 * LED will started in the value passed in the parameter.
 */
void LED_Init(bool state);

/**
 * @brief	Get LED state.
 * @return	status of LED. The 0 indicate led is off and 1 LED is on.
 */
bool LED_GetState(void);

/**
 * @brief	Turn LED on
 * @return	Nothing
 */
void LED_On(void);

/**
 * @brief	Turn LED off
 * @return	Nothing
 */
void LED_Off(void);

/**
 * @}
 */


/**
 * @}
 */

#endif /* LED_H_ */
