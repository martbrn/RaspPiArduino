/*girar el motor en el sentido y velocidad dada por consola (Posteriormente re recibiría ambos valores desde el rpi )*/
//motor
int pwm=9; //regular la velocidad en el motor
int MOThorario=10; //girar en sentido horario el motor
int MOTantihorario=11; //girar en sentido antihorario el motor


int sentido;
int velocidad;


void setup() {

  pinMode (pwm,OUTPUT);
  pinMode (MOThorario,OUTPUT);
  pinMode (MOTantihorario,OUTPUT);
  Serial.begin(9600);
  Serial.println("intruzca la sentido y la velocidad(separados por coma)  velocidad en procentaje");
  Serial.println("sentido=1 Horario");
  Serial.println("sentido=2 Antihorario");
}
 
void loop() {
  delay(500);
  sentido = Serial.parseInt();
  velocidad = Serial.parseInt();

if (sentido>0 && velocidad>0) {
  switch (sentido) {
  case 1:
      girarHorario();
    break;
  case 2:
      girarAntiHorario();
    break;
  default:
      girarHorario();
    break;
}

  acelerar(pwm);
  }

Serial.print(velocidad);
Serial.print(sentido);
//acelerar();  
//girarHorario();
//girarAntiHorario();
//desacelerar();
}

void acelerar(int pwm0){
  for (int pwm = 0; pwm < 256; pwm++){
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

  
