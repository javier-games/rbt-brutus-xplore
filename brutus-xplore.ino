#include <Servo.h>
#include <SoftwareSerial.h>

//Constantes
int rxPin    = 11;
int txPin    = 5;
int trig     = 6;
int echo     = 7;
int srvPin   = 8;
int sr04Pin  = 9;
int motorR  = 10;
int enableL = 3;
int motorL  = 12;
int ldr     = A1;

SoftwareSerial hc06(rxPin,txPin);

Servo srv;
  float srv_pos = 92;
Servo sr04;
  float sr04_pos = 90;

//Controles rapidos (MTR DC)
int ON = HIGH; //habilitado
int OFF = LOW; //deshabilitado
int FNT = LOW; //enfrente
int BCK = HIGH; //atras

//Manejo de tiempo
unsigned long ct; //tiempo presente
unsigned long pt_sr04 = 0;
  float sr04_180 = 700000; //tiempo en dar 180º [us]
  float sr04_samp = 180; //180/XX 
  int sr04_sen = 1;
unsigned long pt_trig = 0;
  float trig_time = 72; // time = sr04_180/trig_time
unsigned long pt_echo = 0;
  int lastStade = LOW;
unsigned long sr04_time = 0;
int sr04_dist = 0;
unsigned long dly = 150000;
unsigned long pt = 0;

char control = 'n';

void setup(){
  
  Serial.begin(9600);
  hc06.begin(9600);
  srv.attach(srvPin,700,2160);
  sr04.attach(sr04Pin,520,2420);
  
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(motorR,OUTPUT);
  pinMode(motorL,OUTPUT);
  pinMode(enableL,OUTPUT);
  
  //Condiciones Iniciales
  srv.write(srv_pos);
  sr04.write(sr04_pos);
  digitalWrite(trig,LOW);
  digitalWrite(motorR,FNT);
  digitalWrite(motorL,FNT);
  digitalWrite(enableL,OFF);
 
  
  delay(3000);
}

void loop(){
  
  ct = micros();
  
  if( ct-pt_trig >= sr04_180/trig_time){
    digitalWrite(trig,LOW);
    if( ct-pt_sr04 >= sr04_180/sr04_samp){
      if(sr04_pos >= 180)
        sr04_sen = -1;
      if(sr04_pos <= 0)
        sr04_sen = 1;
    
      sr04.write(sr04_pos+=(sr04_sen*180/sr04_samp));
      digitalWrite(trig,HIGH);
      pt_sr04 = ct;
    }
  }
  
  int currentStade = digitalRead(echo);
  if(currentStade != lastStade && currentStade == HIGH)
    pt_echo = ct;
  if(currentStade != lastStade && currentStade == LOW){
    sr04_time = ct-pt_echo;
    sr04_dist = map(sr04_time,0,850,0,15);
    
  }
  lastStade = currentStade;

  if( ct-pt >= dly ){
    
    hc06.print(char(sr04_pos));
    hc06.print(" ");
    if(sr04_dist<=200)
      hc06.print(char(sr04_dist));
    else
      hc06.print(char(200));
    hc06.print(" ");
    hc06.println(char(analogRead(ldr)));
    
    if(hc06.available()){
      control=hc06.read();
      Serial.println(control);
    }
    
    
      if( control == '6' || control == '7' || control == '8'){
        digitalWrite(motorR,FNT);
        digitalWrite(motorL,FNT);
        digitalWrite(enableL,ON);
      }
      else if( control == '0' || control == '1' || control == '2'){
        digitalWrite(motorR,BCK);
        digitalWrite(motorL,BCK);
        digitalWrite(enableL,ON);
      }
      else
        digitalWrite(enableL,OFF);
      
      if( control == '6' || control == '3' || control == '0')
        srv.write(srv_pos-20);
      else if( control == '8' || control == '5' || control == '2')
        srv.write(srv_pos+20);
      else
        srv.write(srv_pos);
    
    pt = ct;
  }
  
}
