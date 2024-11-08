#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

// Sensor de distancia Ultrasónico HC-SR04.
#define TRIG_PIN D5 // "Trig" 
#define ECHO_PIN D6 // "Echo"

#define WIFI_SSID "Tec-IoT"
#define WIFI_PASSWORD "spotless.magnetic.bridge"
//Red Key

HTTPClient httpClient;
WiFiClient wClient;

String URL1 = "http://192.168.1.12:3000/api/getLogs/"; //use GET for SELECT QUERY
String URL2 = "http://192.168.1.12:3000/api/logTemp/";
String URL4 = "http://129.23.23.08/Pruebas_GP/?devID=";
String deviceID1 = "1/";
//long tiempoAnterior = 0; // Hora del reporte anterior.
//char msg_G[50]; // Variable para Cadena(string).

int lecturaSensorA0 = 0; // Lectura sensor analogico
int umbral_A0 = 500; // Criterio para enviar un mensaje al "broker", Sensor analogico
int umbral_D = 40;

void setup() {
pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
digitalWrite(TRIG_PIN, LOW); // Inicializar

// Indicadores
Serial.begin(9600); // Puerto

WiFi.mode(WIFI_STA);
WiFi.disconnect();
delay(100);

WiFi.begin(ssid, password);
Serial.print("Conectando a red WiFi \"");
Serial.print(ssid);
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
long t, d;
float h;
float tmp;
long distancia = distanciaUltrasonico(Trig, Echo);
Serial.print("Distancia:");
Serial.print(distanciaIzquierdo);
Serial.println(" cm");
delay(1000);
}

// Metodo GET para consultar la base de datos
void logIntentoGETselect(String deviceID){
//if(WiFi.status() == WL_CONNECTED){
String data = URL1;
data = data + deviceID;
/data = http://192.168.1.12:3000/api/getLogs/1/
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
void logIntentoPOSinsert(String deviceID, float tmp){
//if(WiFi.status() == WL_CONNECTED){
String data = URL2;
data = data + deviceID;
data = data + tmp;
//data = http://192.168.1.12:3000/api/logTemp/1/20
Serial.println(data);
/*URL4 = http://129.23.23.08/Pruebas_GP/?devID=
String data4 = URL4;
data4 = data4 + deviceID + "&temperature=" + tmp;
Serial.println(data4);*/
if(WiFi.status() == WL_CONNECTED){
httpClient.begin(wClient, data.c_str());
httpClient.addHeader("Content-Type", "Content-Type: application/json");
int httpResponseCode = httpClient.POST(data.c_str());
Serial.println(httpResponseCode);
//if (httpResponseCode>0) {
Serial.println(httpClient.getString());
//}
httpClient.end();
}
return;
}

long distanciaUltrasonico(int Trig, int Echo) {
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);

    long duracion = pulseIn(Echo, HIGH);
    long distancia = duracion * 0.034 / 2;
    return distancia;
}


