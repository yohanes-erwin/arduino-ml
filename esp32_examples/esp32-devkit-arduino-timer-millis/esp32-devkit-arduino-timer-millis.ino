// Author: Erwin Ouyang, aiotedge.tech
// Date  : 8 Mar 2020

void setup()
{
  // Initialize serial port
  Serial.begin(115200);
}

void loop()
{
  // Get milliseconds value
  unsigned long ms = millis();
  // Print milliseconds value to serial monitor
  Serial.println(ms);
  delay(1000);
}

