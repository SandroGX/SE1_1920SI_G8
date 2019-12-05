/*
 * bmp.h
 *
 *  Created on: 28/11/2019
 *      Author: Saturn
 */

#ifndef BMP_H_
#define BMP_H_

void BMP_init();


void BMP_config(char t_sb, char filter, char spi3w_en, char osrs_t, char osrs_p, char mode);


double getTemperature();

double getPressure();


#endif /* BMP_H_ */
