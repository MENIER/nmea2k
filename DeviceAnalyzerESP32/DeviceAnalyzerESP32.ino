#include <Arduino.h>
#include "setupBoard.h"
// Beware, the following constants MUST be defined before including NMEA2000_CAN.h
//#define USE_N2K_CAN 1  // for use with SPI and MCP2515 can bus controller
//#define USE_N2K_CAN 2  // for use with due based CAN
//#define USE_N2K_CAN 3  // for use with Teensy 3.1/3.2 boards
//#define USE_N2K_CAN 4  // for use with avr boards
//#define USE_N2K_CAN 5  // for use with socketCAN (linux, etc) systems
//#define USE_N2K_CAN 6  // for use with MBED (ARM) systems
//#define USE_N2K_CAN 7  // for use with ESP32
#ifdef ARDUINO_ARCH_ESP32
//#define USE_N2K_CAN 1
#define ESP32_CAN_TX_PIN GPIO_NUM_5
#define ESP32_CAN_RX_PIN GPIO_NUM_4
#else
#define USE_N2K_CAN 1
#define N2k_CAN_INT_PIN D0 // Use interrupt  and it is connected to pin 4
#define N2k_SPI_CS_PIN D4  // Pin for SPI Can Select
//#define USE_MCP_CAN_CLOCK_SET 16  // possible values 8 for 8Mhz and 16 for 16 Mhz clock, 10 for 10MHz clock
#define MCP_CAN_RX_BUFFER_SIZE 10
// set the n2kSourceId to a unique number on the NMEA2000 bus
const uint8_t n2kSourceId = 36;
#endif

#include <NMEA2000_CAN.h>  // This will automatically choose right CAN library and create suitable NMEA2000 object
#include <N2kDeviceList.h>

tN2kDeviceList *pN2kDeviceList;
Stream *OutputStream;

//*****************************************************************************
template<typename T> void PrintLabelValWithConversionCheckUnDef(const char* label, T val, double (*ConvFunc)(double val) = 0, bool AddLf = false ) {
  OutputStream->print(label);
  if (!N2kIsNA(val)) {
    if (ConvFunc) {
      OutputStream->print(ConvFunc(val));
    } else {
      OutputStream->print(val);
    }
  } else OutputStream->print("not available");
  if (AddLf) OutputStream->println();
}

//*****************************************************************************
void setup() {
  Serial.begin(115200);
  OutputStream = &Serial;
  delay(3000);
  setupBoard();
  Serial.println("Device analyzer is starting up...");
  NMEA2000.SetN2kCANReceiveFrameBufSize(150);
  NMEA2000.SetN2kCANMsgBufSize(8);
  // Set Product information
  NMEA2000.SetProductInformation("00000003", // Manufacturer's Model serial code
                                 100, // Manufacturer's product code
                                 "N2k bus device analyzer",  // Manufacturer's Model ID
                                 "1.0.0.10 (2017-07-29)",  // Manufacturer's Software version code
                                 "1.0.0.0 (2017-07-12)" // Manufacturer's Model version
                                );

  // Set device information
  NMEA2000.SetDeviceInformation(2, // Unique number. Use e.g. Serial number.
                                130, // Device function=Display. See codes on http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                120, // Device class=Display. See codes on  http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                2046 // Just choosen free from code list on http://www.nmea.org/Assets/20121020%20nmea%202000%20registration%20list.pdf
                               );
  // Uncomment 3 rows below to see, what device will send to bus

  NMEA2000.SetForwardStream(0); //&Serial);
  NMEA2000.SetForwardType(tNMEA2000::fwdt_Text); // Show in clear text. Leave uncommented for default Actisense format.
  // NMEA2000.SetForwardOwnMessages();

  NMEA2000.EnableForward(false);
  //***************************************************************
  // set the n2kSourceId to a unique number on the NMEA2000 bus
  //  const uint8_t n2kSourceId = 36;
  //  NMEA2000.SetMode(tNMEA2000::N2km_ListenAndNode, n2kSourceId);
  NMEA2000.SetMode(tNMEA2000::N2km_ListenAndNode, 50);
  pN2kDeviceList = new tN2kDeviceList(&NMEA2000);
  NMEA2000.Open();
  Serial.println("Device analyzer started");
}

//*****************************************************************************
void PrintUlongList(const char *prefix, const unsigned long * List) {
  uint8_t i;
  if ( List != 0 ) {
    Serial.print(prefix);
    for (i = 0; List[i] != 0; i++) {
      if (i > 0) Serial.print(", ");
      Serial.print(List[i]);
    }
    Serial.println();
  }
}

//*****************************************************************************
void PrintDevice(const tNMEA2000::tDevice *pDevice) {
  if ( pDevice == 0 ) return;

  Serial.println(pDevice->GetModelID());
  Serial.print("  Source: "); Serial.println(pDevice->GetSource());
  Serial.print("  Manufacturer code:        "); Serial.println(pDevice->GetManufacturerCode());
  Serial.print("  Unique number:            "); Serial.println(pDevice->GetUniqueNumber());
  Serial.print("  Software version:         "); Serial.println(pDevice->GetSwCode());
  Serial.print("  Model version:            "); Serial.println(pDevice->GetModelVersion());
  Serial.print("  Manufacturer Information: "); Serial.println(pDevice->GetManufacturerInformation());
  PrintUlongList("  Transmit PGNs :", pDevice->GetTransmitPGNs());
  PrintUlongList("  Receive PGNs  :", pDevice->GetReceivePGNs());
  Serial.println();
}

//*****************************************************************************
void ListDevices(bool force = false) {
  if ( !force && !pN2kDeviceList->ReadResetIsListUpdated() ) return;

  Serial.println();
  Serial.println("**********************************************************************");
  for (uint8_t i = 0; i < N2kMaxBusDevices; i++) PrintDevice(pN2kDeviceList->FindDeviceBySource(i));
}

//*****************************************************************************
void CheckCommand() {
  if (Serial.available()) {
    char chr = Serial.read();
    switch ( chr ) {
      case 'u': ListDevices(true); break;
    }
  }
}

//*****************************************************************************
void loop() {
  NMEA2000.ParseMessages();
  ListDevices();
  CheckCommand();
}
