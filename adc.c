#include "adc.h"
#include "gpio.h"

void adcInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = ADC_PA1 | ADC_PA2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ADC1 Periph clock enable

	ADC_InitTypeDef ADC_InitStructure;

	ADC_StructInit(&ADC_InitStructure); //Initialize ADC structure

	// Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC1->CFGR1 |= ADC_CFGR1_DISCEN; //!!! Software trigger Enable

	ADC_ChannelConfig(ADC1, ADC_Channel_1 | ADC_Channel_2, ADC_SampleTime_239_5Cycles);

	ADC_GetCalibrationFactor(ADC1); //ADC Calibration

	ADC_Cmd(ADC1, ENABLE); //Enable ADC1

	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN))
		; //Wait the ADCEN flag
}

uint16_t getAdcValue() {
	ADC_StartOfConversion(ADC1);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		;
	return ADC_GetConversionValue(ADC1);
}
