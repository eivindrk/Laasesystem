#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;

char* ssid = "Munkenettet";
char* password = "kongKrilliOgHansLand";


void setup() {
  // put your setup code here, to run once:
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
}

void toggle() {
  // do something
  server.send(204, "");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
