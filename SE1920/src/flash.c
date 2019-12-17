/*
 * flash.c
 *
 *  Created on: 05/12/2019
 *      Author: Saturn
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define IAP_LOCATION 0x1FFF1FF1

typedef void (*IAP)(unsigned int[], unsigned int[]);
IAP iap_entry = (IAP)IAP_LOCATION;

#define PrepareWrite 50
#define RAM2FLASH 51
#define Erase 52
#define Compare 56

#define SECTOR_SIZE 4096
#define FREQ 100000//????

unsigned int getSector(void *addr);
unsigned int getWriteSize(unsigned int size);

/* Apaga o conteúdo de um sector, ou de múltiplos sectores, da FLASH. Para apagar
apenas um sector, deve usar-se o mesmo número de sector para os dois parâmetros. */
unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector)
{
	unsigned int in[3] = { PrepareWrite, startSector, endSector };
	unsigned int out[1] = { 0 };

	iap_entry(in, out);

	if(*out)
		return *out;

	unsigned int in2[4] = { Erase, startSector, endSector, FREQ };

	iap_entry(in2, out);

	return *out;
}

/* Escreve o bloco de dados referenciado por srcAddr, de dimensão size bytes, no
endereço da FLASH referenciado por dstAddr. */
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size)
{
	void* copy = malloc(SECTOR_SIZE);
	memcpy(copy, dstAddr, SECTOR_SIZE);
	memcpy(copy, srcAddr, size);

	FLASH_EraseSectors(getSector(dstAddr), getSector(dstAddr));

	unsigned int in[3] = { PrepareWrite, getSector(dstAddr), getSector(dstAddr) };
	unsigned int out[1] = { 0 };

	iap_entry(in, out);

	if(*out)
		return *out;

	unsigned int in2[5] = { RAM2FLASH, (unsigned int)dstAddr, (unsigned int)copy, SECTOR_SIZE, FREQ };

	iap_entry(in2, out);

	free(copy);

	return *out;
}

/* Compara o conteúdo do bloco de dados referenciado por srcAddr, de dimensão size
bytes, com o conteúdo do bloco de dados referenciado por dstAddr. */
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size)
{
	unsigned int in[4] = { Compare, (unsigned int)dstAddr, (unsigned int)srcAddr, size - (size%4) };
	unsigned int out[2] = { 0 , 0 };

	iap_entry(in, out);

	return *out;
}

unsigned int getSector(void *addr)
{
	unsigned int addrU = (unsigned int)addr;

	if (0x0 <= addrU && addrU < 0x10000)
	{
		return (addrU - addrU % 0x1000) / 0x1000;
	}
	else if (0x10000 <= addrU && addrU < 0x80000)
	{
		addrU -= 0x10000;
		return (addrU - addrU % 0x8000)/0x8000 + 0x10;
	}
	return 0;
}

unsigned int getWriteSize(unsigned int size)
{
	if(size <= 256)
		return 256;
	else if(size <= 512)
		return 512;
	else if(size <= 1024)
		return 1024;
	else if(size <= 4096)
		return 4096;
	else return 0;
}

unsigned int getSectorSize(void *addr)
{
	unsigned int addrU = (unsigned int)addr;

	if (0x0 <= addrU && addrU < 0x10000)
	{
		return 4098;
	}
	else if (0x10000 <= addrU && addrU < 0x80000)
	{
		addrU -= 0x10000;
		return (addrU - addrU % 0x8000)/0x8000 + 0x10;
	}
	return 0;
}
