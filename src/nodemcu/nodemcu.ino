#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h> // https://github.com/adafruit/DHT-sensor-library

// Sensor de distancia Ultrasónico HC-SR04.
#define Trig 13 // "Trig" 
#define Echo 15 // "Echo"

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
float voltage = 0;

void setup() {
pinMode( Trig, OUTPUT); // Configuracion
pinMode( Echo, INPUT);
digitalWrite(Trig, LOW); // Inicializar

// Indicadores
Serial.begin(9600); // Puerto
dht.begin();
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
String msg_str = "Hello World";
int lecturaSensorA0 = analogRead(A0); // **** Sensor analogico
float voltage = lecturaSensorA0 * (3.3 / 1023.0); //escalamos a voltaje msg_str = "The resistance value is: ";

//Enviamos por el puerto serie
if(voltage <= 1){
delay(2000);
Serial.print(" LED ON");
digitalWrite(Lamp1, HIGH);
}
else{
delay(2000);
Serial.print(" LED OFF");
digitalWrite(Lamp1, LOW);
}
Serial.print(" ADC= ");
Serial.print(lecturaSensorA0);
Serial.print(" Voltaje= ");
Serial.println(voltage);
delay(2000);
// Esperar 3 segundos
h = dht.readHumidity(); // Leer la humedad relativa
tmp = dht.readTemperature(); // Leer teperatura en grados centígrados
(dht.readTemperature(true) en grados Fahrenheit)
// Comprobamos si ha habido algún error en la lectura
if (isnan(h) || isnan(tmp) ) {
Serial.println("Error obteniendo los datos del sensor DHT11");
//return;
}
msg_str = "The Temperature value is: "; // Construye mensaje (manejado como STRING).
Serial.println(msg_str);
Serial.println(tmp);//msg_str= msg_str + tmp;
//msg_str.toCharArray(msg_chr, 58); // Copies the msg’s characters to the supplied
buffer(message): STRING -> Char Array.
// Muestra mensaje localmente.
if ( isnan(tmp) == 0){
logIntentoGETselect(deviceID1);
// delay(2000);
// Usamos metodo POST para insertar en la base de datos
logIntentoPOSinsert(deviceID1, tmp);
}
delay(30000);
msg_str = "The humidity value is: "; // Construye mensaje (manejado como STRING).
Serial.println(msg_str);
Serial.println(h);
//msg_str= msg_str + h;
// msg_str.toCharArray(msg_chr, 58); // Copies the msg’s characters to the supplied
buffer(message): STRING -> Char Array.
// Muestra mensaje localmente.
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


