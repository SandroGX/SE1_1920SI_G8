#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdbool.h>

#include "time.h"
#include "wait.h"

#define RS 1<<6
#define E 1<<7
#define DB7 1<<12
#define DB6 1<<11
#define DB5 1<<10
#define DB4 1<<8

void LCDWrite5bits(bool rs, int data4) {
	if (rs) {
		LPC_GPIO2->FIOSET = RS;
	} else {
		LPC_GPIO2->FIOCLR = RS;
	}

	LPC_GPIO2->FIOCLR = DB7|DB6|DB5|DB4;

	LPC_GPIO2->FIOSET = ((data4&1)<<8)|((data4&0x0e)<<9);


	LPC_GPIO2->FIOSET = E;
	WAIT_ChronoUs(6);
	//wait(15);
	LPC_GPIO2->FIOCLR = E;
	WAIT_ChronoUs(6);
	//wait(15);
}

void LCDWrite9bits(bool rs, int data8) {
	LCDWrite5bits(rs,data8>>4);
	LCDWrite5bits(rs,data8);
	WAIT_ChronoUs(100);
	//wait(15);
}

void LCDWriteCMD(int cmd8) {
	LCDWrite9bits(false,cmd8);
}

void LCDWriteData(int data8) {
	LCDWrite9bits(true,data8);
}


/* Escreve um carácter na posição corrente do cursor. */
void LCDText_WriteChar(char ch) {
	if (ch != 0)
		LCDWriteData(ch);
}

/* Escreve uma string na posição corrente do cursor. */
void LCDText_WriteString(char *str) {
	int i = 0;
	while(*(str+i) != '\0') {
		LCDText_WriteChar(*(str+i));
		++i;
	}
}

/* Posiciona o cursor na linha row e coluna column do mostrador. */
void LCDText_Locate(int row, int column) {
	if(row == 1)
		LCDWriteCMD(192 + column);
	else LCDWriteCMD(128 + column);
}

//N: number of display lines, 0 = 1, 1 = 2
//F: character font,
void LCD_FuntionSet(bool N, bool F)
{
	uint32_t c = 0b100000;

	if(N) c |= 0b1000;
	if(F) c |= 0b100;
	LCDWriteCMD(c);
}

//D: display on
//C: display cursor
//B: blinking cursor
void LCD_Control(bool D, bool C, bool B)
{
	uint32_t c = 0b1000;

	if(D) c |= 0b100;
	if(C) c |= 0b10;
	if(B) c |= 1;
	LCDWriteCMD(c);
}

/* Limpa o visor, usando o comando disponível na API do periférico. */
void LCDText_Clear(void){
	LCDWriteCMD(1);
	wait(5);
}

//ID: increment/decrement DDRAM
//S: shift display
void LCD_EntryModeSet(bool ID, bool S)
{
	uint32_t c = 0b100;
	if(ID)
		c |= 2;
	if(S)
		c |= 1;
	LCDWriteCMD(c);

}

/* DESAFIO */
/* Escreve na posição corrente do cursor a string fmt. O formato da string
 *  fmt é idêntico à função printf da biblioteca standard da linguagem C. */
void LCDText_Printf(char *fmt, ...){

}

/* Faz a iniciação do sistema para permitir o acesso ao periférico LCD,
 * utilizando 2 linhas com 16 colunas e comunicação a 4 bits.*/
void LCDText_Init(void){
	//power on
	wait(20); //wait more than 15 ms
	LPC_GPIO2->FIODIR |= RS;
	LPC_GPIO2->FIODIR |= DB7;
	LPC_GPIO2->FIODIR |= DB6;
	LPC_GPIO2->FIODIR |= DB5;
	LPC_GPIO2->FIODIR |= DB4;
	LPC_GPIO2->FIODIR |= E;

	LCDWrite5bits(false,0b0011);

	wait(10); //wait more than 4.1 ms

	LCDWrite5bits(false, 0b0011);

	wait(15); //wait more than 100 ys

	LCDWrite5bits(false, 0b0011);
	WAIT_ChronoUs(80);
	//wait(15);

	LCDWrite5bits(false, 0b0010);
	WAIT_ChronoUs(80);
	//wait(15);

	LCD_FuntionSet(true, false);

	LCD_Control(false, true, true);

	LCDText_Clear();

	LCD_EntryModeSet(true, false);
}
