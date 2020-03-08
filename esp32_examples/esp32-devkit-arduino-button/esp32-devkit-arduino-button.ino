// Author: Erwin Ouyang, aiotedge.tech
// Date  : 8 Mar 2020

void setup()
{
  // Set GPIO pin as output for on-board LED
  pinMode(2, OUTPUT);
  // Set GPIO pin as input with pull-up resistor for button
  pinMode(12, INPUT_PULLUP);
}

void loop()
{
  // *** Read button state *** 
  if (digitalRead(12) == LOW)
  {
    // If button is pressed, then turn on the LED 
    digitalWrite(2, HIGH);
  }
  else
  {
    // If button is not pressed, then turn off the LED
    digitalWrite(2, LOW);
  }
}

