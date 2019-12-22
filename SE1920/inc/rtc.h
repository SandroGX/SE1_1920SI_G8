/**
* @file		rtc.h
* @brief	Contains the timer API.
* @version	1.1
* @date		31 Out 2019
* @author	SE1_1920_i_G8
*/

#ifndef RTC_H_
#define RTC_H_

int RTC_GetMonDays(int year, int month);

/** @defgroup RTC
 * This package provides the core capabilities to manipulate Real Time Clock of the processor board
 * @{
 */

/** @defgroup RTC_Public_Functions RTC Public Functions
 * @{
 */

/**
 * @brief Returns in dateTime the current value of RTC
 * @param dateTime: Pointer to struct tm we wanna affect
 */
void RTC_GetValue(struct tm *dateTime);

/**
 * @brief Sets in dateTime the value of RTC
 * @param dateTime: Pointer to struct tm we wanna affect RTC with
 */
void RTC_SetValue(struct tm *dateTime);

/**
 * @brief Sets in dateTime the value of RTC
 * @param seconds: Time in seconds since january 1st 1970 00:00:00 UTC
 */
void RTC_SetSeconds(time_t seconds);

/**
 * @brief Returns the current value of RTC
 * @returns Time in seconds since january 1st 1970  00:00:00 UTC
 */
time_t RTC_GetSeconds(void);

/**
 * @brief Initializes the system to access RTC, initiating it with parameter seconds
 * @param seconds: Time in seconds since january 1st 1970  00:00:00 UTC
 */
void RTC_Init(time_t seconds);

/**
 * @}
 */

/**
 * @}
 */
#endif /* RTC_H_ */
