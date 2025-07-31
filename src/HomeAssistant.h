//
// Created by sasch on 29.07.2025.
//

#ifndef HOMEASSISTANT_H
#define HOMEASSISTANT_H
#include <WString.h>

String createSensorPayload(const String& state, const String& unit, const String& name);
bool isHttpOk(int code, const int* validCodes, size_t len);
void sendPercentageToHA(int percent);
void sendVoltageToHA(float voltage);
void sendBatteryToHA(float voltage, int percent);

#endif //HOMEASSISTANT_H
