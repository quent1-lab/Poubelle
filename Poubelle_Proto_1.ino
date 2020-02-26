#include <Wire.h>
#include <Servo.h>
//#include "simpleMinuteur.h"
#include "rgb_lcd.h"

rgb_lcd lcd;

Servo trappe1;
Servo trappe2;

// Définition des adresses logiques des esclaves I2C.
#define I2C_SLAVE_LCD_ADDRESS  2
#define I2C_SLAVE_ENGINE_ADDRESS  1


int pos1 = 0, pos2 = 0, pos3 = 0;

int chronoAuto = 0;
int recu = 100;
int incomingByte = 0;
bool Auto = true;

//LED de couleur
int rouge = 8;
int jaune = 9;
int vert = 10;
int bleu = 11;
int blanc = 12;

//Entrée Bouton
int b1 = 2;
int b2 = 3;
int b3 = 4;
int b4 = 5;

//Valeur
int ultraValeur = 0;
int cm = 0;
byte x = 0;

/*simpleMinuteur minuteurA(2000);
simpleMinuteur minuteurB(2000);
simpleMinuteur minuteurC(2000);
simpleMinuteur minuteurD(2000);
simpleMinuteur minuteurE(2000);*/


void setup()
{
  Wire.begin();

  //Initialisation LED
  pinMode(rouge, OUTPUT);
  pinMode(jaune, OUTPUT);
  pinMode(vert, OUTPUT);
  pinMode(bleu, OUTPUT);
  pinMode(blanc, OUTPUT);

  //Initialisation Boutons
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);

  //Initialisation Ultrasons
  pinMode(A0, INPUT);

  trappe1.attach(2);
  trappe2.attach(3);

  Serial.begin(9600);
}

void loop()
{ 
  
   cm = 0.01723 * readUltrasonicDistance(7, 7);

  Serial.print(cm);
  Serial.println("cm");
  delay(10);

  if (digitalRead(b1) == HIGH) {
    x = 11;
    digitalWrite(rouge , HIGH);
  }

  if (digitalRead(b2) == HIGH) {
    x = 12;
    digitalWrite(jaune , HIGH);
  }

  if (digitalRead(b3) == HIGH) {
    x = 13;
    digitalWrite(vert , HIGH);
  }

  if (digitalRead(b4) == HIGH) {
    x = 14;
    digitalWrite(bleu , HIGH);
  }

  readRegisterAndSendValue(x , I2C_SLAVE_LCD_ADDRESS);
  readRegisterAndSendValue(x , I2C_SLAVE_ENGINE_ADDRESS);

}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void readRegisterAndSendValue(byte previousValue, int slaveAddress) {

  Wire.beginTransmission(slaveAddress);
  Wire.write(previousValue);
  Serial.println(previousValue);
  Wire.endTransmission();

}

void Read() {
  if (Serial.available() > 0) { //vérification d'une donnée de l'hôte
    incomingByte = Serial.read();//enregistrement de la donnée de l'hôte
    recu = incomingByte;
    chronoAuto = 0;// mise a 0 du chrono de changement d'état Auto tant que l'hôte est connecté
  }
}

void Scan() {
}
