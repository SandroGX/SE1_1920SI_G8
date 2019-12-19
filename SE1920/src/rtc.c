/*
 * rtc.c
 *
 *  Created on: 24/10/2019
 *      Author: Saturn
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <time.h>

#define SECONDS 0x3f
#define MINUTES 0x3f
#define HOURS 0x1f
#define DAYOFWEEK 0x7
#define DAYOFMONTH 0x1f
#define DAYOFYEAR 0x1f
#define MON 0xf
#define YR 0xfff

int RTC_GetMonDays(int year, int month)
{
	const int m_days[12] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if(month == 2)
		return (year%4==0 && !year%100==0) || year%400==0 ? 29 : 28;
	else return m_days[month-1];
}

/* Devolve em dateTime o valor corrente do RTC. */
void RTC_GetValue(struct tm *dateTime)
{
	dateTime->tm_sec = LPC_RTC->CTIME0 & SECONDS;
	dateTime->tm_min = LPC_RTC->CTIME0>>8 & MINUTES;
	dateTime->tm_hour = LPC_RTC->CTIME0>>16 & HOURS;
	dateTime->tm_mday = LPC_RTC->CTIME1 & DAYOFMONTH;
	dateTime->tm_wday = LPC_RTC->CTIME0>>24 & DAYOFWEEK;
	dateTime->tm_yday = (LPC_RTC->CTIME2 & DAYOFYEAR) - 1;
	dateTime->tm_mon = (LPC_RTC->CTIME1>>8 & MON) - 1;
	dateTime->tm_year = (LPC_RTC->CTIME1>>16 & YR) - 1900;
}

/* Realiza a atualização do RTC com os valores do parâmetro dateTime. */
void RTC_SetValue(struct tm *dateTime)
{
	LPC_RTC->CCR &= ~1; //disable

	LPC_RTC->SEC = dateTime->tm_sec;
	LPC_RTC->MIN = dateTime->tm_min;
	LPC_RTC->HOUR = dateTime->tm_hour;
	LPC_RTC->DOM = dateTime->tm_mday;
	LPC_RTC->DOW = dateTime->tm_wday;
	LPC_RTC->DOY = dateTime->tm_yday + 1;
	LPC_RTC->MONTH = dateTime->tm_mon + 1;
	LPC_RTC->YEAR = dateTime->tm_year + 1900;

	LPC_RTC->CCR |= 1; //enable
}

/* Realiza a atualização do RTC com o valor do parâmetro seconds, que representa
os segundos desde 00:00:00 UTC de 1 janeiro 1970. */
void RTC_SetSeconds(time_t seconds)
{
	RTC_SetValue(localtime(&seconds));
}

/* Retorna o valor corrente do RTC, em segundos desde 00:00:00 UTC de 1 janeiro
1970. */
time_t RTC_GetSeconds(void)
{
	struct tm dateTime ;
	RTC_GetValue(&dateTime);
	return mktime(&dateTime);
}

/* Faz a iniciação do sistema para permitir o acesso ao periférico RTC. O RTC é
iniciado com o valor do parâmetro seconds, que representa os segundos desde
00:00:00 UTC de 1 janeiro 1970. */
void RTC_Init(time_t seconds)
{
	RTC_SetSeconds(seconds);
}
