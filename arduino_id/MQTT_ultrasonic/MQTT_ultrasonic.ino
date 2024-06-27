#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ultrasonic.h>

// Definición de pines para el sensor ultrasónico
#define TRIGGER_PIN 12
#define ECHO_PIN 13

// Inicialización del objeto Ultrasonic
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

// Configuración de WiFi
#define WIFI_SSID         "Flia. Colque"
#define WIFI_PASSWORD     "b805z45w"


// Configuración del servidor MQTT
#define MQTT_SERVER       "192.168.1.5"
#define MQTT_CLIENT_ID    "ESP8266UltrasonicSensor"
#define DISTANCE_TOPIC    "sensor/ultrasonic/distance"

// Inicialización de los objetos WiFi y PubSubClient
WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  Serial.begin(115200);
  setupWiFi();
  client.setServer(MQTT_SERVER, 1883);
}

void loop() {
  if (!client.connected()) {
      reconnect();
  }
  client.loop();

  // Captura de la distancia usando el sensor ultrasónico
  int distance = ultrasonic.distanceRead();

  // Publicación de la distancia al servidor MQTT
  String distanceStr = String(distance);
  client.publish(DISTANCE_TOPIC, distanceStr.c_str(), true);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Espera de 1 segundo antes de la siguiente lectura
  delay(1000);
}

void setupWiFi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect(MQTT_CLIENT_ID)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}
