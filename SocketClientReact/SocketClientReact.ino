/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "IZZI-ED55"
#define STAPSK "189C27F5ED55"
#endif

int valorLDR = A0;
int pinLED = 4;
int valoresLDR[5]; // Array para almacenar 5 valores del sensor LDR
int maximo = 681;
int minimo = 100;

int message;

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "192.168.0.7";  // la IP de la maquina en la red local
const uint16_t puerto = 5000;

void setup() {
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);

  // comienza conectandose a la red WiFi

  Serial.println();
  Serial.println();
  Serial.print("Conectando a red ");
  Serial.println(ssid);

  // especifica que el ESP8266 actue como cliente WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a WiFi");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int sensorValue = analogRead(valorLDR);
  message = sensorValue;
  
  Serial.print("Conectando con ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(puerto);

  // Utilizar la clase WiFiClient para crear conexiones TCP
  WiFiClient client;
  if (!client.connect(host, puerto)) {
    Serial.println("Conexion fallida");
    delay(5000);
    return;
  }

  Serial.println("Conexion exitosa con servidor");
  
  // Enviar un string al servidor
  Serial.println("Mandando datos al servidor");
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["message"] = message;
  String jsonData;
  serializeJson(jsonDoc, jsonData);

  if (client.connected()) {
    client.print("POST /data HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(host);
    client.print("\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Content-Length: ");
    client.print(jsonData.length());
    client.print("\r\n\r\n");
    client.print(jsonData);
    client.print("\r\n");
    delay(500); // Esperar respuesta del servidor
  }

  // Esperar a que los datos estén disponibles
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Tiempo de espera excedido !");
      delay(60000);
      return;
    }
  }

  // Leer respuesta del servidor e imprimirlo en el puerto serial
  Serial.println("Recibiendo desde servidor");
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }

  // Cerrar la conexión con el servidor
  Serial.println();
  Serial.println("Cerrando conexión");
  client.stop();

  delay(5000);  // Ejecutar cada 5 segundos
}
