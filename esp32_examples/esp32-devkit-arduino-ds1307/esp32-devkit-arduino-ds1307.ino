// Author: Erwin Ouyang, aiotedge.tech
// Date  : 8 Mar 2020

#include <Wire.h>
#include <RtcDS1307.h>

// I2C pins
#define I2C_SDA 33
#define I2C_SCL 32

// RTC object declaration
RtcDS1307<TwoWire> rtc(Wire);

void setup()
{
  // Initialize serial port
  Serial.begin(115200);
  
  // Initialize I2C pins
  Wire.begin(I2C_SDA, I2C_SCL, 400000);
  
  // Initialize RTC
  rtc.Begin();  
  // *** Set RTC date and time to code compiled time ***
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  rtc.SetDateTime(compiled);
  rtc.SetIsRunning(true);
}

void loop()
{
  // Read RTC date and time
  RtcDateTime now = rtc.GetDateTime();
  // Print RTC date and time to serial monitor 
  Serial.printf("%04d/%02d/%02d %02d:%02d:%02d\n",
      now.Year(), now.Month(), now.Day(),
      now.Hour(), now.Minute(), now.Second());
  delay(1000);
}

