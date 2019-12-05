#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#define minFreq 390625
#define maxFreq 100000000

/* Faz a iniciação do controlador e configura os respetivos pinos. */
void SPI_Init(void) {
	//pin config
	//LPC_PINCON->PINSEL1 = 0b00 | (LPC_PINCON->PINSEL1 & ~(0b11)); //Slave chip select
	LPC_PINCON->PINSEL1 = 0b11<<2 | (LPC_PINCON->PINSEL1 & ~(0b11<<2)); //MISO
	LPC_PINCON->PINSEL1 = 0b11<<4 | (LPC_PINCON->PINSEL1 & ~(0b11<<4)); //MOSI
	LPC_PINCON->PINSEL0 = 0b11<<30 | (LPC_PINCON->PINSEL0 & ~(0b11<<30)); //CLK

	//LPC_GPIO0->FIOSET = 1<<16; //clear slave chip select
	//LPC_GPIO0 ->FIODIR |= 1<<16; //out


	//spi config
	LPC_SPI->SPCR |= 1<<2; //bitEnable
	LPC_SPI->SPCR |= 1<<5; //set master
	LPC_SPI->SPCR &= ~(1<<6); //lsbf
	LPC_SPI->SPCR |= 1<<7; //spie

	//clock stuff
	LPC_SC->PCLKSEL0 = 0b01<<2 | (LPC_SC->PCLKSEL0 & ~(0b11<<2)); //set SCLK equals to cpu clock
}

//min 390625 Hz max 100M Hz
/* Configura o ritmo de envio/receção, o numero de bits de dados e o modo (CPOL, CPHA). */
void SPI_ConfigTransfer(int frequency, int bitData, int mode) {
	frequency = frequency > maxFreq ? maxFreq : frequency;
	frequency = frequency < minFreq ? minFreq : frequency;
	int divider = maxFreq/frequency;

	divider -= divider % 2; //make pair
	LPC_SPI->SPCCR = (divider & 0xff) | (LPC_SPI->SPCCR & ~(0xff));

	if(bitData == 16)
		bitData = 0;

	LPC_SPI->SPCR = bitData<<8 | (LPC_SPI->SPCR & ~(0b1111<<8));

	LPC_SPI->SPCR = mode<<3 | (LPC_SPI->SPCR & ~(0b11<<3));
}

/* Realiza uma transferência. Retorna sucesso ou erro na transferência. */
int SPI_Transfer(unsigned short *txBuffer, unsigned short *rxBuffer, int length)
{
	//LPC_GPIO0->FIOCLR = 1<<16; //set chip select
	for(int i = 0; i < length; ++i) {
		LPC_SPI->SPDR = txBuffer[i];

		while(!(LPC_SPI->SPSR));
		if(!(LPC_SPI->SPSR & 1<<7))
			return -1;

		rxBuffer[i] = LPC_SPI->SPDR;
	}
	//LPC_GPIO0->FIOSET = 1<<16; //clear chip select

	return 0;
}

/* Realiza uma transferência. Retorna sucesso ou erro na transferência. buffer com unidade de um byte*/
int SPI_Transfer8(unsigned char *txBuffer, unsigned char *rxBuffer, int length)
{
	//LPC_GPIO0->FIOCLR = 1<<16; //set chip select
	for(int i = 0; i < length; ++i) {
		LPC_SPI->SPDR = txBuffer[i];

		while(!(LPC_SPI->SPSR));
		if(!(LPC_SPI->SPSR & 1<<7))
			return -1;

		rxBuffer[i] = LPC_SPI->SPDR;
	}
	//LPC_GPIO0->FIOSET = 1<<16; //clear chip select

	return 0;
}
