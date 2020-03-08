// Author: Erwin Ouyang, aiotedge.tech
// Date  : 1 Mar 2020

#include <WiFi.h>

// On-board LED's GPIO pin
#define LED_ON_BOARD 2

const char ssid[] = "Huawei-E5573";
const char pass[] = "huaweie5573";

// TCP server port 
const uint16_t port = 23;

// TCP server object declaration
WiFiServer server(port);

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

  // *** Start TCP server ***
  server.begin();
  Serial.printf("TCP server started at port %d\n", port);
}

void loop()
{
  // Get TCP client
  WiFiClient client = server.available();

  // If a client connected
  if (client)
  {
    Serial.printf("Client connected\n");
    while (client.connected())
    {
      if (client.available())
      {
        // Read command from receive buffer
        String cmd = client.readStringUntil('\n');

        // *** Process the command ***
        if (cmd == "LED+ON")        // Turn on LED
        {
          digitalWrite(LED_ON_BOARD, HIGH);
        }
        else if (cmd == "LED+OFF")  // Turn off LED
        {
          digitalWrite(LED_ON_BOARD, LOW);
        }
        else if (cmd == "LED")      // Query the LED value
        {
          if (digitalRead(LED_ON_BOARD))
          {
            client.println("LED is on");
          }
          else
          {
            client.println("LED is off");
          }
        }
        else
        {
          Serial.println("Unknown command");
        }
      }
    }
    Serial.printf("Client disconnected\n");
  }
}

