// Author: Erwin Ouyang, aiotedge.tech
// Date  : 1 Mar 2020

#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

const char ssid[] = "Huawei-E5573";
const char pass[] = "huaweie5573";

// *** MQTT server's IP and port ***
const char mqtt_ip[] = "192.168.8.101"; 
const uint16_t mqtt_port = 1883;

// *** Create a WiFi Client and an MQTT client ***
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, mqtt_ip, mqtt_port);

// Setup an MQTT topic called '/test' for publishing
Adafruit_MQTT_Publish test = Adafruit_MQTT_Publish(&mqtt, "/test");

void setup()
{
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
}

void loop()
{
  // Connect to an MQTT server
  mqtt_connect();

  // *** Publish a message ***
  if (!test.publish("Hello, World!"))
  {
    Serial.println("MQTT publish failed");
  }
  else
  {
    Serial.println("MQTT publish succeed");
  }
  delay(1000);
}

void mqtt_connect()
{
  // Stop if already connected
  if (mqtt.connected())
  {
    return;
  }

  // *** Connect to MQTT broker ***
  Serial.println("Connecting to MQTT broker ... ");
  while (mqtt.connect() != 0) 
  {
    Serial.println("Retrying MQTT connection in 5 seconds ...");
    mqtt.disconnect();
    delay(5000);
  }
  Serial.println("MQTT Connected");
}

