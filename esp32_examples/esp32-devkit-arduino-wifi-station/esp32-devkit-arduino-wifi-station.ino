// Author: Erwin Ouyang, aiotedge.tech
// Date  : 29 Feb 2020

#include <WiFi.h>

const char ssid[] = "Huawei-E5573";
const char pass[] = "huaweie5573";

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

  // *** Print WiFi station configuration ***
  Serial.printf("SSID: %s\n", WiFi.SSID().c_str());
  Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("Subnet mask: %s\n", WiFi.subnetMask().toString().c_str());
  Serial.printf("Gateway: %s\n", WiFi.gatewayIP().toString().c_str());
  Serial.printf("MAC address: %s\n", WiFi.macAddress().c_str()); 
}

void loop()
{
}

