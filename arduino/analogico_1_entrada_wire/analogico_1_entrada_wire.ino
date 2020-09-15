/*girar el motor en el sentido y velocidad dada por consola (Posteriormente re recibiría ambos valores desde el rpi )*/
#include <Wire.h>
//motor
int pwm=9; //regular la velocidad en el motor
int MOThorario=10; //girar en sentido horario el motor
int MOTantihorario=11; //girar en sentido antihorario el motor


int sentido;
int velocidad;
int velMapeada;

void setup() {
  Wire.begin(0x8); //asignar dirección 8 y asociar como esclavo al arduino
  pinMode (pwm,OUTPUT);
  pinMode (MOThorario,OUTPUT);
  pinMode (MOTantihorario,OUTPUT);
  Serial.begin(9600);
  Serial.println("intruzca la sentido y la velocidad(separados por coma)  velocidad en procentaje");
  Serial.println("sentido=1 Horario");
  Serial.println("sentido=2 Antihorario");
//  Wire.onReceive(receiveEvent);
//  Wire.onRequest(requestEvent);
}
 
void loop() {
  delay(500);
  sentido = Serial.parseInt();
  velocidad = Serial.parseInt();
//inicia solo si se cargan datos
if (sentido>0 && velocidad>0) {
  switch (sentido) {
  case 1:
      girarHorario();
    break;
  case 2:
      girarAntiHorario();
    break;
}
//mapear la velocidad de 1-100 a 0-255
velMapeada= round((velocidad*255)/100);


  acelerar(pwm);
  }
Serial.print(" sentido:");
Serial.println(sentido);
Serial.print(" velocidad:");
Serial.println(velocidad);
Serial.print(" velMapeada:");
Serial.println(velMapeada);
//acelerar();  
//girarHorario();
//girarAntiHorario();
//desacelerar();
}

void acelerar(int pwm0){
  for (int pwm = 0; pwm < velMapeada; pwm++){
     analogWrite(pwm0,pwm); 
     delay(30);
  }
  }
void desacelerar(int pwm0){
  for (int pwm = 255; pwm > 0; pwm--){
     analogWrite(pwm0,pwm); 
     delay(100);
  }
}
void girarHorario(){
  digitalWrite(MOThorario,HIGH);
  digitalWrite(MOTantihorario,LOW);
  }
void girarAntiHorario(){
  digitalWrite(MOThorario,LOW);
  digitalWrite(MOTantihorario,HIGH);
  }

void detener(){
  digitalWrite(MOThorario,LOW);
  digitalWrite(MOTantihorario,LOW);
  }

/*void receiveEvent(int howMany) { //dejar el howmany sino se rompe 
  while (Wire.available()) { // loop through all but the last
    x = Wire.read(); // receive byte as a character
    if (x == HIGH){   //si llego un 1
      apretar();
    }
  }
} */
  
