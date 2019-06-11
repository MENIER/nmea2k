/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#define ESP32_CAN_TX_PIN GPIO_NUM_5
#define ESP32_CAN_RX_PIN GPIO_NUM_4
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(ARDUINO_BOARD);
  Serial.printf_P( PSTR("Comile time: %s %s\n"), __DATE__ , __TIME__ );
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ESP32_CAN_TX_PIN, OUTPUT);
  pinMode(ESP32_CAN_RX_PIN, INPUT);
   digitalWrite(ESP32_CAN_TX_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(ESP32_CAN_TX_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
 bool lastRead=1;
// the loop function runs over and over again forever
void loop() {
 
  if(digitalRead(ESP32_CAN_RX_PIN)!=lastRead)
  {
    lastRead=!lastRead;
    Serial.println("LEVEL CHANGE");
  }
 }
