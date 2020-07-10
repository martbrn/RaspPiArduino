#include <Wire.h>
const int ledPin = 13;
const int btnPin = 10;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x8);
  Wire.onReceive(receiveEvent);
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
  digitalWrite(ledPin, LOW);
}
void receiveEvent(int howMany){
  while(Wire.available()){
    char c = Wire.read();
    digitalWrite(ledPin, c);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  buttonState = !buttonState;// digitalRead(btnPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
