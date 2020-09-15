/*ejemplo de almacenar distintos estados de todos los pines
posteriormente generar el codigo de mensaje con toda la info*/
int X;
int miArray[70];
String salida; //en salida quedan guardados el estado de los pins
void setup() {
  pinMode (1,INPUT);
  pinMode (2,OUTPUT);
  pinMode (3,INPUT);
  pinMode (4,INPUT);
  pinMode (5,OUTPUT);
  pinMode (6,OUTPUT);
  pinMode (7,INPUT);
  pinMode (8,INPUT);
  pinMode (9,OUTPUT);
  pinMode (A1,INPUT);
  pinMode (A2,OUTPUT);
  pinMode (A3,INPUT);
  pinMode (A4,INPUT);
  pinMode (A5,OUTPUT);
  pinMode (A6,OUTPUT);
  pinMode (A7,INPUT);
  pinMode (A8,OUTPUT);
  pinMode (A9,OUTPUT);
  Serial.begin(9600);
//el pin mas alto del atmega2560 es el A15 que vale 69
}
void loop() {
  delay(1000);

 for (int i = 0; i <= 69; i++) {
 int nro = i;
 miArray[nro] = getPinMode(nro);
 Serial.print(nro);
 Serial.print("Modo:");
 Serial.println(miArray[nro]);
 salida= salida+miArray[nro];
   delay(100);
  }
  Serial.print(salida);

/*
X= getPinMode(2);
Serial.print("X:");
Serial.println(X);
*/
}
//en el original input o nada te devuelve 0, output devuelve 1
uint8_t getPinMode(uint8_t pin){
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  volatile uint8_t *reg = portModeRegister(port);
 /*    Serial.print("bit:");
     Serial.println(bit);
     Serial.print("reg:");
     Serial.println(*reg);
     Serial.print("reg y bit:");
     Serial.println(*reg & bit);
  */
  if (*reg & bit) {
     return OUTPUT;
  } else {
     return INPUT;
  }
}
