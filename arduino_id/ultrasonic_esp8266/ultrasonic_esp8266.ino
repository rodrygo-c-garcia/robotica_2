// ESP82266 + HC-SR04
#include <SoftwareSerial.h>
#include <Ultrasonic.h>


#define BT_RX  10  // Pin RX para el módulo ESP8266
#define BT_TX  11  // Pin TX para el módulo ESP8266

// SENSOR ULTRASONICO
int triggerPin = 8;
int echoPin = 9;
int distance = 0;

//Ultrasonic ultrasonic(trigger, echo)
Ultrasonic ultrasonic(triggerPin, echoPin);


SoftwareSerial esp8266(BT_RX, BT_TX); // RX, TX
String responseESP = "";
int index = 0; // Índice para recorrer los comandos AT

// comandos AT para la conexion
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
}

void loop() {
  distance = ultrasonic.read(); // retorna la distancia en cm

  // obtenemos la respuesta del ESP8266
  responseESP = responseESP8266(); 

  // chequea si la respuesta es correcta o no.
  if(checkResponse(responseESP)) {
     // imprimimos la respuesta en el Monitor Serial
    Serial.println("Respuesta: ");
    Serial.println(responseESP);

    // verfica si el comando en el que estamos, es para configurar el servidor
    if (ordenes[index].equals("AT+CIPSERVER=1,80")) {
      int esperar = 0; // Contador para esperar la conexión
      responseESP = "";

      // ciclo donde esperaremos la conexion de un cliente
      while (true) {
        Serial.println("Esperando conexion...");
        Serial.println(ordenes[index]); // mostroamos en el monitor serial el comando actual en que estamos
        
        responseESP = responseESP8266();  // en cada iteracion del ciclo, siempre consultaremos si el ESP8266 tiene algo que responder

        // en caso de tener una respuesta, verificamos si es una solicitud de un cliente
        if (checkConecction(responseESP)) {
           index++;
           String comandCIPSEND = "AT+CIPSEND=0," + String(distance).length(); // formamos el comando para enviar el mensaje con los bytes de distancia
           esp8266.println(comandCIPSEND);  // enviamos el comando para que se pueda enviar un mensaje
           delay(1000);
           
           // verficamos si se puede enviar mensaje
           if (responseESP8266().indexOf(">") != -1) {
            esp8266.print("Distancia: ");
            // enviamos mensaje
            esp8266.print(distance);
            esp8266.println(" cm");
            Serial.println("Mensaje Enviado");
            // una vez enviado el mensaje salimos del ciclo para continuar con el siguiente comando, que es cerrar el CIPCLOSE
            break;
           } else {
            Serial.println("Mensaje no enviado");
            index -= 2;
            break;
           }
        }

        // esperamos 1 minuto para que un cliente pueda conectarse
        if (esperar == 30) {
          Serial.println("SALIENDO...");
          index=-1;
          // si no hay cliente, salimos para configurar nuevamente el servidor con CIPSERVER
          break;
        }
        Serial.println(responseESP);
        delay(1000);
        esperar++;
      }
    }
  } 
  // En caso de que el comando AT sea error.
  else {
    Serial.println("ERROR EN AT");
    index = -1;
  }
  // en cada loop se ira incrementando el index, con eso garantizamos para avanzar al siguiente comando
  index++;
  // entonces enviamos el comando siguiente
  esp8266.println(ordenes[index]);
  // esperamos 1 minuto
  delay(1000);
  responseESP = "";

  // verificamos si estamos en el ultimo comando AT+RST para setear el indice y comenzar todo de nuevo 
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
    if (response.indexOf("ERROR") == -1) {
      return true;
    }
    return false;
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
