#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN 14     // Pin donde está conectado el sensor
#define DHTTYPE DHT22 // AM2302 es lo mismo que DHT22

const char* ssid = "Maestros";           // Nombre de la red WiFi
const char* password = "Maestros_2021";  // Contraseña del WiFi
const char* server = "10.0.20.150";       // Dirección IP del servidor
const int port = 80;                     // Puerto del servidor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Conectar al WiFi con tiempo de espera (timeout)
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    attempts++;
    Serial.println("Conectando al WiFi...");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conectado al WiFi");
  } else {
    Serial.println("Error: No se pudo conectar al WiFi. Reiniciando...");
    ESP.restart(); // Reiniciar si no logra conectar
  }

  dht.begin();  // Iniciar sensor
}

void loop() {
  delay(2000);
  
  fl0oat h = dht.readHumidity();    // Leer humedad
  float t = dht.readTemperature(); // Leer temperatura

  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer el sensor!");
    return;
  }

  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" °C");

  if (WiFi.status() == WL_CONNECTED) {  // Solo si está conectado al WiFi
    WiFiClient client;
    HTTPClient http;

    // Construir la URL completa con la IP y el puerto del servidor
    String url = "http://"+String(server)+"/panel_regador/backend/datos_recepcion.php?temperatura="+String(t)+"&humedad="+String(h);

    // Iniciar la solicitud HTTP
    http.begin(client, url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Establecer un timeout para la solicitud HTTP
    http.setTimeout(5000); // Timeout de 5 segundos
     // Ejecuta la petición GET
    int httpCode = http.GET();
    // Verifica la respuesta del servidor
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Respuesta del servidor:");
      Serial.println(payload);
    } else {
      Serial.print("Error en la petición HTTP: ");
      Serial.println(httpCode);
    }
    // Preparar los datos que se enviarán
    // String postData = "temperatura=" + String(t) + "&humedad=" + String(h);

    // // Enviar la solicitud POST
    // int httpResponseCode = http.POST(postData);

    // if (httpResponseCode > 0) {
    //   String response = http.getString();  // Obtener la respuesta del servidor
    //   Serial.println(httpResponseCode);    // Código de respuesta HTTP
    //   Serial.println(response);            // Respuesta del servidor
    // } else {
    //   Serial.print("Error en la solicitud: ");
    //   Serial.println(httpResponseCode);
    // }

    http.end();  // Terminar la conexión HTTP
  } else {
    Serial.println("Error de conexión WiFi");
  }
}

