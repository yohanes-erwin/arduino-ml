// Author: Erwin Ouyang, aiotedge.tech
// Date  : 7 Mar 2020

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Button's GPIO pin
#define BUTTON 12

const char ssid[] = "Huawei-E5573";
const char pass[] = "huaweie5573";

// TCP server port for HTTP
const uint16_t port = 80;

// Create AsyncWebServer object
AsyncWebServer server(port);

// Web page
const char webpage[] PROGMEM = R"=====(
<html>
  <head>
    <title>ESP32 Web Page</title>
  </head>
  <body>
    <p>Read Button State using AJAX</p>
    <p><strong><span id="button_state">N/A</span></strong></p>
    <script>
      setInterval(function() {
        getButtonState();
      }, 1000);
      function getButtonState() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("button_state").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "button_ajax", true);
        xhttp.send();
      }
    </script>
  </body>
</html>
)=====";

void setup()
{
  // Set GPIO pin as input for button
  pinMode(BUTTON, INPUT_PULLUP);
  // Setup serial communication
  Serial.begin(115200);

  // *** Connect to a WiFi access point ***
  Serial.printf("Connecting to %s ...\n", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi connect failed! Rebooting ...\n");
    delay(1000);
    ESP.restart();
  }
  Serial.printf("Connected\n");
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());

  // Handler for root request
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/html", webpage);
  });

  // Handler for button AJAX request
  server.on("/button_ajax", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if (digitalRead(BUTTON))
    {
      request->send(200, "text/plain", "OFF");
    }
    else
    {
      request->send(200, "text/plain", "ON");
    }
  });

  // Start server
  server.begin();
}

void loop()
{
}

