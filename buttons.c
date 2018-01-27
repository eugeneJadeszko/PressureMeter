#include "buttons.h"
#include "gpio.h"
#include "hd44780.h"
#include "display.h"
#include "utility.h"

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

uint8_t lastButtonPlusState;
uint8_t lastButtonUSERState;
uint8_t lastState;
uint8_t ledState;

/**
 * абстрактный метод обработки нажатия кнопки.
 */
uint8_t button(Buttons button) {
	uint8_t currentState;
	currentState = GPIO_ReadInputDataBit(GPIOB, button);
	if (currentState == IS_PRESSED) {
		delay_ms(500);
		return PRESSED;
	}
//	if ((currentState == IS_NOT_PRESSED) && (lastState == IS_PRESSED)) {
//		lastState = IS_NOT_PRESSED;
//		return NOT_PRESSED;
//	} else if ((currentState == IS_PRESSED) && (lastState == IS_NOT_PRESSED)) {
		lastState = IS_PRESSED;
//		GPIO_ResetBits(GPIOC, LED_BLUE_PC8);
//		return PRESSED;
//	}
	return NOT_PRESSED;
}

void buttonUser() {
	uint8_t buttonU;
	buttonU = GPIO_ReadInputDataBit(GPIOA, BUTTON_USER_PA0);
	if ((buttonU == 1) && (lastButtonUSERState == 0)) {
		if (ledState == 0) {
			ledState = 1;
			LcdLedOff();
			GPIO_ResetBits(GPIOC, LED_GREEN_PC9);
		} else {
			ledState = 0;
			LcdLedOn();
			GPIO_SetBits(GPIOC, LED_GREEN_PC9);
		}
		lastButtonUSERState = 1;
	} else if ((buttonU == 0) && (lastButtonUSERState == 1)) {
		lastButtonUSERState = 0;
	}
}
