/**
* @file		flash.h
* @brief	Contains the Flash API.
* @version	1.0
* @date		22 Dec 2019
* @author	SE1_1920_i_G8
*/

#ifndef FLASH_H_
#define FLASH_H_

/** @defgroup Flash Flash
 * This package provides the ability to write to the Flash
 * @{
 */

/** @defgroup Flash_Public_Functions Flash Public Functions
 * @{
 */

/**
 * @brief Erases contents of flash sectors between startSector and endSector. To erase just one use the same
 * number for both sectors
 * @returns Error code
 *
 * @param startSector: The first sector to erase
 * @param endSector: The last sector to erase
 */
unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector);

/**
 * @brief: Writes contents pointed by srcAddr, of size bytes, to flash address pointed by dstAddr
 * @returns Error code
 *
 * @param dstAddr: Pointer of contents to write to Flash
 * @param srcAddr: Pointer of Flash address to write to
 * @param size: Size of contents in bytes
*/
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size);

/**
 * @brief: Compares contents of data pointed by srcAddr, of size size, with contents
 * pointed by dstAddr.
 * @returns Error code
 *
 * @param dstAddr: Pointer of contents to compare to Flash
 * @param srcAddr: Pointer of Flash contents to compare to
 * @param size: Size of contents in bytes
*/
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size);

/**
 * @}
 */

/**
 * @}
 */

#endif /* FLASH_H_ */
