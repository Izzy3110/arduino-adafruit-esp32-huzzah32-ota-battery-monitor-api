#include <WiFi.h>
#include <ArduinoOTA.h>

#include "BatteryMonitor.h"
#include "HomeAssistant.h"
#include "LEDFunctions.h"
#include "OTASetup.h"
#include "WebServer.h"
#include "WiFiConnection.h"

unsigned long previousMillis = 0;
constexpr long interval = 10000;  // 10 seconds

unsigned long previousMillis_http = 0;
constexpr long interval_http = 5000;  // 10 seconds

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(LED_BUILTIN, OUTPUT);

  analogReadResolution(12);

  connectToWiFi();

  OTASetup();

  initWebServer();
}

void loop() {
  ArduinoOTA.handle();

  const float voltage = getBatteryVoltage();
  const int percent = getBatteryPercentage(voltage);

  const unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (WiFiClass::status() != WL_CONNECTED) {
      Serial.println("WiFi disconnected! Reconnecting...");

      WiFi.disconnect();
      connectToWiFi();

      flashLED(2);
    }
  }

  if (currentMillis - previousMillis_http >= interval_http) {
    previousMillis_http = currentMillis;

    sendBatteryToHA(voltage, percent);

    flashLED(1);
  }

  // HTTP-Server
  handleWebClient(voltage);

}
