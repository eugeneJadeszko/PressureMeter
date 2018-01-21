#ifndef _TIMER_H_
#define _TIMER_H_

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_misc.h"

void TIM3_Init(void);
void TIM2_Init(void);
void Tim17_pwm_init(void);
void setBrightness(uint8_t brightness);
uint8_t getLcdBrightness();
void setLcdBrightness(uint8_t brightness);

#endif
