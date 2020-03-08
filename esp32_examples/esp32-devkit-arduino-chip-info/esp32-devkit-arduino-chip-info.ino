// Author: Erwin Ouyang, aiotedge.tech
// Date  : 8 Mar 2020

void setup()
{
  // Initialize serial port
  Serial.begin(115200);
  
  // Print chip information
  Serial.printf("Chip ID (eFuse MAC): 0x%X\n", ESP.getEfuseMac());
  Serial.printf("Chip revision: %d\n", ESP.getChipRevision());
  Serial.printf("CPU frequency: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Cycle count: %u\n", ESP.getCycleCount());
  Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
  Serial.printf("Flash chip size: %d bytes\n", ESP.getFlashChipSize());
  Serial.printf("Flash chip speed: %d Hz\n", ESP.getFlashChipSpeed());
  Serial.printf("Flash chip mode: 0x%X\n", ESP.getFlashChipMode());
  Serial.printf("SDK version: %s\n", ESP.getSdkVersion());
}

void loop()
{
}

