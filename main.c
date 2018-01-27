#include "gpio.h"
#include "Timer.h"
#include "hd44780.h"
#include "display.h"
#include "buttons.h"
#include "adc.h"
#include "status.h"
#include "calc.h"

int main(void) {
	GPIOInit();
	initPWMtimer17();
	initTimer2();
	DisplayInit();
	adcInit();
//	calcInit();
	initTimer3();

	while (1) {
		Display();
	}
}

void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		updateValues();
		buttonUser();
	}
}

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		updateStatuses();
	}
}
