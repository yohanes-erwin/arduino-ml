// Author: Erwin Ouyang, aiotedge.tech
// Date  : 7 Mar 2020

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// On-board LED's GPIO pin
#define LED_ON_BOARD 2

// PWM parameters
const int channel = 0;
const int freq = 1000;
const int res = 10;

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
    <p>Write LED Value</p>
    <form action="/led_pwm" method="POST">
      <input type="range" name="pwm_value" min="0" max="1023" value="0"><br>
      <input type="submit">
    </form>
  </body>
</html>
)=====";

void setup()
{
  // Set GPIO pin as output for on-board LED
  pinMode(LED_ON_BOARD, OUTPUT);
  // Configure PWM
  ledcSetup(channel, freq, res);
  // Attach the PWM channel to the LED
  ledcAttachPin(LED_ON_BOARD, channel);
  
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

  // Handler for button request
  server.on("/led_pwm", HTTP_POST, [](AsyncWebServerRequest *request)
  {
    // Get HTTP POST parameter
    AsyncWebParameter *p = request->getParam(0);
    if (p->isPost())
    {
      // Print HTTP POST parameter to the serial monitor
      Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
    }
    // Write PWM value to the LED
    ledcWrite(channel, p->value().toInt());
    
    request->redirect("/");
  });

  // Start server
  server.begin();
}

void loop()
{
}

