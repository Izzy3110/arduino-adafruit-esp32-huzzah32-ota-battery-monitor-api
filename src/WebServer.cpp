//
// Created by sasch on 29.07.2025.
//

#include "WebServer.h"

#include "BatteryMonitor.h"
#include "config.h"

WiFiServer server(HTTP_PORT);  // Define the server instance here

void initWebServer() {
  server.begin();
  Serial.println("HTTP server started");
}

void handleWebClient(const float voltage) {
  WiFiClient client = server.available();
  if (!client) return;

  const String req = client.readStringUntil('\r');
  client.readStringUntil('\n'); // Skip newline

  if (req.indexOf("GET /api/battery") >= 0) {
    const int percent = getBatteryPercentage(voltage);
    sendBatteryJSON(client, voltage);
  } else {
    sendHTML(client);
  }

  client.stop();
}

void sendBatteryJSON(WiFiClient& client, const float voltage) {
    const int percent = getBatteryPercentage(voltage);

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("Access-Control-Allow-Origin: *");
    client.println();

    client.print("{\"battery_voltage\": ");
    client.print(voltage, 2);
    client.print(", \"battery_percent\": ");
    client.print(percent);
    client.println("}");
}

void sendHTML(WiFiClient& client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();

    client.println(R"rawliteral(
<!DOCTYPE html><html><head>
<meta charset='UTF-8'>
<title>ESP32 Battery Monitor</title>
<style>
  body {
    font-family: Arial;
    text-align: center;
    background-color: #121212;
    color: #00FF90;
  }
  h1 {
    margin-top: 40px;
    font-size: 2em;
  }
  .voltage {
    font-size: 2em;
    margin: 10px 0;
  }
  .progress-container {
    width: 80%;
    background: #333;
    margin: auto;
    border-radius: 10px;
    overflow: hidden;
  }
  .progress-bar {
    height: 30px;
    width: 0%;
    text-align: center;
    line-height: 30px;
    color: #000;
    transition: width 0.3s, background-color 0.3s;
  }
</style>
<script>
function fetchVoltage() {
  fetch('/api/battery')
    .then(res => res.json())
    .then(data => {
      const voltage = data.battery_voltage.toFixed(2);
      const percent = data.battery_percent;
      const bar = document.getElementById('percent');

      document.getElementById('voltage').textContent = voltage + ' V';
      bar.textContent = percent + '%';
      bar.style.width = percent + '%';

      // Change color based on percentage
      if (percent >= 60) {
        bar.style.backgroundColor = '#00FF90';  // Green
      } else if (percent >= 30) {
        bar.style.backgroundColor = '#FFFF00';  // Yellow
        bar.style.color = '#000000';            // Black text
      } else {
        bar.style.backgroundColor = '#FF4040';  // Red
        bar.style.color = '#FFFFFF';            // White text
      }
    });
}
setInterval(fetchVoltage, 5000);
window.onload = fetchVoltage;
</script>
</head><body>
<h1>🔋 Battery Monitor</h1>
<div class='voltage'>Voltage: <span id='voltage'>...</span></div>
<div class='progress-container'>
  <div class='progress-bar' id='percent'>...</div>
</div>
</body></html>
)rawliteral");
}                  // variable for reading the pin status