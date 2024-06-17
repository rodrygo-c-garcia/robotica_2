ESP8266 O ESP01/07

prerrequisitos instalar el módulo esp8266

https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/

Diagrama circuital y pasos para subir el código a ESP8266

https://electronics-project-hub.com/send-ultrasonic-sensor-data-to-thingspeak/



Código ESP8266

#include <ESP8266WiFi.h>

const char *ssid = "CUCHU";
const char *password = "Herrera.";

WiFiServer server(80);
String header;
String distance;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 10000;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop()
{
    WiFiClient client = server.available();
    if (client)
    {
        String currentLine = "";
        currentTime = millis();
        previousTime = currentTime;
        while (client.connected() && currentTime - previousTime <= timeoutTime)
        {
            currentTime = millis();
            if (client.available())
            {
                char c = client.read();
                header += c;
                if (c == '\n')
                {
                    if (currentLine.length() == 0)
                    {
                        Serial.println("on");
                        delay(1000);
                        while (Serial.available() > 0)
                        {
                            char c = Serial.read();
                            distance += c;
                        }
                        client.println("HTTP/1.1 200 OK");
                        client.println("Access-Control-Allow-Origin:*");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
                        client.println("<body>");
                        client.println(distance);
                        client.println("</body></html>");
                        client.println();
                        break;
                    }
                    else
                    {
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {
                    currentLine += c;
                }
            }
        }
        header = "";
        distance = "";
        client.stop();
    }
}