/*
  Arduino Slave for Raspberry Pi Master
  i2c_slave_ard.ino
  Connects to Raspberry Pi via I2C
  
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Include the Wire library for I2C
#include <Wire.h>

// LED on pin 13
const int ledPin = 13; 
byte x = 0;
String msg;
void setup() {
  Serial.begin(9600);
  Serial.print("Wire Buffer Length=");
  Serial.println(BUFFER_LENGTH);
  // Join I2C bus as slave with address 8
  Wire.begin(0xA);
  
  // Call receiveEvent when data received                
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  // Setup pin 13 as output and turn LED off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}
void requestEvent() {
  //Wire.write("S->M=");
  Serial.println(msg);
  int buffer_len = msg.length() + 1;
  char chars[buffer_len];
  msg.toCharArray(chars, buffer_len);
  Serial.println(chars);
  Wire.write(chars);
}
// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  msg = "";
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    digitalWrite(ledPin, c);
    Serial.println(c);
   }
}
void loop() {
  delay(100);
}
