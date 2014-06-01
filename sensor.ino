#include <Servo.h>

int trig = 6;
int echo = 7;
int pinSrv = 9;
Servo srv;

//
int lastStade = LOW; 

//Manejo de tiempo
unsigned long tp = 0;
unsigned long tpHC = 0;

void setup() {
  Serial.begin(9600);
  srv.attach(pinSrv,520,2420);
  pinMode(trig,OUTPUT);
}

void loop() {
  unsigned long tc = micros();
  if( tc-tp >= 5000)
    srv.write(180);
    
  if( tc-tp >= 10000){
    srv.write(1);
    digitalWrite(trig,HIGH);
    tp=tc;
  }
  
  if(tc-tp >= 100)
    digitalWrite(trig,LOW);
  
  int currentStade = digitalRead(echo);
  if(currentStade != lastStade && currentStade == HIGH)
    tpHC = tc;
  if(currentStade != lastStade && currentStade == LOW){
    unsigned long tHC= tc-tpHC;
    Serial.println(map(tHC,0,850,0,15));  
}
  
    
  lastStade = currentStade;
}
