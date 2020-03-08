// Author: Erwin Ouyang, aiotedge.tech
// Date  : 1 Mar 2020

#include <WiFi.h>

const char ssid[] = "Huawei-E5573";
const char pass[] = "huaweie5573";

const char host[] = "www.google.com";
const uint16_t port = 80;

String httpRequest =
  "GET / HTTP/1.1\r\n" \
  "Host: " + String(host) + "\r\n" \
  "Connection: close\r\n\r\n";

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
    Serial.printf("WiFi connect failed! Rebooting...\n");
    delay(1000);
    ESP.restart();
  }
  Serial.printf("Connected\n");
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
}

void loop()
{
  // TCP client object declaration
  WiFiClient client;

  // *** Connect to host server ***
  Serial.printf("Connecting to %s ...\n", host);
  if (!client.connect(host, port))
  {
    Serial.printf("Connection failed\n");
    Serial.println("Wait 5 sec ...");
    delay(5000);
    return;
  }
  Serial.printf("Connected\n");
    
  // Send HTTP request
  client.print(httpRequest);

  // *** Wait until server give response ***
  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 5000) 
    {
      Serial.printf("Client Timeout\n");
      client.stop();
      return;
    }
  }
  
  // *** Read HTTP response from server ***
  while(client.available())
  {
    String line = client.readStringUntil('\n');
    Serial.print(line);
  }
  
  // *** Close TCP connection ***
  Serial.printf("\nClosing connection\n");
  client.stop();
    
  Serial.println("Wait 5 sec ...");
  delay(5000);
}

