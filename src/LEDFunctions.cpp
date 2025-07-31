//
// Created by sasch on 29.07.2025.
//

#include "Arduino.h"
#include "LEDFunctions.h"

void flashLED(const int times, const int delayMs) {
    for (int i = 0; i < times; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(delayMs);
        digitalWrite(LED_BUILTIN, LOW);
        delay(delayMs);
    }
}
