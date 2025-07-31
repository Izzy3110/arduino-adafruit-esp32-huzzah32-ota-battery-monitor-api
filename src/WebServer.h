//
// Created by sasch on 29.07.2025.
//

#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <WiFiClient.h>
#include <WiFiServer.h>

void sendBatteryJSON(WiFiClient& client, float voltage);
void sendHTML(WiFiClient& client);

// Declare the server instance as extern
extern WiFiServer server;
// Declare a function to initialize the server
void initWebServer();
void handleWebClient(float voltage);

#endif //WEBSERVER_H
