/**
* @file		bmp.h
* @brief	Contains the BMP API.
* @version	1.0
* @date		22 Dec 2019
* @author	SE1_1920_i_G8
*/

#ifndef BMP_H_
#define BMP_H_

/** @defgroup BMP BMP
 * This package provides the ability to read the temperature and pressure measured by the BMP and configure it
 * @{
 */

/** @defgroup BMP_Public_Functions BMP Public Functions
 * @{
 */

/**
 * @brief Initializes the BMP
 * @returns Nothing
 * @note This function must be called prior to any other BMP functions.
 */
void BMP_init();

/**
 * @brief Configures the BMP, see the manual for more information for each parameter
 * @returns Nothing
 *
 * @param t_sb: Controls inactive duration t_standby in normal mode. See chapter 3.6.3 for details.
 * @param filter: Controls the time constant of the IIR filter. See chapter 3.3.3 for details.
 * @param spi3w_en: Enables 3-wire SPI interface when set to ‘1’. See chapter 5.3 for details.
 * @param osrs_t: Controls oversampling of temperature data. See chapter 3.3.2 for details.
 * @param osrs_p: Controls oversampling of pressure data. See chapter 3.3.1 for details.
 * @param mode: Controls the power mode of the device. See chapter 3.6 for details.
 */
void BMP_config(char t_sb, char filter, char spi3w_en, char osrs_t, char osrs_p, char mode);

/**
 * @brief Returns the temperature measured by the BMP in celsius or fahrenheit
 * @returns The temperature
 *
 * @param CnF: If true returns temperature in celsius else in fahrenheit
 */
double BMP_getTemperature(bool CnF);

/**
 * @brief Returns the pressure measured by the BMP in Pascal
 * @returns The pressure
 */
double BMP_getPressure();

/**
 * @}
 */

/**
 * @}
 */

#endif /* BMP_H_ */
