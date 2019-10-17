/*
 * lcd.h
 *
 *  Created on: 17/10/2019
 *      Author: Saturn
 */

#ifndef LCD_H_
#define LCD_H_

void LCDWrite5bits(bool rs, int data4);
void LCDWrite9bits(bool rs, int data8);

void LCDWriteCMD(int cmd8);

void LCDWriteData(int data8);
/* Faz a iniciação do sistema para permitir o acesso ao periférico LCD,
 * utilizando 2 linhas com 16 colunas e comunicação a 4 bits.*/
void LCDText_Init(void);

/* Escreve um carácter na posição corrente do cursor. */
void LCDText_WriteChar(char ch);
/* Escreve uma string na posição corrente do cursor. */
void LCDText_WriteString(char *str);
/* Posiciona o cursor na linha row e coluna column do mostrador. */
void LCDText_Locate(int row, int column);

/* Limpa o visor, usando o comando disponível na API do periférico. */
void LCDText_Clear(void);

/* DESAFIO */
/* Escreve na posição corrente do cursor a string fmt. O formato da string
 *  fmt é idêntico à função printf da biblioteca standard da linguagem C. */
void LCDText_Printf(char *fmt, ...);


#endif /* LCD_H_ */
