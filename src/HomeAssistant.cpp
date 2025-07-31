//
// Created by sasch on 29.07.2025.
//

#include "HomeAssistant.h"

#include <HTTPClient.h>
#include <WString.h>

#include "secrets.h"

auto ha_server = HA_SERVER;
auto ha_token = HA_TOKEN;

int validCodes[] = {200, 201};

String createSensorPayload(const String& state, const String& unit, const String& name) {
    String payload = "{";
    payload += R"("state": ")" + state + "\",";
    payload += "\"attributes\": {";
    payload += R"("unit_of_measurement": ")" + unit + "\",";
    payload += R"("friendly_name": ")" + name + "\"";
    payload += "}}";
    return payload;
}


bool isHttpOk(int code, const int* validCodes, const size_t len) {
  for (size_t i = 0; i < len; ++i) {
    if (code == validCodes[i]) return true;
  }
  return false;
}

void sendPercentageToHA(const int percent) {
  HTTPClient http;

  String url_percentage = String(ha_server) + "/api/states/sensor.esp32_battery";

  String payload_percentage = createSensorPayload(String(percent), "%", "ESP32 Battery Level");

  http.begin(url_percentage);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(ha_token));

  int httpResponseCode_percentage = http.POST(payload_percentage);

  if (httpResponseCode_percentage > 0) {
    bool http_ok = isHttpOk(httpResponseCode_percentage, validCodes, sizeof(validCodes)/sizeof(validCodes[0]));

    String response = http.getString();

    Serial.print("http-ok (percentage): ");
    Serial.println(http_ok);
    Serial.println(response);
  } else {
    Serial.printf("Error sending data to HA: %s\n", http.errorToString(httpResponseCode_percentage).c_str());
  }
  http.end();
}

void sendVoltageToHA(const float voltage) {
  HTTPClient http;

  String url_voltage = String(ha_server) + "/api/states/sensor.esp32_battery_voltage";

  String payload_voltage = createSensorPayload(String(voltage), "V", "ESP32 Battery Voltage");

  http.begin(url_voltage);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(ha_token));

  int httpResponseCode_voltage = http.POST(payload_voltage);

  if (httpResponseCode_voltage > 0) {
    bool http_ok = isHttpOk(httpResponseCode_voltage, validCodes, sizeof(validCodes)/sizeof(validCodes[0]));

    String response_voltage = http.getString();

    Serial.print("http-ok (voltage): ");
    Serial.println(http_ok);
  } else {
    Serial.printf("Error sending data to HA: %s\n", http.errorToString(httpResponseCode_voltage).c_str());
  }
  http.end();
}

void sendBatteryToHA(const float voltage, const int percent) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected, cannot send data to HA");
    return;
  }

  sendPercentageToHA(percent);
  sendVoltageToHA(voltage);
}