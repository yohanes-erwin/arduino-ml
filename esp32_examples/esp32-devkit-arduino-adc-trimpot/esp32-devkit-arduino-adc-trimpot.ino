// Author: Erwin Ouyang, aiotedge.tech
// Date  : 8 Mar 2020

void setup()
{
  // Initialize serial port
  Serial.begin(115200);
}

void loop()
{
  // Read trimpot value using ADC
  int trimpot = analogRead(27);
  // Print the value to the serial monitor
  Serial.println(trimpot);
  delay(1000);
}

