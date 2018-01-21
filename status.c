#include "status.h"
#include "gpio.h"
#include "hd44780.h"
#include "calc.h"
#include "utility.h"

extern uint8_t charge;
uint8_t stat;

//void ShowBatteryStatus() {
//	uint8_t stdby, chargeStat;
//	stdby = GPIO_ReadInputDataBit(GPIOB, STDBY_PB10);
//	chargeStat = GPIO_ReadInputDataBit(GPIOB, CHARGE_PB11);
//	if ((chargeStat == 0) && (stdby == 1)) {
//		if (GPIO_ReadInputDataBit(GPIOA, LED_Fpanel_PA6) == 0) {
//			GPIO_SetBits(GPIOA, LED_Fpanel_PA6);
//		}
//		showStatus();
//		LcdGoToPos(0, 19);
//		LcdFillSpace(1);
//		LcdGoToPos(0, 19);
//		stat++;
//		if (stat > 6)
//			stat = 0;
//		LcdSendData(stat);
//	} else if ((chargeStat == 1) && (stdby == 0)) {
//		LcdGoToPos(0, 8);
//		LcdFillSpace(11);
//		LcdGoToPos(0, 15);
//		LcdDrawString("100%");
//		LcdSendData(3);
//		GPIOA->ODR ^= LED_Fpanel_PA6; //toggling
//	} else {
//		showStatus();
//		if (GPIO_ReadInputDataBit(GPIOA, LED_Fpanel_PA6) == 0) {
//			GPIO_SetBits(GPIOA, LED_Fpanel_PA6);
//		}
//	}
//}
//
//void showStatus() {
//	CalcUpdate();
//	LcdGoToPos(0, 8);
//	LcdFillSpace(12);
//	LcdGoToPos(0, 15);
//	LcdConvertIntDisplay(charge);
//	LcdSendData('%');
//	if (charge >= 95) {
//		LcdGoToPos(0, 19);
//		LcdSendData(6);
//	} else if ((charge < 95) && (charge >= 70)) {
//		LcdGoToPos(0, 19);
//		LcdSendData(5);
//	} else if ((charge < 70) && (charge >= 50)) {
//		LcdGoToPos(0, 19);
//		LcdSendData(4);
//	} else if ((charge < 50) && (charge >= 30)) {
//		LcdGoToPos(0, 19);
//		LcdSendData(3);
//	} else if ((charge < 30) && (charge >= 10)) {
//		LcdGoToPos(0, 19);
//		LcdSendData(2);
//	} else if ((charge < 10) && (charge >= 5)) {
//		LcdGoToPos(0, 19);
//		LcdSendData(1);
//	} else if (charge < 5) {
//		LcdGoToPos(0, 19);
//		LcdSendData(0);
//	}
//}
