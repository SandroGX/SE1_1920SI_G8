/*
 * flash.h
 *
 *  Created on: 12/12/2019
 *      Author: Saturn
 */

#ifndef FLASH_H_
#define FLASH_H_

unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector);

/* Escreve o bloco de dados referenciado por srcAddr, de dimensão size bytes, no
endereço da FLASH referenciado por dstAddr. */
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size);

/* Compara o conteúdo do bloco de dados referenciado por srcAddr, de dimensão size
bytes, com o conteúdo do bloco de dados referenciado por dstAddr. */
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size);

#endif /* FLASH_H_ */
