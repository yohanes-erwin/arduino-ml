// Author: Erwin Ouyang, aiotedge.tech
// Date  : 29 Feb 2020

#include <WiFi.h>

const char ssid[] = "ESP32-AP";
const char pass[] = "esp32accesspoint";

IPAddress ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

int currentNumOfStation;

void setup()
{
  // Setup serial communication
  Serial.begin(115200);

  // *** Create a WiFi access point ***
  Serial.print("Setting AP ... ");
  Serial.println(WiFi.softAP(ssid, pass) ? "Ready" : "Failed!");
  Serial.print("Setting AP configuration ... ");
  Serial.println(WiFi.softAPConfig(ip, gateway, subnet) ? "Ready" : "Failed!");

  // *** Print WiFi AP configuration ***
  Serial.printf("IP address: %s\n", WiFi.softAPIP().toString().c_str());
  Serial.printf("MAC address: %s\n", WiFi.softAPmacAddress().c_str());
}

void loop()
{
  // *** Print number of stations that are connected to AP ***
  if (WiFi.softAPgetStationNum() != currentNumOfStation)
  {
    currentNumOfStation = WiFi.softAPgetStationNum();
    Serial.printf("Stations connected to AP: %d\n", currentNumOfStation); 
  }
}

