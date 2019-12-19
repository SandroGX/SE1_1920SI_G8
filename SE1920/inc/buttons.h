/**
* @file		buttons.h
* @brief	Contains the BUTTON API.
* @version	1.0
* @date		31 Out 2019
* @author	SE1_1920_i_G8
*/

#ifndef BUTTONS_H_
#define BUTTONS_H_

/** @defgroup Buttons Buttons
 * This package provides the ability to read the state of each of the 3 buttons
 * @{
 */

/** @defgroup Buttons_Macros Buttons Macros
 * @{
 */

/**
 * @defgroup Buttons_Macros_PINMODEs Buttons Macros PINMODEs
 * @brief	Macros to configure the mode of a pin
 * @{
 */
#define PINMODECFG_PULLUP 0
#define PINMODECFG_REPEATER 1
#define PINMODECFG_NOTHING 2
#define PINMODECFG_PULLDOWN 3
/**
 * @}
 */

/**
 * @defgroup Buttons_Macros_ButtonPINs Buttons Macros Button PINs
 * @brief	Macros that represent the number of the pin to which the button is connected
 * @{
 */
#define UPBUTTON_PIN 2
#define DOWNBUTTON_PIN 3
#define ENTERBUTTON_PIN 21
/**
 * @}
 */
/**
 * @defgroup Buttons_Macros_ButtonPINConfigMask Buttons Macros Button PIN Configuration Masks
 * @brief	Macros of the mask for the configuration register for each button
 * @note mod 16 because they may be in different registers
 * @{
 */
#define UPBUTTON_PINCFG (UPBUTTON_PIN%16)*2
#define DOWNBUTTON_PINCFG (DOWNBUTTON_PIN%16)*2
#define ENTERBUTTON_PINCFG (ENTERBUTTON_PIN%16)*2
/**
 * @}
 */
/**
 * @defgroup Buttons_Macros_ButtonPINMask Buttons Macros Button PIN Masks
 * @brief	Macros of the mask for the GPIO for each button
 * @{
 */
#define UPBUTTON 1<<UPBUTTON_PIN
#define DOWNBUTTON 1<<DOWNBUTTON_PIN
#define ENTERBUTTON 1<<ENTERBUTTON_PIN
/**
 * @}
 * @}
 */

/** @defgroup Button_Public_Functions Button Public Functions
 * @{
 */

/**
 * @brief	Initializes the system to access the buttons
 * @return Nothing
 * @note Must be called prior to any Button functions
 */
void BUTTON_Init(void);

/**
 * @brief	Gets the bitmap of the pressed buttons,
 * 			if pressed the bit of the button will be 1,
 * 			otherwise 0
 * @returns bitmap of the pressed buttons
 * @note non-blocking function
 */
int BUTTON_Hit(void);

/**
 * @brief	Gets the bitmap of the pressed buttons,
 * 			and only returns if one of them is pressed
 * @returns bitmap of the pressed buttons
 * @note blocking function
 */
int BUTTON_Read(void);

/**
 * @brief	Not implemented
 * @returns Not implemented
 * @note Not implemented
 */
int BUTTON_GetButtonsEvents(void);

/**
 * @}
 */

/**
 * @}
 */

void BUTTON_WaitNoneHit(void);

#endif /* BUTTONS_H_ */
