/**
* @file		spi.h
* @brief	Contains the SPI API.
* @version	1.0
* @date		22 Dec 2019
* @author	SE1_1920_i_G8
*/

/** @defgroup SPI SPI
 * This package provides the ability to communicate with other devices via SPI
 * @{
 */

/** @defgroup SPI_Public_Functions SPI Public Functions
 * @{
 */

/**
 * @brief Initializes the controller and configures the respective pins
 * @returns Nothing
 * @note This function must be called prior to any other SPI functions.
 */
void SPI_Init(void);

/**
 * @brief Configures the rhythm of transfer, the number of bits per transfer and mode (CPOL, CPHA)
 * @returns Nothing
 *
 * @param frequency: The frequency of SPI. Min: 390625 Hz Max: 100M Hz
 * @param bitData: Number of bits per transfer
 * @param mode: Controls the clock phase and polarity
 */
void SPI_ConfigTransfer(int frequency, int bitData, int mode);

/**
 * @brief Does a transfer
 * @returns Success or error in transfer
 *
 * @param txBuffer: Buffer of data to transfer to slave
 * @param rxBuffer: Buffer of data received by master
 * @param length: The number of transfers
 */
int SPI_Transfer(unsigned short *txBuffer, unsigned short *rxBuffer, int length);

/**
 * @brief Does a transfer, with 8 bits of data per transfer
 * @returns Success or error in transfer
 *
 * @param txBuffer: Buffer of data to transfer to slave
 * @param rxBuffer: Buffer of data received by master
 * @param length: The number of transfers
 */
int SPI_Transfer8(unsigned char *txBuffer, unsigned char *rxBuffer, int length);

/**
 * @}
 */

/**
 * @}
 */
