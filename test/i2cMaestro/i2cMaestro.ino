#include <Wire.h>
#define I2CAddressESPWifi 8
int x=32;
void setup()
{
  Serial.begin(115200);
  Wire.begin(D1,D2);//Change to Wire.begin() for non ESP.
}
void loop()
{
  Wire.beginTransmission(I2CAddressESPWifi);
  Wire.write(x);
  Wire.endTransmission();
  x++;
  delay(1);//Wait for Slave to calculate response.
  Wire.requestFrom(I2CAddressESPWifi,10);
  Serial.print("Request Return:[");
  while (Wire.available())
  {
    delay(1);
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println("]");
  delay(1000);
}
