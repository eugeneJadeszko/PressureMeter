#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include "inttypes.h"
#include "gpio.h"

typedef enum {
	IS_PRESSED = 0,
	IS_NOT_PRESSED = !IS_PRESSED,
	PRESSED = 1,
	NOT_PRESSED = !PRESSED
} ButtonState;

typedef enum {
	MENU_OK = BUTTON_MENU_OK, PLUS = BUTTON_PLUS
} Buttons;

uint8_t button(Buttons button);
uint8_t buttonPlus();
uint8_t buttonOk();
void buttonUser();

#endif
