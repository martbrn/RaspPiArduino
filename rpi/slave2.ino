#include <Wire.h>
const int ledPin = 13;
const int btnPin = 10;
int buttonState = 0;
int contador = 0;

void setup() {
  Serial.begin(9600);
  contador = 0;
  
  //I2C
  Wire.begin(0x8);
  Wire.onReceive(receiveEvent); 
  Wire.onRequest(requestEvent);
  
  //IO
  pinMode(btnPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}
void receiveEvent(int howMany){
  while(Wire.available()){
    char c = Wire.read();
    digitalWrite(ledPin, c);
  }
}
void requestEvent() {
  Wire.write("S->M=");
  Wire.write(contador);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  buttonState = !buttonState;// digitalRead(btnPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
	contador++;
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}