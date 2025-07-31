//
// Created by sasch on 29.07.2025.
//
#pragma once
#include <secrets.h>
#ifndef CONFIG_H
#define CONFIG_H

// #define LED_BUILTIN 2  // Usually GPIO 2 on HUZZAH32
#define BATTERY_PIN 35  // GPIO35 (A13)
#define HTTP_PORT 80
#define OTA_HOSTNAME "esp32-battery"
#define OTA_PASSWORD OTA_PASSWD
#define DEVICE_UUID        "b18f2e3f-8409-4648-8ef9-23f03430c3f8"
#endif //CONFIG_H
