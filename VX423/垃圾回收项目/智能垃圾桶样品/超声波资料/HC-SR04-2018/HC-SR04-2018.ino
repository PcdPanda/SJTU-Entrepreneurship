/*
 模块：HC-SR04-2018
 功能：读取2018版HC-SR04距离数据并串口显示
 连线：
   -VCC   = 5V /3.3V 
   -TRIG  = A3 
   -ECHO  = A2 
   -GND   = GND
 编写：无锡日晨物联科技有限公司
*/
float      distance;
const int  echo=A2;                          //echO接A2脚
const int  trig=A3;                          //echO接A3脚
void setup()
{
  Serial.begin(9600);                       //波特率9600
  pinMode(echo,INPUT);                       //设置echo为输入脚
  pinMode(trig,OUTPUT);                      //设置trig为输出脚
  Serial.println("HC-SR04-2018测距开始：");
}
void loop()
{
 digitalWrite(trig,LOW);
 delayMicroseconds(20); 
 digitalWrite(trig,HIGH);
 delayMicroseconds(20);
 digitalWrite(trig,LOW);                     //发一个20US的高脉冲去触发Trig
 
 distance  = pulseIn(echo,HIGH);             //计数接收高电平时间
 distance  = distance*340/2/10000;           //计算距离 1：声速：340M/S  2：实际距离1/2声速距离 3：计数时钟为1US
 Serial.print("距离: ");
 Serial.print(distance);
 Serial.println("cm");
 delay(20);                                   //单次测离完成后加20mS的延时再进行下次测量。防止近距离测量时，测量到上次余波，导致测量不准确。
 delay(500);                                  //500mS测量一次
} 


