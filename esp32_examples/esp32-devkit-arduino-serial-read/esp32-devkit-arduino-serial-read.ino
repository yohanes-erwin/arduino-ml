// Author: Erwin Ouyang, aiotedge.tech
// Date  : 8 Mar 2020

void setup()
{
  // Initialize serial port
  Serial.begin(115200);
}

void loop()
{
  // If there is data in receive buffer
  if (Serial.available() > 0)
  {
    // Read string from receive buffer
    String input = Serial.readString();
    // Print to serial monitor
    Serial.print(input);
  }
}

