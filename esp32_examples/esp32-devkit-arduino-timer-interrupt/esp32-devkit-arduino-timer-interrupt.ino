// Author: Erwin Ouyang, aiotedge.tech
// Date  : 8 Mar 2020

#include <Ticker.h>

Ticker ticker;

void led_isr()
{
  // Toggle LED
  digitalWrite(2, !digitalRead(2));
}

void setup()
{
  // Set GPIO pin as output for on-board LED
  pinMode(2, OUTPUT);
  // Set ticker to generate interrupt every 1 second
  ticker.attach(1, led_isr);
}

void loop()
{
}

