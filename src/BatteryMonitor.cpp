//
// Created by sasch on 29.07.2025.
//
#include <Arduino.h>
#include "BatteryMonitor.h"
#include "config.h"


int getBatteryPercentage(const float voltage) {
    int percent = (voltage - 3.0) / (4.2 - 3.0) * 100;
    percent = constrain(percent, 0, 100);  // Ensure it's between 0–100
    return percent;
}

float getBatteryVoltage() {
    const int raw = analogRead(BATTERY_PIN);
    const float voltage = (raw / 4095.0) * 3.3;
    return voltage * 2;
}