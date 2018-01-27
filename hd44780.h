#ifndef _HD44780_H_
#define _HD44780_H_

#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

#define SYSCLK	48

// control gpio
#define LCD_CONT_PORT		GPIOA
#define RCC_LCD_CONT_PORT	RCC_AHBPeriph_GPIOA
#define RS    				GPIO_Pin_8 // Вывод команда/данные
#define EN   				GPIO_Pin_11 // Вывод синхронизации
// data gpio
#define LCD_DAT_PORT		GPIOA
#define RCC_LCD_DAT_PORT	RCC_AHBPeriph_GPIOA // RCC_AHBPeriph_GPIOB, RCC_AHBPeriph_GPIOC...
#define DB4    				GPIO_Pin_12
#define DB5   				GPIO_Pin_13
#define DB6    				GPIO_Pin_14
#define DB7   				GPIO_Pin_15

typedef enum {
	CURSOR_DISABLE = 0, CURSOR_ENABLE = !CURSOR_DISABLE
} cursor_state;

typedef enum {
	NO_BLINK = 0, BLINK = !NO_BLINK
} cursor_mode;

void LcdCursorMode(cursor_state curState, cursor_mode curMode);

void LcdInit(void);

void LcdLedOn(void);

void LcdLedOff(void);

void LcdSendCommand(uint8_t data);

void LcdSendData(uint8_t data);

void LcdSendByte(uint8_t data);

uint8_t LcdDrawString(char* text);

//---Установка позиции курсора---//
void LcdGoToPos(char Row, char Col);

//---Очистка дисплея---//
void LcdClear(void);

//---Очистка дисплея---//
uint8_t LcdConvertIntDisplay(int32_t u);

//---Очистка дисплея---//
void LcdFillSpace(uint8_t num);

//---Очистка дисплея---//
uint8_t LcdGetCurPos();

uint8_t itoa(int n, uint8_t* s);

#endif
