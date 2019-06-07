//#include "setupEsp.h"
#ifdef ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#endif
void setupEsp()
{
#ifdef ARDUINO_ARCH_ESP8266
  Serial.print(F("ESP8266 Core Version:"));  Serial.println(ESP.getCoreVersion());
//  Serial.print(F("ChipId:"              ));  Serial.println(ESP.getChipId     ());
#endif
#ifdef ARDUINO_ARCH_ESP32
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  Serial.printf_P(PSTR("ESP32 %d cores\nWiFi%s%s\n"), chip_info.cores,
                  (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
                  (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
  Serial.printf_P(PSTR("ESP Rev.%d\n"), chip_info.revision);
//  Serial.printf_P(PSTR("%dMB %s Flash\n"), spi_flash_get_chip_size() / (1024 * 1024),
//                 (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "int." : "ext.");
//  chipid = ESP.getEfuseMac();
#endif
#ifdef ARDUINO_ARCH_ESP32 ||ARDUINO_ARCH_ESP8266
  Serial.print( F("Heap: ") ); Serial.println(system_get_free_heap_size());
//  Serial.print( F("Boot Vers: ") ); Serial.println(system_get_boot_version());
//  Serial.print( F("CPU: ") ); Serial.println(system_get_cpu_freq());
  Serial.print( F("SDK: ") ); Serial.println(system_get_sdk_version());
//  Serial.print( F("Chip ID: ") ); Serial.println(system_get_chip_id());
//  Serial.print( F("Flash ID: ") ); Serial.println(spi_flash_get_id());
//  Serial.print( F("Flash Size: ") ); Serial.println(ESP.getFlashChipRealSize());
//  Serial.print( F("Vcc: ") ); Serial.println(ESP.getVcc());
  Serial.println();
#endif
#ifdef ARDUINO_ARCH_ESP8266
  Serial.print( F("Heap: ") ); Serial.println(system_get_free_heap_size());
  Serial.print( F("Boot Vers: ") ); Serial.println(system_get_boot_version());
  Serial.print( F("CPU: ") ); Serial.println(system_get_cpu_freq());
  Serial.print( F("SDK: ") ); Serial.println(system_get_sdk_version());
  Serial.print( F("Chip ID: ") ); Serial.println(system_get_chip_id());
  Serial.print( F("Flash ID: ") ); Serial.println(spi_flash_get_id());
  Serial.print( F("Flash Size: ") ); Serial.println(ESP.getFlashChipRealSize());
  Serial.print( F("Vcc: ") ); Serial.println(ESP.getVcc());
  Serial.println();
#endif
}
