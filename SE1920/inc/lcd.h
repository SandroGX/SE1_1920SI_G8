/**
* @file		lcd.h
* @brief	Contains the LCD API.
* @version	1.0
* @date		31 Out 2019
* @author	SE1_1920_i_G8
*/

#ifndef LCD_H_
#define LCD_H_

#include <stdbool.h>

/** @defgroup LCD LCD
 * This package provides the ability to write to the LCD
 * @{
 */

/** @defgroup LCD_Public_Functions LCD Public Functions
 * @{
 */

/**
 * @brief Sends 4 data bits and the rs bit to LCD
 * @returns Nothing
 * @param rs: 	if we are writing a command should be false(0),
 * 			 	if we are writing data should be true(1)
 * @param data4: the 4 bits corresponding to part of the command or character we are sending to the LCD
 */
void LCDWrite5bits(bool rs, int data4);
/**
 * @brief Sends 8 data bits and the rs bit to LCD
 * @returns Nothing
 * @param rs: 	if we are writing a command should be false(0),
 * 			 	if we are writing data should be true(1)
 * @param data8: 	the 8 bits corresponding to the full command or character we are sending to the LCD
 */
void LCDWrite9bits(bool rs, int data8);

/**
 * @brief Sends command to LCD
 * @returns Nothing
 *
 * @param cmd8: the 8 bits corresponding to the command we are sending to the LCD
 */
void LCDWriteCMD(int cmd8);

/**
 * @brief Writes character to LCD on the current position of the cursor
 * @returns Nothing
 *
 * @param data8: the 8 bits corresponding to the character we are sending to the LCD
 */
void LCDWriteData(int data8);

/**
 * @brief Writes character to LCD on the current position of the cursor
 * @returns Nothing
 *
 * @param ch: Character we are sending to the LCD
 */
void LCDText_WriteChar(char ch);
/**
 * @brief Writes string to LCD on the current position of the cursor
 * @returns Nothing
 *
 * @param str: String we are sending to the LCD
 */
void LCDText_WriteString(char *str);
/**
 * @brief Positions cursor in a certain position
 * @returns Nothing
 *
 * @param row: The row we are where the cursor is positioned
 * @param column: The column we are where the cursor is positioned
 */
void LCDText_Locate(int row, int column);

/**
 * @brief Clear all characters written to LCD
 * @returns Nothing
 */
void LCDText_Clear(void);

/**
 * @brief Controls the number of display lines and character font
 * @returns Nothing
 *
 * @param N: if true display 2 lines else display 1
 * @param F: Controls the type of font
 * @note font can only be controlled if N is false (1 display line)
 */
void LCD_FuntionSet(bool N, bool F);

/**
 * @brief Controls if LCD display is on, if the cursor is shown and if it is blinking
 * @returns Nothing
 *
 * @param D: if true display on else off
 * @param C: if true the cursor is shown else it isn't
 * @param B: if true the cursor is blinking else it isn't
 */
void LCD_Control(bool D, bool C, bool B);

/**
 * @brief Control how the display behaves when characters are written to int
 * @returns Nothing
 *
 * @param ID: if true when a character is written cursor goes to the right else goes left
 * @param S: if true the entire display shifts right(ID = 1) or left(ID=0) when a character is written
 */
void LCD_EntryModeSet(bool ID, bool S);

/**
 * @brief Writes to the current position of cursor with the same syntax as a printf
 * @returns Nothing
 *
 * @param fmt: the format string as used by printf
 * @param ...: the rest of the arguments that would be passed to printf go here
 */
void LCDText_Printf(char *fmt, ...);

/**
 * @brief Initializes the LCD system with 2 display lines, 16 columns and communication with 4 bits
 * @returns Nothing
 * @note This function must be called prior to any other LCD functions.
 */
void LCDText_Init(void);

/**
 * @}
 */

/**
 * @}
 */


#endif /* LCD_H_ */
