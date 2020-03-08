// Author: Erwin Ouyang, aiotedge.tech
// Date  : 1 Mar 2020

#include <WiFi.h>

const char ssid[] = "Huawei-E5573";
const char pass[] = "huaweie5573";

// *** TCP server IP and port ***
const char ip[] = "192.168.8.101"; 
const uint16_t port = 23;

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
  // TCP client object declaration
  WiFiClient client;

  // *** Connect to a TCP server ***
  Serial.printf("Connecting to %s ...\n", ip);
  if (!client.connect(ip, port))
  {
    Serial.printf("Connection failed\n");
    Serial.println("Wait 5 sec ...");
    delay(5000);
    return;
  }
  Serial.printf("Connected\n");
    
  // Send a message to the TCP server
  client.printf("Message from TCP client\n");

  // *** Read an echo from the TCP server ***
  String response = client.readStringUntil('\n');
  Serial.print("Echoed message: ");
  Serial.println(response);

  // *** Close TCP connection ***
  Serial.printf("Closing connection\n");
  client.stop();
    
  Serial.println("Wait 5 sec ...");
  delay(5000);
}

