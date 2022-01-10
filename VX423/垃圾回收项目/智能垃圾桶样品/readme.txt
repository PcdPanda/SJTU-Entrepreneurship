prototpye用arduino mega2560作为主控器,平时可以用充电宝或者电脑供电，需要读数据的话直接连接电脑打开arduino串口监视器即可，
波特率我设置的是9600
一共用了2个传感器，分别为顶部的超声波测距HC-SR04和底部的电桥式称重传感器配合HX711芯片
超声波一共4个接口，gnd和vcc供电，Echo和trig负责通信，接线方式对应程序
HX711一共4个接口，gnd和vcc供电，Dout和SCK负责通信，接线方式对应程序
此外还用了一个舵机RDS3218负责上下开关，不需要额外电源供电，直接对应程序接到arduino板上即可

如果要更改程序的话必须要在arduino库中包含HX711.H github上面有或者在auduino中项目-加载库中添加


#include <Servo.h>  //头文件
#include "HX711.h"	//HX711库
const int LOADCELL_DOUT_PIN = 10;	//HX711dout口接到arduino10号信号口
const int LOADCELL_SCK_PIN = 9;	//HX711sck口接到arduino9号信号口
float      distance;
const int  echo=A2;                          //超声波echo口接arduinoA2信号口
const int  trig=A3;                          // 超声波trig口接arduinoA3信号口
// HX711 circuit wiring
Servo myservo;	//定义伺服电机
HX711 scale;	//定义称重传感器

int pos=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);		//读数据时串口监视器的波特率
  myservo.attach(11);		//舵机接arduino11号口，棕色线接GND
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // 设置HX711
  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // 初始化称重传感器

  pinMode(echo,INPUT);                       //  设置超声波模式
  pinMode(trig,OUTPUT);                      //
}

void loop() {
  // put your main code here, to run repeatedly:	//这段被我注释了，是可以控制舵机位置0-180
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
  myservo.write(0);		//将舵机位置设置到0度
  double distance, weight;
  digitalWrite(trig,LOW);
  delayMicroseconds(20); 
  digitalWrite(trig,HIGH);
  delayMicroseconds(20);
  digitalWrite(trig,LOW);                     
  distance  = pulseIn(echo,HIGH);	   
  distance  = distance*340/2/10000; 
  if(distance>150)distance=0;	//以上8行是超声波读数据    
  weight=scale.get_units();	//称重传感器读数据
  if(abs(weight<5))weight=0;	//过滤重量不稳定值
  else weight*=15.4;
  Serial.print("weight reading: ");	//显示数据
  Serial.print(weight);         
  Serial.print("g\ndistance: ");
  Serial.print(distance);
  Serial.println("cm\n");
  scale.power_down();              // put the ADC in sleep mode
  delay(1000);
  scale.power_up();
}