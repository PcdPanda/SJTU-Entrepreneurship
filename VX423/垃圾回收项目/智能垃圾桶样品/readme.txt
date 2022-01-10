prototpye��arduino mega2560��Ϊ������,ƽʱ�����ó�籦���ߵ��Թ��磬��Ҫ�����ݵĻ�ֱ�����ӵ��Դ�arduino���ڼ��������ɣ�
�����������õ���9600
һ������2�����������ֱ�Ϊ�����ĳ��������HC-SR04�͵ײ��ĵ���ʽ���ش��������HX711оƬ
������һ��4���ӿڣ�gnd��vcc���磬Echo��trig����ͨ�ţ����߷�ʽ��Ӧ����
HX711һ��4���ӿڣ�gnd��vcc���磬Dout��SCK����ͨ�ţ����߷�ʽ��Ӧ����
���⻹����һ�����RDS3218�������¿��أ�����Ҫ�����Դ���磬ֱ�Ӷ�Ӧ����ӵ�arduino���ϼ���

���Ҫ���ĳ���Ļ�����Ҫ��arduino���а���HX711.H github�����л�����auduino����Ŀ-���ؿ������


#include <Servo.h>  //ͷ�ļ�
#include "HX711.h"	//HX711��
const int LOADCELL_DOUT_PIN = 10;	//HX711dout�ڽӵ�arduino10���źſ�
const int LOADCELL_SCK_PIN = 9;	//HX711sck�ڽӵ�arduino9���źſ�
float      distance;
const int  echo=A2;                          //������echo�ڽ�arduinoA2�źſ�
const int  trig=A3;                          // ������trig�ڽ�arduinoA3�źſ�
// HX711 circuit wiring
Servo myservo;	//�����ŷ����
HX711 scale;	//������ش�����

int pos=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);		//������ʱ���ڼ������Ĳ�����
  myservo.attach(11);		//�����arduino11�ſڣ���ɫ�߽�GND
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // ����HX711
  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // ��ʼ�����ش�����

  pinMode(echo,INPUT);                       //  ���ó�����ģʽ
  pinMode(trig,OUTPUT);                      //
}

void loop() {
  // put your main code here, to run repeatedly:	//��α���ע���ˣ��ǿ��Կ��ƶ��λ��0-180
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
  myservo.write(0);		//�����λ�����õ�0��
  double distance, weight;
  digitalWrite(trig,LOW);
  delayMicroseconds(20); 
  digitalWrite(trig,HIGH);
  delayMicroseconds(20);
  digitalWrite(trig,LOW);                     
  distance  = pulseIn(echo,HIGH);	   
  distance  = distance*340/2/10000; 
  if(distance>150)distance=0;	//����8���ǳ�����������    
  weight=scale.get_units();	//���ش�����������
  if(abs(weight<5))weight=0;	//�����������ȶ�ֵ
  else weight*=15.4;
  Serial.print("weight reading: ");	//��ʾ����
  Serial.print(weight);         
  Serial.print("g\ndistance: ");
  Serial.print(distance);
  Serial.println("cm\n");
  scale.power_down();              // put the ADC in sleep mode
  delay(1000);
  scale.power_up();
}