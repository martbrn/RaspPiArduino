#include <Wire.h>
const unsigned char CM_CFG = 0x10;
const unsigned char CM_RDI = 0x20;
const unsigned char CM_WDO = 0x21;
const unsigned char CM_RAI = 0x22;
const unsigned char CM_WAO = 0x23;

const byte DIR_I2C = 0x8;//Direccion I2C
byte CM = 0x0;//Código de Mensaje
byte analogInput[32];

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando...");
  
  
  Wire.begin(DIR_I2C);       
  Wire.onReceive(receiveEvent); 
  Wire.onRequest(requestEvent); 
  
}

void loop() {
  delay(100);
}

//###Funciones primitivas
void serialPrintf(char* formato, char valor) {
     char texto[128];
     sprintf(texto, formato, valor);
     Serial.println(texto);
}
uint8_t getPinMode(uint8_t pin){  
  uint8_t bit = digitalPinToBitMask(pin);    
  uint8_t port = digitalPinToPort(pin);  
  volatile uint8_t *reg = portModeRegister(port);  
  if (*reg & bit) { return OUTPUT; }
  else { return INPUT; }
}
void parseAnalogInput(int val, byte pos){    
  analogInput[(2*pos)] = (val & 0xff00) >> 8;
  analogInput[(2*pos)+1] = val & 0x00ff;  
}

//read_i2c_block_data(DIR, #BYTES)
void requestEvent() {
  char* msg = "";  
  //Responderá al masters segun ultimo codigo de mensaje
  switch (CM) {
    case CM_CFG://0x10
      //TODO: Armar mensaje de la CONFIGURACION actual del Arduino
      //Serial.println("Procesar CFG");
      msg = "1";
      break;
    case CM_RDI://0x20
      //TODO: Armar mensaje de entradas DIGITALES actuales del Arduino
      //Serial.println("Procesar RDI");
      msg = "2";
      break;
    case CM_RAI://0x22
      //TODO: Armar mensaje de entradas ANALOGICAS actuales del Arduino
      //Serial.println("Processar RAI");
      msg = "3";
      break;
    default:
      //Serial.println("El Código de Mansaje  no requiere respuesta");
      msg = "9";
      break;
  }
  
  Wire.write(msg);
  //serialPrintf("Procesando Código de Mansaje actual=0x%x", CM);
}
//write_i2c_block_data()
void receiveEvent(int howMany) {
  //if (Wire.available()>1)
    //Wire.read();
    
  if (Wire.available()) {
    //Se actualiza CM para saber si es necesario procesar el mensaje para actualizar salidas
    //o si es solo el codigo de lo que el master le pedirá en el request.
    CM = Wire.read();
    //serialPrintf("Nuevo Código de Mansaje recibido=0x%x", CM);
  }
  Serial.println(CM);
  /*while (Wire.available()) {
    //Se actualiza CM para saber si es necesario procesar el mensaje para actualizar salidas
    //o si es solo el codigo de lo que el master le pedirá en el request.
    //serialPrintf("DATOS=0x%x", Wire.read());
  }
  switch (CM) {
    case CM_WDO://0x21
      //Es necesario parsear el resto del mensaje como valores digitales autoindexados
      Serial.println("Setear salidas DIGITALES con estados recibidos en mensaje");
      break;
    case CM_WAO://0x23
       //Es necesario parsear el resto del mensaje como valores analogicos indexados
      Serial.println("Setear salidas ANALOGICAS con valores recibidos en mensaje");
      break;
    default:
      Serial.println("El Código de Manesaje no requiere actualizar salidas");
      break;
  }
  */
}
