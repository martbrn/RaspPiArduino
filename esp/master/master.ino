// Wire Master Writer
// by devyte
// based on the example of the same name by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// This example code is in the public domain.


#include <Wire.h>
#include <PolledTimeout.h>

#define SDA_PIN 4
#define SCL_PIN 5
const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x08;
byte x = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");  
  Wire.begin(SDA_PIN, SCL_PIN); // join i2c bus (address optional for master)
  x = 0;
}


void loop() {
  using periodic = esp8266::polledTimeout::periodicMs;
  static periodic nextPing(2000);
  
  if (nextPing) {
    Wire.beginTransmission(I2C_SLAVE); // transmit to device #8
    Serial.println("M->S=");        // sends five bytes
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    x++;
    Wire.requestFrom(I2C_SLAVE, 6);    // request 6 bytes from slave device #8
    while (1 < Wire.available()) { // slave may send less than requested
      char c = Wire.read(); // receive a byte as character
      Serial.print(c);         // print the character
    }
    int y = Wire.read();    // receive byte as an integer
    Serial.println(y);
  }
}
