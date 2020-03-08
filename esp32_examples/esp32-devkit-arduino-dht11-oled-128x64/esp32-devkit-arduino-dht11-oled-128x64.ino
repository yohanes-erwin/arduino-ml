// Author: Erwin Ouyang, aiotedge.tech
// Date  : 8 Mar 2020

#include <Wire.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// DHT11 pins
#define DHTPIN  22
#define DHTTYPE DHT11

// I2C pins
#define I2C_SDA 33
#define I2C_SCL 32
// *** Check library setting ***
#if (SSD1306_LCDHEIGHT != 64)    // 128 x 64 pixel display
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
// OLED I2C address
#define OLED_ADDR 0x3C

// Setup DHT pin and type
DHT dht(DHTPIN, DHTTYPE);
// OLED object declaration
Adafruit_SSD1306 oled;

void setup()
{
  // Initialize DHT11
  dht.begin();
    
  // Initialize I2C pins
  Wire.begin(I2C_SDA, I2C_SCL, 400000);
  
  // *** Initialize and clear display ***
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  // Clear OLED buffer
  oled.clearDisplay();
}

void loop()
{
  // *** Read temperature and humidity ***
  float celcius = dht.readTemperature();
  float humidity = dht.readHumidity();

  // *** Display temperature and humidity on OLED ***
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(45, 12);
  oled.printf("%.0f%cC", celcius, (char)247);
  oled.setCursor(50, 38);
  oled.printf("%.0f%%", humidity);
  oled.display();

  delay(1000);
}

