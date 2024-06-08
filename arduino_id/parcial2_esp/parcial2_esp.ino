/* 
  Este programa utiliza un ESP8266 y un sensor ultrasónico HC-SR04 para medir distancias y 
  mostrar los resultados en una página web.

  Desarrollado por los estudiantes:
  - Ariel Rodrigo Colque Garcia (Ing. en Ciencias de la Computacion)
  - Omar Cruz Quiroga (Ing. en Telecomunicaciones)
  
  Para configurar y conectar el ESP8266 a una red WiFi, sigue estos pasos:
  1. Carga un código vacío en el Arduino para usarlo como un puente serial.
  2. Conecta el pin TX del ESP8266 al pin TX del Arduino.
  3. Conecta el pin RX del ESP8266 al pin RX del Arduino.
  4. Abre el Monitor Serial del IDE de Arduino y usa los siguientes comandos AT para conectar el ESP8266 a tu red WiFi:
     - AT+CWJAP="tu_SSID","tu_contraseña"     (Para conectarse a la red WiFi)
     - AT+CIFSR                             (Para obtener la dirección IP asignada)
  5. Una vez conectado y obtenida la IP, reconfigura las conexiones:
     - Conecta el pin TX del ESP8266 al pin RX del Arduino (pin 10)
     - Conecta el pin RX del ESP8266 al pin TX del Arduino (pin 11)
     - Conecta los pines del sensor ultrasónico al Arduino (triggerPin = 8, echoPin = 9)
  6. Carga el código a continuación en el Arduino y ejecuta.
    Funcionalidad del programa:
    - Una vez ejecutado el programa, el servidor se iniciará en el puerto 80 para escuchar peticiones.
    - El Monitor Serial mostrará la distancia a enviar medida por el sensor ultrasónico.
    - Cuando se recibe una solicitud del cliente, se envía un código HTML al ESP8266 junto con la distancia capturada.
    - Después de enviar la respuesta, el ESP8266 se reinicia para liberar el buffer y evitar saturaciones.
    - Debido al reinicio, la página web no estará disponible durante 12 segundos.
    - Pasados los 12 segundos, se podrá hacer una nueva solicitud, repitiendo el ciclo.

  Nota: Asegúrate de que la configuración de pines en el código coincide con las conexiones físicas.

  Código principal:
*/

// ESP82266 + HC-SR04
#include <SoftwareSerial.h>
#include <Ultrasonic.h>
// 192.168.1.3

#define BT_RX  10  // Pin RX para el módulo ESP8266
#define BT_TX  11  // Pin TX para el módulo ESP8266

// SENSOR ULTRASONICO
int triggerPin = 8;
int echoPin = 9;
int distance = 0;

bool send = false;
String htmlContent = "";

//Ultrasonic ultrasonic(trigger, echo)
Ultrasonic ultrasonic(triggerPin, echoPin);

SoftwareSerial esp8266(BT_RX, BT_TX); // RX, TX

void setup() {
  Serial.begin(9600);  // monitor serial del arduino
  esp8266.begin(9600); // baud rate del ESP8255
 
  sendComands();
}

void loop() {
  distance = ultrasonic.read(); // retorna la distancia en cm
  Serial.print("Distancia a Enviar: ");
  Serial.println(distance);
  
  htmlContent = buildHtmlContent(String(distance));
  delay(100);

  // Verifica si hay respuesta del modulo
  if(esp8266.available()) {
    // verifica si hay peticion o no
    if(esp8266.find("+IPD,")) { 
      while(esp8266.available()){
       char c = esp8266.read();
       Serial.print(c);
      }

      String comandCIPSEND = "AT+CIPSEND=0," + String(htmlContent.length()) + "\r\n"; // formamos el comando para enviar el mensaje con los bytes de distancia
      
      sendData(comandCIPSEND,1000); // enviamos el comando al ESP8266

      // enviamos el codigo HTML
      esp8266.print(htmlContent);
      Serial.println("HTML enviado");

      String comandCIPCLOSE = "AT+CIPCLOSE=0\r\n";
      sendData(comandCIPCLOSE,1000);

      String comandCIPSERVER = "AT+CIPSERVER=0\r\n";
      sendData(comandCIPSERVER,1000);
      send = true;
    }
  } 

  // verificamos si el HTML ha sido enviado
  if (send) {
    send = false;
    sendData("AT+RST\r\n", 2000); // Resetear módulo
    Serial.println("RESETEANDO...");
    delay(4500);
    sendComands();
  }
}

/*
Enviar comando al esp8266 y verificar la respuesta del módulo, todo esto dentro del tiempo timeout
*/
void sendData(String comando, const int timeout)
{
 long int time = millis(); // medir el tiempo actual para verificar timeout
 
 esp8266.print(comando); // enviar el comando al ESP8266
 while((time+timeout) > millis()) {
   while(esp8266.available()) { 
     // Leer los datos disponibles
     char c = esp8266.read(); // leer el siguiente caracter
     Serial.print(c);
   }
 } 
 return;
}

void sendComands() {
  sendData("AT+CIFSR\r\n",1000);    // obtener dirección IP
  sendData("AT+CIPMUX=1\r\n",1000); // configurar para multiples conexiones
  sendData("AT+CIPSERVER=1,80\r\n",1000);   // servidor en el puerto 80
}

// metodo para formar el codigo HTML
String buildHtmlContent(String distance) {
  String html = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<title>ESP8266</title>"
    "<style>"
    "body, html {"
    "  display: flex;"
    "  height: 100%;"
    "  margin: 0;"
    "  align-items: center;"
    "  justify-content: center;"
    "  background-color: #f2f2f2;"
    "}"
    ".container {"
    "  display: flex;"
    "  flex-direction: column;"
    "  text-align: center;"
    "}"
    "h1 {"
    "  color: #333;" 
    "  font-size: 4em;"
    "}"
    "h2 {"
    "  color: #666;"
    "  font-size: 3em;"
    "}"
    "button {"
    "  background-color: #4CAF50;"
    "  color: white;"
    "  border: none;"
    "  padding: 20px 30px;"
    "  border-radius: 20px;"
    "  cursor: pointer;"
    "  font-size: 2.2em;"
    "}"
    "button:disabled {"
    "  background-color: #cccccc;" 
    "  cursor: not-allowed;" 
    "}"
    "#countdown {"
    "  font-size: 2.2em;"
    "}"
    "</style>"
    "</head>"
    "<body>"
    "<div class='container'>"
    "<h1>ESP8266 & HC-SRO4</h1>"
    "<h2>Distancia: <span style='font-size: 3em;'>" + distance + " cm</span></h2>"
    "<button id='reloadButton' onclick='reloadPage()' disabled>Solicitar Distancia</button>" 
    "<p style='font-size: 2em;'>Solicitud disponible en <span id='countdown'></span> segundos</p>"
    "<script>"
    "function reloadPage() {"
    "  location.reload();"
    "}"
    "var counter = 12;" 
    "function updateCounter() {"
    "  document.getElementById('countdown').innerText = ' ' + counter + '';" 
    "  if (counter > 0) {" 
    "    setTimeout(updateCounter, 1000);" 
    "  } else {" // Si el contador llega a 0, habilitar el botón
    "    document.getElementById('reloadButton').disabled = false;"
    "  }"
    "  counter--;" 
    "}"
    "document.addEventListener('DOMContentLoaded', function() {"
    "  updateCounter();"
    "});"
    "</script>"
    "</div>"
    "</body>"
    "</html>";
  return html;
}
