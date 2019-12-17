/*
===============================================================================
 Name        : lab6.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

#include "flash.h"

int main(void) {

	void *dstAddr = (void*)0x78000;
	unsigned int size = 256;
	char sentence[256] = "Hello World, how are you? ABCDEFGHIJKLMNOP";

	int error;
	if((error = FLASH_EraseSectors(29, 29)))
		printf("ERASE ERROR %d\n", error);
	else if((error = FLASH_WriteData(dstAddr, (void*)sentence, size)))
		printf("WRITE ERROR %d\n", error);

	printf("Sentence: %s\n", (char*)dstAddr);

	char sentence2[256] = "GOODBYE";
	if((error = FLASH_WriteData(dstAddr, (void*)sentence2, 7)))
		printf("WRITE ERROR %d\n", error);

	printf("Sentence2: %s\n", (char*)dstAddr);

	if((error = FLASH_VerifyData(dstAddr, sentence, size)))
		printf("VERIFY ERROR %d\n", error);
	else if((error = FLASH_EraseSectors(29, 29)))
		printf("ERASE ERROR %d\n", error);
}
