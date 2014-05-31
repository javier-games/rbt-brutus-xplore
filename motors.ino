
#include <Servo.h>

Servo servoX;
int motor1  = 10;
int motor2  = 11;
int enable1 = 13;
int enable2 = 12;
int pinSRV2 = 8;

void setup() {
  servoX.attach(pinSRV2,420,2400);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(enable1,OUTPUT);
  pinMode(enable2,OUTPUT);
}


void loop() {
  digitalWrite(enable1,HIGH);
  digitalWrite(enable2,HIGH);
  
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,LOW);
  servoX.write(90);
  delay(10000);
  
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,LOW);
  servoX.write(107);
  delay(100);
  
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,HIGH);
  delay(3000);
  
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,HIGH);
  servoX.write(73);
  delay(100);
  
  digitalWrite(enable1,HIGH);
  digitalWrite(enable2,HIGH);
  servoX.write(90);
  
  delay(3000);
  
    
  digitalWrite(enable1,LOW);
  digitalWrite(enable2,LOW);
  servoX.write(90);
  
  delay(3000);
}

/*
void loop() {
  for(pos = 73; pos < 107; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servoX.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 

  for(pos = 107  ; pos >= 73; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servoX.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 

}

void loop() {                           // in steps of 1 degree 
     servoX.write(90);     // tell servo to go to position in variable 'pos' 
    delay(15);  
}*/
