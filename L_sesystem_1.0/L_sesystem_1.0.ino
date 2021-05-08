#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <iostream>
#include <Servo.h>
#include <ArduinoJson.h> // Viktig å laste inn denne før du kjører koden. Gå til:
// Skisse -> Inkluder Bibliotek -> Administrer Bibliotek -> Søk: ArduinoJson og last inn den som er laget av:
// Benoit Blanchon
// Prøv å installer 5.7.1 versjon

using namespace std;

ESP8266WebServer server(80);

char* ssid = "Munkenettet";
char* password = "kongKrilliOgHansLand";
// const char* host = "10.0.0.12"; //ikke nødvendig

//Servo pinouts:
Servo servoOpen;
Servo servoClose;
const int servo_pin1 = 0; //Åpne servo
const int servo_pin2 = 0; //Låse servo

void setCrossOrigin() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Headers", "*");
  server.sendHeader("Access-Control-Max-Age", "600");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS,HEAD");
}

void setup() {
  // Connect to Wifi
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());

  // Bare test funksjon
  server.on("/", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Headers", "*");
    server.sendHeader("Access-Control-Max-Age", "600");
    server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS,HEAD");
    server.send(200, "text/plain", "Hei godgutten, Andyboy!\n Du e ein snill gutt!");
  });
  server.on("/open", HTTP_OPTIONS, sendCrossOriginHeader);
  server.on("/open", HTTP_POST, open);
  server.on("/test", HTTP_POST, test);
  server.on("/close", close);

  // server.on("/toggle", toggle);
  server.begin();

  //Servo start:
  servoOpen.attach(servo_pin1);
  servoClose.attach(servo_pin2);

}

// test funksjon
void test() {
  server.send(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}


//Funksjoner:
void open() {
  setCrossOrigin();
  // Henter ut koden som er sendt fra nettsiden
  String data = server.arg("plain");
  StaticJsonBuffer<200> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);
  String doorcode = jObject["doorcode"];

  String kode = "gullsmidige";
  if (doorcode == kode) {
    servoOpen.write(180);
    delay(2000);
    servoOpen.write(0);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Headers", "*");
    server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS,HEAD");
    server.send(204, "");
    //server.send(204); // Prøv kanskje dette
  }
  else{
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Headers", "*");
    server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS,HEAD");
    server.send(400, "");
    //server.send(400); // Prøv kanskje dette
  }
}

// Funksjon for å håndtere option request. Sender tilbake ok
void sendCrossOriginHeader(){
    setCrossOrigin();
    server.send(204);
}

void close() {
  servoClose.write(180);
  delay(2000);
  servoClose.write(0);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Headers", "*");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS,HEAD");
  server.send(200);
}
