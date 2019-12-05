/*
 * flash.c
 *
 *  Created on: 05/12/2019
 *      Author: Saturn
 */


#define IAP_LOCATION 0x1FFF1FF1

typedef void (*IAP)(unsigned int[], unsigned int[]);
IAP iap_entry = (IAP) IAP_LOCATION;

unsigned int freq = 1000;//????

/* Apaga o conteúdo de um sector, ou de múltiplos sectores, da FLASH. Para apagar
apenas um sector, deve usar-se o mesmo número de sector para os dois parâmetros. */
unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector)
{
	unsigned int in[] = { 52, startSector, endSector, freq };
	unsigned int* out = { 0 };

	iap_entry(in, out);

	return &out;
}

/* Escreve o bloco de dados referenciado por srcAddr, de dimensão size bytes, no
endereço da FLASH referenciado por dstAddr. */
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size)
{
	unsigned int in[] = { 50, getSector(dstAddr), getSector(dstAddr+size) };
	unsigned int* out = { 0 };

	iap_entry(in, out);

	unsigned int in2[] = { 51, (unsigned int)dstAddr, (unsigned int)srcAddr, size, freq };
	unsigned int* out2 = { 0 };

	iap_entry(in2, out2);

	return &out2;
}

/* Compara o conteúdo do bloco de dados referenciado por srcAddr, de dimensão size
bytes, com o conteúdo do bloco de dados referenciado por dstAddr. */
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size)
{

}

unsigned int getSector(void *addr)
{
	unsigned int addrU = (unsigned int)addr;

	if(0x0 <= adrrU < 0x10000)
	{
		return (adrrU % 0x1000) / 0x1000;
	}
	else if(0x10000 <= adrrU < 0x80000)
	{
		return ((adrrU % 8000) - 0x10000)/0x8000 + 0x10;
	}
}
