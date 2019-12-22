/**
* @file		ui.h
* @brief	Contains the UI API.
* @version	1.0
* @date		22 Dec 2019
* @author	SE1_1920_i_G8
*/

#ifndef UI_H_
#define UI_H_

/** @defgroup UI UI
 * This package provides the funtions to program a UI
 * @{
 */

/** @defgroup UI_Public_Functions UI Public Functions
 * @{
 */

/**
 * @brief Represents a unction run by a menu
 */
typedef void (*MenuFunc)(void);

/**
 * @brief Represents a menu
 */
typedef struct Menu {
	char *name; /**< The name of the menu */
	MenuFunc menu; /**< The function run by the menu */
} Menu;

/**
 * @brief Allows user to choose an option
 * @returns The index of the chosen option
 *
 * @param options: A string array with the name of the options
 * @param count: The number of options
 */
int UI_SelectOptions(char* options[], int count);

/**
 * @brief Allows user to choose a menu, once the user leaves the number it will return here to choose another one
 * @returns The index of the chosen menu
 *
 * @param menu: A Menu array with the menus to choose from
 * @param count: The number of menus
 */
void UI_SelectMenu(Menu menu[], int count);

/**
 * @brief Allows user to choose a menu, but starts by running at the menu of index init
 * @returns Nothing
 *
 * @param menu: A Menu array with the menus to choose from
 * @param count: The number of menus
 * @param init: The starting menu
 */
void UI_StartMenu(Menu menu[], int count, int init);

/**
 * @brief Allows user to choose a number. The user can increase or decrease the number using the up and down buttons
 * and choose the number pressing enter button
 * @returns The number chosen by user
 *
 * @param l: The line where number is presented
 * @param c: The column of the leftmost digit of number
 * @param min: The minimum value of number
 * @param max: The maximum value of number
 * @param initVal: The initial value to present
 * @param maxDigits: The maximum number of digits of the number
 */
int UI_Digit(int l, int c, int min, int max, int initVal,int maxDigits);

/**
 * @brief Allows user to choose a number.
 * The user can increase or decrease a digit of the number using the up and down buttons,
 * and go to the next digit pressing enter button. If it is last digit it ends the process
 * @returns The number chosen by user
 *
 * @param l: The line where number is presented
 * @param c: The column of the leftmost digit of number
 * @param min: The minimum value of number
 * @param max: The maximum value of number
 * @param initVal: The initial value to present
 * @param maxDigits: The maximum number of digits of the number
 */
int UI_Number(int l, int c, int min, int max, int initVal, int maxDigits);

/**
 * @brief Displays the date given by the RTC in the format yyyy/mm/dd hh:mm.
 * @returns Nothing
 *
 * @param l: The line where the date is presented
 * @param c: The column of the leftmost digit of date
 */
void UI_DisplayTime(int l, int c);

/**
 * @brief Allows the user to change the date stored in the RTC
 * @returns Nothing
 *
 * @param l: The line where the date is presented
 * @param c: The column of the leftmost digit of date
 */
void UI_SetTime(int l, int c);


/**
 * @}
 */

/**
 * @}
 */

#endif /* UI_H_ */
