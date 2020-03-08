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
    <meta http-equiv="refresh" content="3">
  </head>
  <body>
    <p>Read Button State</p>
    <p><strong>%STATE%</strong></p>
  </body>
</html>
)=====";

// Template processor for replacing placeholder with button state
String processor(const String& var)
{
  String button_state;
  
  if (var == "STATE")
  {
    // Read active-low button state
    if (digitalRead(BUTTON))
    {
      button_state = "OFF";
    }
    else
    {
      button_state = "ON";
    }
    return button_state;
  }
  
  return String();
}

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
    request->send_P(200, "text/html", webpage, processor);
  });

  // Start server
  server.begin();
}

void loop()
{
}

