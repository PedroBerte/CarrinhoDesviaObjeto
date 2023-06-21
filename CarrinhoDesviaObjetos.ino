#include <HCSR04.h>

#define pinMot1A 5
#define pinMot1B 6
#define pinMot2A 9
#define pinMot2B 10

#define buzzer 7

#define TRIG_PIN 12
#define ECHO_PIN 13

#define velocidade 100

HCSR04 hc(TRIG_PIN, ECHO_PIN);

  int dist = 0;

void setup() {
  Serial.begin(9600);

  pinMode(pinMot1A, OUTPUT);
  pinMode(pinMot1B, OUTPUT);
  pinMode(pinMot2A, OUTPUT);
  pinMode(pinMot2B, OUTPUT);
  
  pinMode(buzzer, OUTPUT);

  pinMode(3, OUTPUT);
  analogWrite(3, velocidade);
}

void loop() {
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);

  dist = hc.dist();

  Serial.println(dist);

  do{
    analogWrite(pinMot1A, velocidade);
    analogWrite(pinMot2A, velocidade);
    dist = hc.dist();
    delay(60);
  } while(dist < 30);
  if(dist < 30){
    desaceleraCarrinho();
  }
  delay(60);
}

void desaceleraCarrinho(){
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);

  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);

  dist = hc.dist();

  while(dist < 10){
    analogWrite(pinMot1A, velocidade - (dist * 2));
    analogWrite(pinMot2A, velocidade - (dist * 2));
    dist = hc.dist();
    delay(60);
  }
  delay(60);
  return;
}