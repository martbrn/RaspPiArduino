/**
Teniendo en cuenta la entrada desde el RPI activar una secuencia de leds, si la entrada se repite en un lapso determinado de tiempo
el led siguiente de la secuencia se activara y asi sucesivamente, caso contrario se apagaran y volvera al estado inicial
*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int Led_rojo = 2;   //Pin digital 2 led rojo
const int Led_amarillo = 3;   //Pin digital 3 led amarillo
const int Led_verde = 4;   //Pin digital 4 led verde(azul)
long int cont=0; // contador de tiempo transcurrido 
int led_estado=0; //indica cuantos led estan prendidos, 0 ninguno, 1 verde, 2 amarillo.
const int tiempo=5000; //tiempo maximo de espera por una proxima pulsacion del boton
byte x = 0;//byte a recibir desde el maestro
LiquidCrystal_I2C lcd(0x3F,16,2);//Crear el objeto lcd  dirección 0x3F y 16 columnas x 2 filas

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación del arduino con el monitor del IDE
  Wire.begin(0x8); //asignar dirección 8 y asociar como esclavo al arduino
  lcd.init(); // iniciar el lcd
  lcd.backlight(); //prender la luz de fondo 
  pinMode(Led_rojo, OUTPUT); //led como salida
  pinMode(Led_amarillo, OUTPUT); //led como salida
  pinMode(Led_verde, OUTPUT); //led como salida
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop()
{
delay(100);  
cont=cont+100;  
}
void apretar(){
  lcd.clear();  //limpia la pantalla sino se secuencian los textos
  lcd.print("Tiempo: ");
  lcd.print(cont);
  if (cont<tiempo) { // si paso menos de X segundos entre señales
    switch (led_estado){
  case 0:
        {digitalWrite(Led_verde,HIGH); led_estado=1;}
  break;
  case 1:
        {digitalWrite(Led_amarillo,HIGH);led_estado=2;}
  break;
  case 2:
        { int estado_rojo= digitalRead(Led_rojo);
          if (estado_rojo==HIGH){
                  apagado(); break;}
          digitalWrite(Led_rojo,HIGH);}
  break;
                        }
    } else { //si paso mas de 5 seg
            apagado();
            }
  cont=0;       
  }

void apagado(){
              led_estado=0;
            digitalWrite(Led_verde,LOW);
            digitalWrite(Led_amarillo,LOW);
            digitalWrite(Led_rojo,LOW);}

void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    x = Wire.read(); // receive byte as a character
    if (x == HIGH){   //si llego un 1
    apretar();
    }
  }
}
void requestEvent() {
  Serial.print("Sending estado=");
  Serial.println(led_estado);
  Wire.write(led_estado);
}
