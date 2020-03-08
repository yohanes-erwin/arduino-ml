// Author: Erwin Ouyang, aiotedge.tech
// Date  : 8 Mar 2020

#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define DHTPIN  22
#define DHTTYPE DHT11

// Setup DHT pin and type
DHT dht(DHTPIN, DHTTYPE);

const char ssid[] = "Huawei-E5573";
const char pass[] = "huaweie5573";

// TCP server port for HTTP
const uint16_t port = 80;

// Create AsyncWebServer object
AsyncWebServer server(port);

// Global variable for storing temperature value
int temp;

void setup()
{
  // Setup serial communication
  Serial.begin(115200);
  // Initialize DHT sensor
  dht.begin();
  
  // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }

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
    request->send(SPIFFS, "/index.html");
  });

  // Handler for DHT11 AJAX request
  server.on("/temperature", HTTP_POST, [](AsyncWebServerRequest *request)
  {
    // Send temperature
    request->send(200, "text/plain", readDHT11Temperature());
  });

  // Handler for Bootstrap libraries
  server.on("/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/bootstrap.min.css");
  });
  server.on("/jquery-3.3.1.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/jquery-3.3.1.min.js");
  });
  server.on("/popper.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/popper.min.js");
  });
  server.on("/bootstrap.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/bootstrap.min.js");
  });
  server.on("/raphael-2.1.4.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/raphael-2.1.4.min.js");
  });
  server.on("/justgage.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/justgage.js");
  });
    
  // Start server
  server.begin();
}

void loop()
{
}

String readDHT11Temperature()
{
  // Read temperature
  int t = (int)dht.readTemperature();
  // Update temperature value only if it is not NaN and between -15 and 35
  temp = (isnan(t)) ? temp : (((t >= -15) && (t <= 35)) ? t : temp);
  
  return String(temp);
}

