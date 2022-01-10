#include <HX711.h>

#include <Servo.h>
#include "HX711.h"
const int LOADCELL_DOUT_PIN = 10;
const int LOADCELL_SCK_PIN = 9;
float      distance;
const int  echo=A2;                          //ultrasonic echo pin
const int  trig=A3;                          // ultrasonic trig pin
// HX711 circuit wiring
Servo myservo;  
HX711 scale;

int pos=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(11);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // HX711 PIN
  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  pinMode(echo,INPUT);                       //  ultrasoic setting
  pinMode(trig,OUTPUT);                      //
}

void loop() {
  // put your main code here, to run repeatedly:
//  myservo.write(0);
//  for(pos = 0; pos < 180; pos += 1)  
//  {                                                    
//    myservo.write(pos);        
//    delay(15);                     
//  }
//  for(pos = 180; pos>=1; pos-=1)     
//  {                                
//    myservo.write(pos);         
//    delay(15);                       
//  } 
  myservo.write(0);
  double distance, weight;
  digitalWrite(trig,LOW);
  delayMicroseconds(20); 
  digitalWrite(trig,HIGH);
  delayMicroseconds(20);
  digitalWrite(trig,LOW);                     
  distance  = pulseIn(echo,HIGH);             
  distance  = distance*340/2/10000; 
  if(distance>150)distance=0; 
  weight=scale.get_units();
  if(abs(weight<5))weight=0;
  else weight*=15.4;
  Serial.print("weight reading: ");
  Serial.print(weight);         
  Serial.print("g\ndistance: ");
  Serial.print(distance);
  Serial.println("cm\n");
  scale.power_down();              // put the ADC in sleep mode
  delay(1000);
  scale.power_up();
}

