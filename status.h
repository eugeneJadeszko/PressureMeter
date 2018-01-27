#ifndef _STATUS_H_
#define _STATUS_H_

#include "inttypes.h"

void updateStatuses();
void ShowBatteryStatus();
void showChargeStatus();
void showPressureStatus();
void showDeviceStatus();

void setPressure(uint16_t pressureValue);
void setCharge(uint8_t chargeValue);
void setCurrentDeviceState(uint8_t state);

#endif
