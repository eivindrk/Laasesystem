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
    server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS,HEAD");
    server.send(200, "text/plain", "Hei godgutten, Andyboy!\n Du e ein snill gutt!");
  });

  server.on("/close", close);
  server.on("/open", open);

  // server.on("/toggle", toggle);
  server.begin();

  //Servo start:
  servoOpen.attach(servo_pin1);
  servoClose.attach(servo_pin2);

}


void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}


//Funksjoner:
void open() {

  // Henter ut koden som er sendt fra nettsiden
  String data = server.arg("plain");
  StaticJsonBuffer<200> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);
  String doorcode = jObject["doorcode"];

  String kode = "gullsmidige";
  servoOpen.write(180);
  delay(2000);
  servoOpen.write(0);
  if (doorcode == kode) {
    servoOpen.write(180);
    delay(2000);
    servoOpen.write(0);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Headers", "*");
    server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS,HEAD");
    server.send(204, "");
  }
  else{
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Headers", "*");
    server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS,HEAD");
    server.send(400, "");
  }

//YOYOYOYOYYOYOYOYO
  

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
