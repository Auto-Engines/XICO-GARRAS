#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#define RXPIN 3
#define TXPIN 1


ESP8266WebServer server;
SoftwareSerial s(RXPIN, TXPIN);

char* ssid = "VIVO-B949";
char* password = "h62e7a89";

void setup() {
  //Inicia o Serial
  s.begin(9600);

  //Configura a rede
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    s.print(".");
    delay(500);
  }
  s.println("");
  s.print("IP Address: ");
  s.println(WiFi.localIP());

  server.on("/",[](){server.send(200,"text/plain","Hello World!");});
  server.on("/controller", controller);
  server.begin();
  
}

void loop() {
  server.handleClient();
}

void controller(){
  String data = server.arg("plain");
  StaticJsonBuffer<200> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);
  int comando = jObject["command"]; //Comando id
  if(comando != -1){
    server.send(200,"text/plain","OC");
    //Manda pro arduino
    s.write(comando);
  }
}
