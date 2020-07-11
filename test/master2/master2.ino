#include<Wire.h>

void setup()
{
  Wire.begin(4, 5);
  Serial.begin(9600);
 
  Wire.beginTransmission(0x08);
  Wire.write(0x23);
  byte busStatus = Wire.endTransmission();
  Serial.println(busStatus);

  Wire.requestFrom(0x08, 1);
  byte x = Wire.read();
}

void loop()
{

}
