#include <SoftwareSerial.h>
#define BT_RX  10
#define BT_TX  11
// 192.168.129.22

SoftwareSerial esp8266(BT_RX, BT_TX); // RX, TX
String comand = "AT";
String dynamicValue = "DESDE ARDUINO";
String responseESP = "";
int index = 0;

String ordenes[]=
  {  
     "AT",
     "AT+CWJAP?",
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

  esp8266.println(ordenes[index]);
  delay(1000);
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
           // Actualizamos el valor dinámico (esto es solo un ejemplo, actualiza según tu lógica)
           dynamicValue = String(millis()); // Usar el tiempo transcurrido desde que empezó el Arduino como valor dinámico

           // Construimos el contenido HTML dinámico
           String htmlContent = buildHtmlContent(dynamicValue);
           String commandSend = "AT+CIPSEND=0," + String(htmlContent.length());
           esp8266.println(commandSend);
           //esp8266.println(ordenes[index]);
           delay(500);
           
           // verficamos si se puede enviar mensaje
           if (responseESP8266().indexOf(">") != -1) {
            
            // enviamos mensaje
            esp8266.print(htmlContent);
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
    Serial.println("Resteando...");
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

String buildHtmlContent(String dynamicValue) {
  String html = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<!DOCTYPE html>"
    "<html><head><title>ESP8266 Web Server</title></head>"
    "<body><h1>Parcial 2, Robotica II</h1>"
    "<p>Distancia: " + dynamicValue + "</p>"
    "</body></html>";
  return html;
}
