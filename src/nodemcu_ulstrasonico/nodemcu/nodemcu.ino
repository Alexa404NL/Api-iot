#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h> // https://github.com/adafruit/DHT-sensor-library

#define D0 16   // Arriba derecha 1
#define D1 5    // Arriba derecha 2
#define D2 4    // Arriba derecha 3
#define D3 0    // Arriba derecha 4
#define D4 2    // Arriba derecha 5

// Posiciones 6 3V3, 7 GND
#define D5 14   // Arriba derecha 8
#define D6 12   // Arriba derecha 9
#define D7 13   // Arriba derecha 10
#define D8 15   // Arriba derecha 11
#define SD3 10  // Arriba izquierda 4
#define SD2  9  // Arriba izquierda 5

// #define WIFI_SSID "GO_RAVENS"
// #define WIFI_PASSWORD "5177632456"

#define WIFI_SSID "Tec-IoT"
#define WIFI_PASSWORD "spotless.magnetic.bridge"

//IP de mi casa: 192.168.1.127
//IP del tec: 10.22.213.76

//Red Key
    HTTPClient httpClient;
    WiFiClient wClient;
    String URL1 = "http://10.22.213.76:3000/iot/api/getDistance/"; //use GET for SELECT QUERY
    String URL2 = "http://10.22.213.76:3000/iot/api/insertDistance/";
    //String URL4 = "http://129.23.23.08/Pruebas_GP/?devID=";
    String deviceID1 = "1/";
//long tiempoAnterior = 0; // Hora del reporte anterior.
//char msg_G[50]; // Variable para Cadena(string).
    int lecturaSensorA0 = 0; // Lectura sensor analogico
    int umbral_A0 = 500; // Criterio para enviar un mensaje al "broker", Sensor analogico
    int umbral_D = 40;
    float voltage = 0;
    int trigPin = D5;  //Conectado a D5,   int trigPin = 
    int echoPin = D6;  //Conectado a D6,   int echoPin = 
    const int buzzer=D8;
    float v = 331.5+0.6*20;   // m/s


float medirDistanciaCm() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);

    //listen for echo
    long duracion = pulseIn(echoPin, HIGH);
    long distanciaCM = duracion * 0.034 / 2;
    return distanciaCM;
}


void setup() {

  Serial.begin(9600); // Puerto
  pinMode(LED_BUILTIN, OUTPUT);
  // ----- Inicializacion sensor de distancia
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.println("Iniciando Sensor Distancia");

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando a red WiFi \"");
    Serial.print(WIFI_SSID);
    Serial.print("\"");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.print("\nConectado! IP: ");
    Serial.println(WiFi.localIP());
    delay(500);
  }


  void loop() {
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(1000); // Wait for 1000 millisecond(s)
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(1000); // Wait for 1000 millisecond(s)

    float distancia=medirDistanciaCm();
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println("cm");

    if (distancia<18){
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    }
    logIntentoPOSinsert(deviceID1, distancia);
    Serial.println("");
    logIntentoGETselect(deviceID1);
    Serial.println("----------------------------------------------------------------------------------------------------------------");

    delay(5000);
  }

  // Metodo GET para consultar la base de datos
  void logIntentoGETselect(String deviceID){
    //if(WiFi.status() == WL_CONNECTED){
    String data = URL1;

    //data = http://192.168.1.12:3000/IoT/api/getLogs/1/
    Serial.println(data);
    if(WiFi.status() == WL_CONNECTED){
    httpClient.begin(wClient, data.c_str());
    int httpResponseCode = httpClient.GET();
    Serial.println(httpResponseCode);
    if (httpResponseCode>0) {
    Serial.println(httpClient.getString());
    }
    httpClient.end();
    }
    return;
  }

  // Metodo POST para insertar en la base de datos
void logIntentoPOSinsert(String deviceID, float distancia){
    String data = URL2;
    // String id = "123";  // ID de ejemplo
    // String fecha = "2024-04-15 17:20:13";  // Fecha de ejemplo
    String payload = "{\"valor\": \"" + String(distancia) + "\"}";

    Serial.println(data); 

    if(WiFi.status() == WL_CONNECTED){
        httpClient.begin(wClient, data.c_str());
        httpClient.addHeader("Content-Type", "application/json");
        int httpResponseCode = httpClient.POST(payload);  // Envía el payload como JSON
        Serial.println(httpResponseCode);

        if (httpResponseCode > 0) {
            String response = httpClient.getString();
            Serial.println(response);
        } else {
            Serial.println(httpResponseCode);
        }
        httpClient.end();
    }
}
