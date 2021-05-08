#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <iostream>
#include <Servo.h>

using namespace std;

ESP8266WebServer server(80);

char* ssid = "Munkenettet";
char* password = "kongKrilliOgHansLand";
// const char* host = "10.0.0.12"; //Usikker på denne, prøv uten først

//Servo pinouts:
Servo servoOpen;
Servo servoClose;
const int servo_pin1 = 1; //Åpne servo
const int servo_pin2 = 0; //Låse servo

void setup() {
  //Wifi setup
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());

  server.on("/",[](){server.send(200,"text/plain", "Hello");});
  // server.on("/toggle", toggle);
  server.begin();

  //Servo start:
  servoOpen.attach(servo_pin1);
  servoClose.attach(servo_pin2);
}

void toggle() {
  // do something
  server.send(204, "");
}

void loop() {
  // put your main code here, to run repeatedly:
  //server.handleClient();
  
  close();
}


//Funksjoner:
void open(string kodeIn) {
  string kode = "gullsmidige";
  if (kodeIn == kode){
    servoOpen.write(180);
    delay(2000);
  }
}

void close(){
  int pos;
  servoClose.write(180);
  delay(2000);
  servoClose.write(0);
  delay(5000);
}
