#include <Servo.h>
#define PINO_EXT 3
#define PINO_ALT 5
#define PINO_GARRA 6

#define PULSE_SERVO 2

Servo altura;
Servo extencao;
Servo garra;

int altAngle = 60;
int extAngle = 90;
int garraAngle = 110;

int comando;

void setup() {
  //Serial Begin
  Serial.begin(9600);


  //Attach
  extencao.attach(PINO_EXT);
  altura.attach(PINO_ALT);
  garra.attach(PINO_GARRA);

  //Zera o Servo
  servoDefault();

}

void loop() {
  comando = Serial.read();
  interpreter(comando);
  
}

void interpreter(int comando){
  //Serial.println(comando);
  if(comando == 1 && (extAngle+PULSE_SERVO) <= 180){ //Extencao +
    extAngle += PULSE_SERVO;
    extencao.write(extAngle);
    Serial.println(extAngle);
  }
  if(comando == 2 && (extAngle-PULSE_SERVO) >= 90){ //Extencao -
    extAngle -= PULSE_SERVO;
    extencao.write(extAngle);
    Serial.println(extAngle);
  }

  if(comando == 3 && (altAngle+PULSE_SERVO) <= 74){ //Alt +
    altAngle += PULSE_SERVO;
    altura.write(altAngle);
    Serial.println(altAngle);
  }
  if(comando == 4 && (altAngle-PULSE_SERVO) >= 0){ //Alt -
    altAngle -= PULSE_SERVO;
    altura.write(altAngle);
    Serial.println(altAngle);
  }

  if(comando == 5){ //Garra +
    garraAngle = 110;
    garra.write(garraAngle);
    Serial.println(garraAngle);
  }
  if(comando == 6){ //Garra -
    garraAngle = 0;
    garra.write(garraAngle);
    Serial.println(garraAngle);
  }
  if(comando == 0){ //Parar
    servoDefault();
  }
}

void servoDefault(){
  extencao.write(extAngle);
  altura.write(altAngle);
  garra.write(garraAngle);
}
