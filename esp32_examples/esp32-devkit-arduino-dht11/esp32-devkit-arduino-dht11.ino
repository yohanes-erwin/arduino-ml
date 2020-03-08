// Author: Erwin Ouyang, aiotedge.tech
// Date  : 23 Feb 2020

#include <DHT.h>

#define DHTPIN  22
#define DHTTYPE DHT11

// Setup DHT pin and type
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  // Initialize serial port
  Serial.begin(115200);
  // Initialize DHT sensor
  dht.begin();
}

void loop()
{ 
  // Read temperature
  float temp = dht.readTemperature();
  // Read humidity
  float hum = dht.readHumidity();
  
  // Print temperature 
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("°C ");
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println("%");

  // Maximum sampling rate of DHT11 is 1Hz
  // So, the minimum delay is one second 
  delay(1000);
}

