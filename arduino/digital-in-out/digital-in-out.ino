/**
Teniendo en cuenta la entrada de un boton activar una secuencia de leds, si la entrada se repite en un lapso determinado de tiempo
el led siguiente de la secuencia se activara y asi sucesivamente, caso contrario se apagaran y volvera al estado inicial
repositorio:
*/
const int Led_rojo = 2;   //Pin digital 2 led rojo
const int Led_amarillo = 3;   //Pin digital 3 led amarillo
const int Led_verde = 4;   //Pin digital 4 led verde(azul)
const int SDAlcd = 5;   //Pin digital 5 para conexion SDA a la pantalla
const int SCLlcd = 6;   //Pin digital 6 para conexion SCL a la pantalla
const int btn = 10;   //Pin digital 10 para el boton
int cont=0;
int btn_estado=LOW; // inicio el estado del boton en apagado
int led_estado=0;
int btn_anterior=LOW;
const int tiempo=5; //tiempo maximo de espera por una proxima pulsacion del boton
void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación del arduino con el monitor del IDE
  pinMode(Led_rojo, OUTPUT); //led como salida
  pinMode(Led_amarillo, OUTPUT); //led como salida
  pinMode(Led_verde, OUTPUT); //led como salida
  pinMode(SDAlcd, OUTPUT); //SDA como salida
  pinMode(SCLlcd, OUTPUT); //SCL como salida
  pinMode(btn, INPUT);  //boton como entrada
}

void loop()
{
btn_estado=digitalRead(btn);
if (btn_estado =0){
apretar();
}
delay(300);
Serial.println(digitalRead(btn));
}
void apretar(){
  if (cont<tiempo) {
    cont=cont+1;
    if (led_estado=0){digitalWrite(Led_verde,HIGH); led_estado=1;}
    if (led_estado=1){digitalWrite(Led_amarillo,HIGH);led_estado=2;}
    if (led_estado=2){digitalWrite(Led_rojo,HIGH);}
    } else {
            cont=0; 
            led_estado=0;
            digitalWrite(Led_verde,LOW);
            digitalWrite(Led_amarillo,LOW);
            digitalWrite(Led_rojo,LOW);
            }
         
  }
