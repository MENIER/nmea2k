//#include "setupBoard.h"
void  setupBoard()
{
  Serial.println(ARDUINO_BOARD);
  Serial.printf_P( PSTR("Comile time: %s %s\n"), __DATE__ , __TIME__ );
}
