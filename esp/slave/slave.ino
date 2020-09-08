// Wire Slave Sender
// by devyte
// based on the example of the same name by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// This example code is in the public domain.


#include <Wire.h>

#define SDA_PIN 4
#define SCL_PIN 5
const int16_t I2C_SLAVE = 0x0C;

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN, I2C_SLAVE);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);
  Serial.print("Wire Buffer Length=");
  Serial.println(BUFFER_LENGTH);
}

void loop() {
  delay(100);
}
// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.println(c);
   }
}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  char chars[] = "ABC";
  Serial.println(chars);
  Wire.write(chars);
}
