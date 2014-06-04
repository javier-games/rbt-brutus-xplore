#include <SoftwareSerial.h>
//Constantes
const int motor1input1 = 6; const int motor1input2 = 4; const int motor2input1 = 2; const int motor2input2 = 3; const int enable1 = 7; const int enable2 = 13; const int bluetoothTx = 8; const int bluetoothRx = 5;
//Variables
char control='n'; boolean m1i1=LOW; boolean m1i2=LOW; boolean m2i1=LOW; boolean m2i2=LOW; boolean en1=LOW; boolean en2=LOW;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
void setup(){ Serial.begin(9600);
pinMode(motor1input1,OUTPUT); pinMode(motor1input2,OUTPUT); pinMode(motor2input1,OUTPUT); pinMode(motor2input2,OUTPUT); pinMode(enable1,OUTPUT); pinMode(enable2,OUTPUT); digitalWrite(enable1,en1); //en1 estado digitalWrite(enable2,en2);
//bluetooth.begin(115200); bluetooth.print("$"); bluetooth.print("$"); bluetooth.print("$"); delay(100); bluetooth.println("U,9600,N"); 
bluetooth.begin(9600);
}
void loop(){
if(bluetooth.available()){ control=bluetooth.read();
Serial.println(control); }
if(Serial.available()){ bluetooth.print((char)Serial.read());
}
digitalWrite(enable1,en1); digitalWrite(enable2,en2); digitalWrite(motor1input1,m1i1); digitalWrite(motor1input2,m1i2); digitalWrite(motor2input1,m2i1); digitalWrite(motor2input2,m2i2);
if(control!='N') {
en1=HIGH;
en2=HIGH; }
if(control=='N') {
en1=LOW;
en2=LOW; }
if(control=='R')
    {
      m1i1=HIGH;
      m1i2=LOW;
      m2i1=LOW;
      m2i2=LOW;
}
//Giro a la izquierda
if(control=='L') {
      m1i1=LOW;
      m1i2=LOW;
      m2i1=HIGH;
      m2i2=LOW;
}
//De frente
if(control=='F') {
      m1i1=HIGH;
      m1i2=LOW;
      m2i1=HIGH;
      m2i2=LOW;
}
//Reversa Derecha
if(control=='r') {
      m1i1=LOW;
      m1i2=HIGH;
      m2i1=LOW;
      m2i2=LOW;
}
//Reversa Izquierda
if(control=='l') {
      m1i1=LOW;
      m1i2=LOW;
      m2i1=LOW;
      m2i2=HIGH;
} //Reversa
if(control=='B') {
      m1i1=LOW;
      m1i2=HIGH;
      m2i1=LOW;
      m2i2=HIGH;
} }
