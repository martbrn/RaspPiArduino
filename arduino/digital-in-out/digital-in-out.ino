

/**
Teniendo en cuenta la entrada de un boton activar una secuencia de leds, si la entrada se repite en un lapso determinado de tiempo
el led siguiente de la secuencia se activara y asi sucesivamente, caso contrario se apagaran y volvera al estado inicial
repositorio:
*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int Led_rojo = 2;   //Pin digital 2 led rojo
const int Led_amarillo = 3;   //Pin digital 3 led amarillo
const int Led_verde = 4;   //Pin digital 4 led verde(azul)
const int btn = 10;   //Pin digital 10 para el boton
long int cont=0;
int btn_estado=LOW; // inicio el estado del boton en apagado
int led_estado=0;
int btn_anterior=LOW;
const int tiempo=5000; //tiempo maximo de espera por una proxima pulsacion del boton

LiquidCrystal_I2C lcd(0x3F,16,2);//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación del arduino con el monitor del IDE
  lcd.init(); // iniciar el lcd
  lcd.backlight();
  pinMode(Led_rojo, OUTPUT); //led como salida
  pinMode(Led_amarillo, OUTPUT); //led como salida
  pinMode(Led_verde, OUTPUT); //led como salida
  pinMode(btn, INPUT);  //boton como entrada
}

void loop()
{
btn_estado=digitalRead(btn);
if (btn_estado == HIGH){
apretar();
}
Serial.print(" estado: ");
Serial.print(btn_estado);
Serial.print(" ---tiempo: ");
Serial.println(cont);
delay(250);
cont=cont+250;

}
void apretar(){
  lcd.clear();
  lcd.print("Tiempo: ");
  lcd.print(cont);
  if (cont<tiempo) {
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
    } else {
            apagado();
            }
  cont=0;       
  }

void apagado(){
              led_estado=0;
            digitalWrite(Led_verde,LOW);
            digitalWrite(Led_amarillo,LOW);
            digitalWrite(Led_rojo,LOW);}
