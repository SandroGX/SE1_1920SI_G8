/**
* @file		rtc.h
* @brief	Contains the timer API.
* @version	1.1
* @date		31 Out 2019
* @author	SE1_1920_i_G8
*/

#ifndef RTC_H_
#define RTC_H_

/** @defgroup RTC
 * This package provides the core capabilities to manipulate Real Time Clock of the processor board
 * @{
 */

/** @defgroup RTC_Public_Functions RTC Public Functions
 * @{
 */

/**
 * @brief returns in dateTime the current value of RTC
 * @param dateTime: pointer to struct tm we wanna affect
 */
void RTC_GetValue(struct tm *dateTime);

/**
 * @brief sets in dateTime the value of RTC
 * @param dateTime: pointer to struct tm we wanna affect RTC with
 */
void RTC_SetValue(struct tm *dateTime);

/**
 * @brief sets in dateTime the value of RTC
 * @param seconds: time in seconds since january 1st 1970 00:00:00 UTC
 */
void RTC_SetSeconds(time_t seconds);

/**
 * @brief returns the current value of RTC
 * @returns time in seconds since january 1st 1970  00:00:00 UTC
 */
1970. */
time_t RTC_GetSeconds(void);

/**
 * @brief initializes the system to access RTC, initiating it with parameter seconds
 * @param seconds: time in seconds since january 1st 1970  00:00:00 UTC
 */
void RTC_Init(time_t seconds);

/**
 * @}
 */

/**
 * @}
 */
#endif /* RTC_H_ */
