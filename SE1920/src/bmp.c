#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "spi.h"

typedef long signed int BMP280_S32_t;

#define dig_T1_address 0x88
unsigned short dig_T1;

#define dig_T2_address 0x8A
signed short dig_T2;

#define dig_T3_address 0x8C
signed short dig_T3;

#define dig_P1_address 0x8E
unsigned short dig_P1;

#define dig_P2_address 0x90
signed short dig_P2;

#define dig_P3_address 0x92
signed short dig_P3;

#define dig_P4_address 0x94
signed short dig_P4;

#define dig_P5_address 0x96
signed short dig_P5;

#define dig_P6_address 0x98
signed short dig_P6;

#define dig_P7_address 0x9A
signed short dig_P7;

#define dig_P8_address 0x9C
signed short dig_P8;

#define dig_P9_address 0x9E
signed short dig_P9;

#define SPI_FREQ 10000000
#define SPI_nBITS 8
#define SPI_MODE 0

signed short readSignedShort(char reg);
unsigned short readUnsignedShort(char reg);
void spiConfig();

void BMP_init(){
	LPC_PINCON->PINSEL1 = 0b00 | (LPC_PINCON->PINSEL1 & ~(0b11)); //Slave chip select

	LPC_GPIO0->FIOSET = 1<<16; //clear slave chip select
	LPC_GPIO0 ->FIODIR |= 1<<16; //out

	dig_T1 = readUnsignedShort(dig_T1_address);
	dig_T2 = readSignedShort(dig_T2_address);
	dig_T3 = readSignedShort(dig_T3_address);
	dig_P1 = readUnsignedShort(dig_P1_address);
	dig_P2 = readSignedShort(dig_P2_address);
	dig_P3 = readSignedShort(dig_P3_address);
	dig_P4 = readSignedShort(dig_P4_address);
	dig_P5 = readSignedShort(dig_P5_address);
	dig_P6 = readSignedShort(dig_P6_address);
	dig_P7 = readSignedShort(dig_P7_address);
	dig_P8 = readSignedShort(dig_P8_address);
	dig_P9 = readSignedShort(dig_P9_address);
}

unsigned char* spiRead(char reg, int length)
{
	unsigned char *txBuffer = malloc(length*sizeof(unsigned char)+1);
	unsigned char *rxBuffer = malloc(length*sizeof(unsigned char)+1);

	txBuffer[0] = (1<<7) | reg; //read ID

	spiConfig();
	LPC_GPIO0->FIOCLR = 1<<16; //set chip select
	SPI_Transfer8(txBuffer, rxBuffer, length + 1);
	LPC_GPIO0->FIOSET = 1<<16; //clear chip select

	free(txBuffer);

	return rxBuffer+1;
}

signed short readSignedShort(char reg)
{
	unsigned char* p = spiRead(reg, sizeof(signed short));
	signed short val = *((signed short*)p);
	free(p);
	return val;
}

unsigned short readUnsignedShort(char reg)
{
	unsigned char* p = spiRead(reg, sizeof(unsigned short));
	unsigned short val = *((unsigned short*)p);
	free(p);
	return val;
}

BMP280_S32_t readAdc(char reg)
{
	unsigned char* p = spiRead(reg, 3);
	BMP280_S32_t adc = (int)p[0]<<12 | (int)p[1]<<4 | (int)p[2]>>4;
	free(p);
	return adc;
}

void spiWrite(unsigned char* txBuffer, int length)
{
	unsigned char *rxBuffer = malloc(length*sizeof(char));
	spiConfig();
	LPC_GPIO0->FIOCLR = 1<<16; //set chip select
	SPI_Transfer8(txBuffer, rxBuffer, length);
	LPC_GPIO0->FIOSET = 1<<16; //clear chip select
	free(rxBuffer);
}

void BMP_config(unsigned char t_sb, unsigned char filter, unsigned char spi3w_en, unsigned char osrs_t, unsigned char osrs_p, unsigned char mode)
{
	unsigned char *txBuffer = malloc(4*sizeof(unsigned char));

	txBuffer[0] = 0x7f & 0xF5; //register
	txBuffer[1] = (t_sb & 0x7)<<5 | (filter & 0x7)<<2 | (spi3w_en & 1);//data
	txBuffer[2] = 0x7f & 0xF4; //register
	txBuffer[3] = (osrs_t & 0x7)<<5 | (osrs_p & 0x7)<<2 | (mode & 3);//data

	spiWrite(txBuffer, 2);
	spiWrite(txBuffer+2, 2);

	free(txBuffer);
}

void spiConfig(){
	SPI_ConfigTransfer(SPI_FREQ, SPI_nBITS, SPI_MODE);
}

// Returns temperature in DegC, double precision. Output value of “51.23” equals 51.23 DegC.
// t_fine carries fine temperature as global value
BMP280_S32_t t_fine;

double bmp280_compensate_T_double(BMP280_S32_t adc_T)
{
	double var1, var2, T;
	var1 = (((double)adc_T)/16384.0-((double)dig_T1)/1024.0)*((double)dig_T2);
	var2 = ((((double)adc_T)/131072.0-((double)dig_T1)/8192.0)*(((double)adc_T)/131072.0-((double) dig_T1)/8192.0))*((double)dig_T3);
	t_fine = (BMP280_S32_t)(var1 + var2);
	T = (var1 + var2) / 5120.0;
	return T;
}

// Returns pressure in Pa as double. Output value of “96386.2” equals 96386.2 Pa = 963.862 hPa
double bmp280_compensate_P_double(BMP280_S32_t adc_P)
{
	double var1, var2, p;
	var1 = ((double)t_fine/2.0)-64000.0;
	var2 = var1 * var1* ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2/4.0)+(((double)dig_P4) * 65536.0);
	var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double)dig_P1);
	if(var1 == 0.0){
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576.0 - ((double)adc_P);
	p = (p -(var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double)dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double)dig_P8) / 32768.0;
	p = p + (var1 + var2 + ((double)dig_P7)) / 16.0;
	return p;
}

double getTemperature(bool CnotF)
{
	BMP280_S32_t adc_T = readAdc(0xfa);
	double value = bmp280_compensate_T_double(adc_T);
	return CnotF ? value : (value * 1.8 + 32);
}

double getPressure()
{
	BMP280_S32_t adc_P = readAdc(0xf7);
	return bmp280_compensate_P_double(adc_P);
}
