#include <Servo.h>
#define PINO_IN1 2
#define PINO_IN2 3
#define PINO_IN3 4
#define PINO_IN4 5

#define PULSE_SEVO 15
#define PINO_BASE 6

/*#define PINO_ 7
#define PINO_BASE 8
#define PINO_BASE 9*/

Servo base;

int baseAngle = 90;

int comando;
int comandoArm = -1;

void setup() {
  //Serial Begin
  Serial.begin(9600);

  //Zera o Servo
  servoDefault();

  //Configura os pinos
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);

  base.attach(PINO_BASE);

}

void loop() {
  comando = Serial.read();
  if(comando != -1){
    Serial.println(comando);
    comandoArm = comando;
  }
  interpreter(comandoArm);
}

void interpreter(int comando){
  if(comando == 1){ //Frente
    
    digitalWrite(PINO_IN1, LOW); 
    digitalWrite(PINO_IN2, HIGH);
    digitalWrite(PINO_IN3, LOW);
    digitalWrite(PINO_IN4, HIGH);
    
  }
  if(comando == 2){ //Trás
    digitalWrite(PINO_IN1, HIGH); 
    digitalWrite(PINO_IN2, LOW);
    digitalWrite(PINO_IN3, HIGH);
    digitalWrite(PINO_IN4, LOW);
  }
  if(comando == 3){ //Esq
    digitalWrite(PINO_IN1, HIGH); 
    digitalWrite(PINO_IN2, LOW);
    digitalWrite(PINO_IN3, LOW);
    digitalWrite(PINO_IN4, HIGH);
  }
  if(comando == 4){ //Dir
    digitalWrite(PINO_IN1, LOW); 
    digitalWrite(PINO_IN2, HIGH);
    digitalWrite(PINO_IN3, HIGH);
    digitalWrite(PINO_IN4, LOW);
  }
  if(comando == 5 && (baseAngle+PULSE_SEVO) <= 180){ //Base Para esq
    baseAngle += PULSE_SEVO;
    base.write(baseAngle);
    Serial.println(baseAngle);
    comandoArm = -1;
  }
  if(comando == 6 && (baseAngle-PULSE_SEVO) >= 0){ //Base Para dir
    baseAngle -= PULSE_SEVO;
    base.write(baseAngle);
    Serial.println(baseAngle);
    comandoArm = -1;
  }
  if(comando == 0){ //Parar
    disableAll();
  }
}

void servoDefault(){
  base.write(baseAngle);
}

void disableAll(){
  //Para todos os motores
  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
}
