#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

// TCS230 or TCS3200 pins wiring to Arduino

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

//RED DEL TEC
#define WIFI_SSID "Tec-IoT"
#define WIFI_PASSWORD "spotless.magnetic.bridge"

//RED MI CASA
// #define WIFI_SSID "GO_RAVENS"
// #define WIFI_PASSWORD "5177632456"
//Red Key
//Red Key
//IP de mi casa: 192.168.1.127
//IP del tec: 10.22.213.76
HTTPClient httpClient;
WiFiClient wClient;
String URL1 = "http://10.22.213.76:3000/iot/api/getColors/";
String URL2 = "http://10.22.213.76:3000/iot/api/insertColor/";
//String URL4 = "http://129.23.23.08/Pruebas_GP/?devID=";
String deviceID1 = "1/";

const int S0 = D3;  
const int S1 = D2;  
const int S2 = D4;  
const int S3 = D0;  
const int sensorOut = D5;
const int mot_v=D1;     

// test

// 130 close, red, further 100

// 350 close, blue, 130 further

// 170 close, green, 100 further

// Stores frequency read by the photodiodes

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() {
  Serial.begin(9600);
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  pinMode(mot_v,OUTPUT);

  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // Hacer la conexión a la red WiFi
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
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // redColor = map(redFrequency, 115, 120, 255,0);
  redColor = max(0,min((int)map(redFrequency, 100, 220, 255,0),255));
  // 63 close, red, further 220

  // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redColor);
  delay(100);
  

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // greenColor = map(greenFrequency, 100, 199, 255, 0);
  greenColor = max(0,min((int)map(greenFrequency, 140, 250, 255, 0),255));
  // 170 close, green, 100 further

  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenColor);
  //Serial.print(" G freq = ");
  //Serial.print(greenFrequency);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  

  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // blueColor = map(blueFrequency, 38, 84, 255, 0);
  blueColor = max(0,min((int)map(blueFrequency, 130, 350, 255, 0),255));
  // 350 close, blue, 130 further

  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.print(blueColor);
  delay(100);

  int diffRG = redColor - greenColor; 
  int diffRB = redColor - blueColor; 
  String color_detectado; 
  if (redColor > blueColor && greenColor > blueColor && diffRG <= 30 && diffRB >= 20) {
    color_detectado = "AMARILLO";
      Serial.println(" - YELLOW detected!");
      digitalWrite(mot_v, HIGH);
      delay(300);
      digitalWrite(mot_v, LOW);
      delay(300);
      
  }
  else if(redColor > greenColor && redColor > blueColor){
      Serial.println(" - RED detected!");
      color_detectado = "ROJO";
  }
  else if(greenColor > redColor && greenColor > blueColor){
    Serial.println(" - GREEN detected!");
    color_detectado = "VERDE";
  }
  else if(blueColor > redColor && blueColor > greenColor){
    color_detectado = "AZUL";
    Serial.println(" - BLUE detected!");
    digitalWrite(mot_v, HIGH);
    delay(300);
    digitalWrite(mot_v, LOW);
    delay(300);
  }
  else if (blueColor >= 240 && redColor >= 240 && greenColor >= 240) {
    color_detectado = "BLANCO";
    Serial.println(" - WHITE detected");
    digitalWrite(mot_v, HIGH);
    delay(300);
    digitalWrite(mot_v, LOW);
    delay(300);
  }

  if (blueColor <= 3 && redColor <= 3 && greenColor <= 3) {
    color_detectado = "NEGRO";
    Serial.println(" - BLACK detected");
  }

  logIntentoPOSinsert(deviceID1, redColor, greenColor, blueColor, color_detectado);
  Serial.println("");
  logIntentoGETselect(deviceID1);
  Serial.println("----------------------------------------------------------------------------------------------------------------");

  delay(3000);
  
}

// Metodo GET para obtener datos de la base de datos
void logIntentoGETselect(String deviceID){
    String data = URL1;
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
void logIntentoPOSinsert(String deviceID, int r, int g, int b, String color){
    String data = URL2;
    String payload = "{\"r\": \"" + String(r) + "\", \"g\": \"" + String(g) + "\", \"b\": \"" + String(b) + "\", \"color\": \"" + color + "\"}";
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
