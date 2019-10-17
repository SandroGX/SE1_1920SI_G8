
#define RS 1<<6
#define E 1<<7
#define DB7 1<<12
#define DB6 1<<11
#define DB5 1<<10
#define DB4 1<<8

void LCDWrite5bits(bool rs, int data4){
	if(rs){
		LPC_GPIO2->FIOSET = RS;
	} else{
		LPC_GPIO2->FIOCLR = RS;
	}
	if(data4 & (1<<3)){
		LPC_GPIO2->FIOSET = DB7;
	} else{
		LPC_GPIO2->FIOCLR = DB7;
	}
	if(data4 & (1<<2)){
		LPC_GPIO2->FIOSET = DB6;
	} else{
		LPC_GPIO2->FIOCLR = DB6;
	}
	if(data4 & (1<<1)){
		LPC_GPIO2->FIOSET = DB5;
	} else{
		LPC_GPIO2->FIOCLR = DB5;
	}
	if(data4 & 1){
		LPC_GPIO2->FIOSET = DB4;
	} else{
		LPC_GPIO2->FIOCLR = DB4;
	}
	LPC_GPIO2->FIOSET = E;
	LPC_GPIO2->FIOCLR = E;
}

void LCDWrite9bits(bool rs, int data8){
	LCDWrite5bits(rs,data8>>4);
	LCDWrite5bits(rs,data8);
}

void LCDWriteCMD(int cmd8){
	LCDWrite9bits(false,cmd8);
}

void LCDWriteData(int data8){
	LCDWrite9bits(true,cmd8);
}

/* Faz a iniciação do sistema para permitir o acesso ao periférico LCD,
 * utilizando 2 linhas com 16 colunas e comunicação a 4 bits.*/
void LCDText_Init(void){
	//power on
	Wait(20); //wait more than 15 ms
	LPC_GPIO2->FIODIR |= RS;
	LPC_GPIO2->FIODIR |= DB7;
	LPC_GPIO2->FIODIR |= DB6;
	LPC_GPIO2->FIODIR |= DB5;
	LPC_GPIO2->FIODIR |= DB4;
	LPC_GPIO2->FIODIR |= E;

	LCDWrite5bits(false,0b0011);

	Wait(5); //wait more than 4.1 ms

	LCDWrite5bits(false, 0b0011);

	Wait(1); //wait more than 100 ys

	LCDWrite5bits(false, 0b0011);

	LCDWrite5bits(false, 0b0010);

	LCDWrite5bits(false, 0b1110);

	LCDWrite5bits(false, 0b0000);

	LCDWrite5bits(false, 0b1000);

	LCDWrite5bits(false, 0b0000);

	LCDWrite5bits(false, 0b0001);

	LCDWrite5bits(false,0b0000);

	LCDWrite5bits(false, 0b0110);
}

/* Escreve um carácter na posição corrente do cursor. */
void LCDText_WriteChar(char ch){
	if(ch != 0){
		LCDWriteData(ch);
	}
}

/* Escreve uma string na posição corrente do cursor. */
void LCDText_WriteString(char *str){
	int i = 0;
	while(*(str+i) != '\0'){
		LCDText_WriteChar(*(str+i));
	}
}

/* Posiciona o cursor na linha row e coluna column do mostrador. */
void LCDText_Locate(int row, int column){
	if(row == 1){
		LCDWriteCMD(192 + column);
	} else writeCMD(128 + column);
}

/* Limpa o visor, usando o comando disponível na API do periférico. */
void LCDText_Clear(void){
	LCD_WriteCMD(1);
	LCDText_Locate(0,0);
}

/* DESAFIO */
/* Escreve na posição corrente do cursor a string fmt. O formato da string
 *  fmt é idêntico à função printf da biblioteca standard da linguagem C. */
void LCDText_Printf(char *fmt, ...){

}
