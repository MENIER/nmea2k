void setupSerial()
{
Serial.begin(115200);
  while (!Serial)
    delayMicroseconds(200000);
  delayMicroseconds(2000000);
}
