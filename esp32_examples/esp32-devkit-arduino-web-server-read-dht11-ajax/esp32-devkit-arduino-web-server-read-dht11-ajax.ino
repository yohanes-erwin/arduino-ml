// Author: Erwin Ouyang, aiotedge.tech
// Date  : 7 Mar 2020

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

// Web page
const char webpage[] PROGMEM = R"=====(
<html>
  <head>
    <title>ESP32 Web Page</title>
  </head>
  <body>
    <p>Read DHT11 Sensor using AJAX</p>
    <p>Temperature: <strong><span id="temp_value">N/A</span>&deg;C</strong></p>
    <p>Humidity: <strong><span id="hum_value">N/A</span>%</strong></p>
    <script>
      setInterval(function() {
        getDHT11Value();
      }, 1000);
      function getDHT11Value() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            var response = JSON.parse(this.responseText);
            document.getElementById("temp_value").innerHTML = Math.round(response.temp);
            document.getElementById("hum_value").innerHTML = Math.round(response.hum);
          }
        };
        xhttp.open("POST", "dht11_ajax", true);
        xhttp.send();
      }
    </script>
  </body>
</html>
)=====";

void setup()
{
  // Setup serial communication
  Serial.begin(115200);
  // Initialize DHT sensor
  dht.begin();
  
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

  // Handler for DHT11 AJAX request
  server.on("/dht11_ajax", HTTP_POST, [](AsyncWebServerRequest *request)
  {
    // Read temperature and humidity
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    // Send JSON response
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    DynamicJsonBuffer jsonBuffer;
    JsonObject &dht11 = jsonBuffer.createObject();
    dht11["temp"] = String(temp);
    dht11["hum"] = String(hum);
    dht11.printTo(*response);
    request->send(response);
  });

  // Start server
  server.begin();
}

void loop()
{
}

