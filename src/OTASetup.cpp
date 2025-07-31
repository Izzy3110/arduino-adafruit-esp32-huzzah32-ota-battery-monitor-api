//
// Created by sasch on 01.08.2025.
//

#include "OTASetup.h"

#include <ArduinoOTA.h>

#include "config.h"


void OTASetup() {

    ArduinoOTA.setHostname(OTA_HOSTNAME);  // Optional: custom hostname
    ArduinoOTA.setPassword(OTA_PASSWORD);

    ArduinoOTA.onStart([]() {
      Serial.println("Start updating...");
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\nUpdate finished.");
    });
    ArduinoOTA.onProgress([](const unsigned int progress, const unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress * 100) / total);
    });
    ArduinoOTA.onError([](const ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

    ArduinoOTA.begin();
    Serial.println("OTA Ready");

}
