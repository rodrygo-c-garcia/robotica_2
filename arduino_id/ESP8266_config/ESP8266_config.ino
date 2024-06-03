// ESP82266 + HC-SR04
#include <SoftwareSerial.h>
#define BT_RX  10
#define BT_TX  11
// 192.168.129.22

SoftwareSerial esp8266(BT_RX, BT_TX); // RX, TX
String comand = "AT";
String mensaje = "MENSAJE DESDE ARDUINO, CODIGO";
String responseESP = "";
int index = 0;
String ordenes[]=
  {  
     "AT",
     "AT+CIFSR",
     "AT+CIPMUX=1",
     "AT+CIPSERVER=1,80",
     "AT+CIPSEND=0,30",
     "AT+CIPCLOSE=0",
     "AT+CIPSERVER=0",
     "AT+RST",
  };

void setup() {
  // Inicia la comunicación serial con el baud rate adecuado
  Serial.begin(9600);
  esp8266.begin(9600);
}

void loop() {
  responseESP = responseESP8266();
  if(checkResponse(responseESP)) {
     // Enviar el dato al monitor serial
    Serial.println("Respuesta: ");
    Serial.println(responseESP);

    // Conexion del servidor
    if (ordenes[index].equals("AT+CIPSERVER=1,80")) {
      int esperar = 0;
      responseESP = "";
      while (true) {
        Serial.println("Esperando conexion...");
        Serial.println(ordenes[index]);
        
        responseESP = responseESP8266();
        if (checkConecction(responseESP)) {
           index++;
           esp8266.println(ordenes[index]);
           delay(500);
           
           // verficamos si se puede enviar mensaje
           if (responseESP8266().indexOf(">") != -1) {
            // enviamos mensaje
            esp8266.println(mensaje);
            Serial.println("Mensaje Enviado");
            break;
           } else {
            Serial.println("Mensaje no enviado");
            index -= 2;
            break;
           }
        }
        
        if (esperar == 30) {
          Serial.println("SALIENDO...");
          index=-1;
          break;
        }
        Serial.println(responseESP);
        delay(1000);
        esperar++;
      }
    }
  } else {
    Serial.println("ERROR EN AT");
    index = -1;
  }
  index++;
  esp8266.println(ordenes[index]);
  delay(500);
  responseESP = "";

  if(checkNotIsRST(index)){
    index = -1;
    responseESP = "";
    Serial.println("Reseteando...");
    delay(5000);
  }
}

String responseESP8266() {
  String response = "";
  
  if (esp8266.available()) {    
    while (esp8266.available()) {
      char c = esp8266.read();
      response += c;
    }
  }
  return response;
}


bool checkResponse(String response) {
  // Verificar si la respuesta contiene "ERROR"
    if (response.indexOf("ERROR") != -1) {
      return false;
    }
    return true;
}

bool checkConecction(String response) {
  // Verificar si la respuesta contiene "GET"
    if (response.indexOf("GET") != -1) {
      return true;
    }
    return false;
}

bool checkNotIsRST(int i) {
  if(ordenes[i].indexOf("AT+RST") != -1) {
    return true;
  }
  return false;
}
