// Author: Erwin Ouyang, aiotedge.tech
// Date  : 29 Feb 2020

// On-board LED's GPIO pin
#define LED_ON_BOARD 2

// PWM parameters
const int channel = 0;
const int freq = 1000;
const int res = 10;

void setup()
{
  // Set GPIO pin as output for on-board LED
  pinMode(LED_ON_BOARD, OUTPUT);
  // Configure PWM
  ledcSetup(channel, freq, res);
  // Attach the PWM channel to the LED
  ledcAttachPin(LED_ON_BOARD, channel);
}

void loop()
{
  // *** Increase brightness ***
  for (int i = 0; i <= 1023; i += 20)
  {
    ledcWrite(channel, i);
    delay(25);
  }
  // *** Decrease brightness ***
  for (int i = 1023; i >= 0; i -= 20)
  {
    ledcWrite(channel, i);
    delay(25);
  }
}

