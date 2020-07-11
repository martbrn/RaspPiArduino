#include<Wire.h>
bool flag1 = LOW;
byte x;

void setup()
{
  Serial.begin(9600);
  Wire.begin(0x08);
  pinMode(13, OUTPUT);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(sendEvent);
}

void loop()
{
  if (flag1 == HIGH)
  {

    Serial.println(x, HEX);
    flag1 = LOW;
  }
  digitalWrite(13, !digitalRead(13));
  delay(1000);
}

void receiveEvent(int howmany)
{
  x = Wire.read();
  flag1 = HIGH;
  //Serial.print(x, HEX);
}

void sendEvent(int howmany)
{
  Wire.write(0x45);
}
