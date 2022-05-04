#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#define PINO_IN1 5
#define PINO_IN2 4
#define PINO_IN3 14
#define PINO_IN4 12

ESP8266WebServer server;
//uint8_t pin_led = 2;
char* ssid = "Auto-Engines-Wifi";
char* password = "h62e7a89";
String comandoArm = "";

void setup() {
  //Configura os pinos
  //pinMode(pin_led, OUTPUT);

  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);

  //Desativa os motores
  disableAll();

  //Mostrar que a placa ta ligada
  //digitalWrite(pin_led,HIGH);

  //Configura a rede
  WiFi.begin(ssid,password);
  Serial.begin(9600);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

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
  String comando = jObject["command"];
  if(comando != ""){
    server.send(200,"text/plain","OC");
    comandoArm = comando;
  }
  interpreter(comandoArm);
  
}

void interpreter(String comando){
  Serial.println(comando);
  int pulse_time = 50; //ms
  
  if(comando == "w"){
    digitalWrite(PINO_IN1, LOW); 
    digitalWrite(PINO_IN2, HIGH);
    digitalWrite(PINO_IN3, LOW);
    digitalWrite(PINO_IN4, HIGH);
    
  }
  if(comando == "s"){
    digitalWrite(PINO_IN1, HIGH); 
    digitalWrite(PINO_IN2, LOW);
    digitalWrite(PINO_IN3, HIGH);
    digitalWrite(PINO_IN4, LOW);
  }
  if(comando == "a"){
    digitalWrite(PINO_IN1, HIGH); 
    digitalWrite(PINO_IN2, LOW);
    digitalWrite(PINO_IN3, LOW);
    digitalWrite(PINO_IN4, HIGH);
  }
  if(comando == "d"){
    digitalWrite(PINO_IN1, LOW); 
    digitalWrite(PINO_IN2, HIGH);
    digitalWrite(PINO_IN3, HIGH);
    digitalWrite(PINO_IN4, LOW);
  }
  if(comando == "space"){
    disableAll();
  }
}

void disableAll(){
  //Para todos os motores
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
}
