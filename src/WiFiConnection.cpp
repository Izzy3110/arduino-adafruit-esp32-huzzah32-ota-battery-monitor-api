//
// Created by sasch on 29.07.2025.
//

#include "WiFiConnection.h"

#include <IPAddress.h>
#include <WiFi.h>

#include "LEDFunctions.h"
#include "secrets.h"

auto ssid = WIFI_SSID;
auto password = WIFI_PASSWORD;

IPAddress local_IP(192, 168, 137, 130);
IPAddress gateway(192, 168, 137, 253);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(1, 1, 1, 1);

void connectToWiFi() {
    Serial.println("Setting static IP...");
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("⚠️  Failed to configure static IP");
    }
    flashLED(3);  // <-- Flash LED here
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20) {
        delay(500);
        Serial.print(".");
        retries++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✅ Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        flashLED(10);  // <-- Flash LED here
    } else {
        Serial.println("\n❌ Failed to connect.");
    }
}
