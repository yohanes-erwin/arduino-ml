// Author: Erwin Ouyang, aiotedge.tech
// Date  : 22 Feb 2020

void setup()
{
  // Set GPIO pin as output for on-board LED
  pinMode(2, OUTPUT);
}

void loop()
{
  // Turn on LED
  digitalWrite(2, HIGH);
  delay(500);
  // Turn off LED
  digitalWrite(2, LOW);
  delay(500);
}
