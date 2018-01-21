#include "timer.h"
#include  "gpio.h"

uint16_t TimerPeriod = 0;
uint16_t PrescalerValue = 0;
uint16_t Channel1Pulse = 0;
uint8_t lcdBrightness = 50;

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // Конфигурация таймера
TIM_OCInitTypeDef TIM_OCInitStructure; // Конфигурация выхода таймера
NVIC_InitTypeDef NVIC_InitStructure;

void TIM3_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	PrescalerValue = (uint16_t)(SystemCoreClock / 1000) - 1; //Делитель на 1000 Гц
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_Period = 500; // Прерывание (1000/TIM_Period) Гц
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //Enable the TIM3 gloabal Interrupt
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //разрешаем прерывание от таймера
	TIM_Cmd(TIM3, ENABLE); //TIM3 enable counter
}

void TIM2_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	PrescalerValue = (uint16_t)(SystemCoreClock / 1000) - 1; //Делитель на 1000 Гц
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_Period = 10; // Прерывание (1000/TIM_Period) Гц
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //Enable the TIM3 gloabal Interrupt
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //разрешаем прерывание от таймера
	TIM_Cmd(TIM2, ENABLE); //TIM3 enable counter
}

void Tim17_pwm_init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE); //Разрешаем тактирование таймера 17
	PrescalerValue = (uint16_t)(SystemCoreClock / 1000) - 1; //Делитель на 1000 Гц
	//	TimerPeriod = (SystemCoreClock / 17570) - 1; //Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz
	TimerPeriod = PrescalerValue * 2; //период переполнения таймера (количество циклов)
	Channel1Pulse = (uint16_t)(
			((uint32_t) lcdBrightness * (TimerPeriod - 1)) / 100); //Вычисление скважности ШИМ
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //PrescalerValue;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod; //1000; 			// Прерывание каждое переполнение (TIM_Period)
	TIM_TimeBaseInit(TIM17, &TIM_TimeBaseStructure);

	/*	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //Enable the TIM3 gloabal Interrupt
	 NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);

	 TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE); //разрешаем прерывание от таймера*/

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Конфигурируем таймер в режиме ШИМ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; //dead time тип
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
	TIM_OC1Init(TIM17, &TIM_OCInitStructure);

	TIM_Cmd(TIM17, ENABLE); //запускаем таймер
	TIM_CtrlPWMOutputs(TIM17, ENABLE); //TIM17 Main Output Enable
}

void setBrightness(uint8_t brightness) {
	uint16_t dutyCykle;
	dutyCykle = (uint16_t)(((uint32_t) brightness * (TimerPeriod - 1)) / 100); //Compute CCR1 value to generate a duty cycle
	TIM17->CCR1 = dutyCykle;
}

uint8_t getLcdBrightness() {
	return lcdBrightness;
}

void setLcdBrightness(uint8_t brightness) {
	lcdBrightness = brightness;
	setBrightness(brightness);
}
