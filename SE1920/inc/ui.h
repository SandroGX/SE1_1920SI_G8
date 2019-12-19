/*
 * ui.h
 *
 *  Created on: 10/12/2019
 *      Author: Saturn
 */

#ifndef UI_H_
#define UI_H_

typedef void (*MenuFunc)(void);
typedef struct Menu {
	char *name;
	MenuFunc menu;
} Menu;


int UI_SelectOptions(char* options[], int count);
void UI_SelectMenu(Menu menu[], int count);
void UI_StartMenu(Menu menu[], int count, int init);
int UI_Digit(int l, int c, int min, int max, int initVal,int maxDigits);
int UI_Number(int l, int c, int min, int max, int initVal, int maxDigits);
void UI_DisplayTime(int l, int c);
void UI_SetTime(int l, int c);

#endif /* UI_H_ */
