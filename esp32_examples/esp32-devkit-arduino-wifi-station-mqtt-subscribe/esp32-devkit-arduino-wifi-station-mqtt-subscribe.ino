// Author: Erwin Ouyang, aiotedge.tech
// Date  : 1 Mar 2020

#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// On-board LED's GPIO pin
#define LED_ON_BOARD 2

const char ssid[] = "Huawei-E5573";
const char pass[] = "huaweie5573";

// *** MQTT server's IP and port ***
const char mqtt_ip[] = "192.168.8.101"; 
const uint16_t mqtt_port = 1883;

// *** Create a WiFi Client and an MQTT client ***
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, mqtt_ip, mqtt_port);

// Setup an MQTT topic called '/onoff' for subscribing to changes to the button
Adafruit_MQTT_Subscribe topic_onoff = Adafruit_MQTT_Subscribe(&mqtt, "/onoff");
// Setup an MQTT topic called '/uint' for subscribing to uint value
Adafruit_MQTT_Subscribe topic_uint = Adafruit_MQTT_Subscribe(&mqtt, "/uint");
// Setup an MQTT topic called '/double' for subscribing to double value
Adafruit_MQTT_Subscribe topic_double = Adafruit_MQTT_Subscribe(&mqtt, "/double");

// MQTT subscribe callback function
void onoff_callback(char *cmd, uint16_t len)
{
  // *** Process the command ***
  if (String(cmd).equals("LED+ON"))        // Turn on LED
  {
    digitalWrite(LED_ON_BOARD, HIGH);
  }
  else if (String(cmd).equals("LED+OFF"))  // Turn off LED
  {
    digitalWrite(LED_ON_BOARD, LOW);
  }
}

void uint_callback(uint32_t value)
{
  Serial.println(value);
}

void double_callback(double value)
{
  Serial.println(value);
}

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

  // *** Setup MQTT subscription ***
  topic_onoff.setCallback(onoff_callback);
  topic_uint.setCallback(uint_callback);
  topic_double.setCallback(double_callback);
  mqtt.subscribe(&topic_onoff);
  mqtt.subscribe(&topic_uint);
  mqtt.subscribe(&topic_double);
}

void loop()
{
  // Connect to an MQTT server
  mqtt_connect();

  // This is our 'wait for incoming subscription packets and callback em' busy subloop
  // Try to spend your time here:
  mqtt.processPackets(10000);

  // Ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  if (!mqtt.ping())
  {
    mqtt.disconnect();
  }
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

