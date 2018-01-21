#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

#define LED_GREEN_PC9 	GPIO_Pin_9
#define LED_BLUE_PC8 	GPIO_Pin_8
#define BUTTON_USER_PA0 GPIO_Pin_0
#define BUTTON_PLUS 	GPIO_Pin_6
#define BUTTON_MENU_OK  GPIO_Pin_7
#define LCD_LIGHT_PB9	GPIO_Pin_9

#define ADC_PA1				GPIO_Pin_1
#define CHARGE_PB11			GPIO_Pin_11
#define STDBY_PB10			GPIO_Pin_10

void GPIOInit(void);

#endif
