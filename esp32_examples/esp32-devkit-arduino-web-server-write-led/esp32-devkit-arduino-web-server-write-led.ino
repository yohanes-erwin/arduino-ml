// Author: Erwin Ouyang, aiotedge.tech
// Date  : 7 Mar 2020

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// On-board LED's GPIO pin
#define LED_ON_BOARD 2

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
    <p>Write LED State</p>
    <a href="/on"><button>ON</button></a>
    <a href="/off"><button>OFF</button></a>
  </body>
</html>
)=====";

void setup()
{
  // Set GPIO pin as output for on-board LED
  pinMode(LED_ON_BOARD, OUTPUT);
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

  // Handler for turning on the LED
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED_ON_BOARD, HIGH);
    request->redirect("/");
  });
  
  // Handler for turning of the LED
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED_ON_BOARD, LOW);
    request->redirect("/");
  });

  // Start server
  server.begin();
}

void loop()
{
}

