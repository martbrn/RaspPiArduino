/**/
//sensor
const int Trigger = 2;   //Pin digital 2 para el Trigger del sensor
const int Echo = 3;   //Pin digital 3 para el echo del sensor
long t; //timepo que demora en llegar el eco
long d; //distancia en centimetros
//motor
int motor = 6;
int sentido1 = 7;
int sentido2 = 8;
int giro1=HIGH; //declarar un sentido de giro inicial
int giro2=LOW; //declarar un sentido de giro inicial
int estado=LOW;
int pwm;
//vibrador
int motorV = 3;
int sentidoV1 = 4;
int sentidoV2 = 5;
int giroV1=HIGH; //declarar un sentido de giro inicial
int giroV2=LOW; //declarar un sentido de giro inicial
int estadoV=LOW;
int velPWM=255;
int contaBarra=0;
void setup() {
  Serial.begin(9600);
//motor
  pinMode(motor, OUTPUT);
  pinMode(sentido1,OUTPUT);
  pinMode(sentido2,OUTPUT);
  digitalWrite(sentido1,giro1);
  digitalWrite(sentido2,giro2);
//motorV
  pinMode(motorV, OUTPUT);
  pinMode(sentidoV1,OUTPUT);
  pinMode(sentidoV2,OUTPUT);
  digitalWrite(sentidoV1,giroV1);
  digitalWrite(sentidoV2,giroV2);

//sensor HC-SR04
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
}

void loop() {
 // acelerar(motor);
 //desacelerar(motor);


//HC-SR04
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

//contador
Serial.print("Cantidad de cargas: ");
Serial.println(contaBarra);

if (d > 5 && !estado){
    acelerar(motor);
  }
  else if (d < 5 && estado) {
    desacelerar(motor);
    contaBarra=contaBarra + 1;
    vibrar(motorV);
  };
  
  delay(100);   

}

void acelerar(int M){
  for (pwm = 0; pwm < 256; pwm++){
     analogWrite(M,pwm); 
     delay(20);
  }
  estado=HIGH;
  }
void desacelerar(int M){
  for (pwm = 255; pwm > 0; pwm--){
     analogWrite(M,pwm); 
     delay(5);
  }
  estado=LOW;
}
void girarDerecha(){
  desacelerar(motor);
  digitalWrite(sentido1,giro1);
  digitalWrite(sentido2,giro2);
  acelerar(motor);
  }
void girarIzquierda(){
  desacelerar(motor);
  digitalWrite(sentido1,giro2);
  digitalWrite(sentido2,giro1);
  acelerar(motor);
  }
void detener(int M){
   analogWrite(M,0); 
   estado=LOW;
  }
void vibrar(int mV){
  analogWrite(mV,velPWM); 
  delay(3000);
  analogWrite(mV,0); 
  }
