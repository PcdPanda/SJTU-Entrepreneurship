
#define hw1 7
#define laser 3
#define IN1 5
#define IN2 6
#define IN3 3
#define IN4 4
#define ENA 12 /*right motor*/
#define ENB 13  /*left motor*/

int RL=1;//1 left
int ZY=1;
float      distance;
const int  echo=A2;                          //echO接A2脚
const int  trig=A3;                          //echO接A3脚
void hw()
{
  while(1)
  {
      int hw =digitalRead(hw1);
      Serial.print("hw=");
      Serial.println(hw); 
      delay(200);
  }
}
void ss()
{
 digitalWrite(trig,LOW);
 delayMicroseconds(20); 
 digitalWrite(trig,HIGH);
 delayMicroseconds(20);
 digitalWrite(trig,LOW);                     //发一个20US的高脉冲去触发Trig
 
 distance  = pulseIn(echo,HIGH);             //计数接收高电平时间
 distance  = distance*340/2/10000;           //计算距离 1：声速：340M/S  2：实际距离1/2声速距离 3：计数时钟为1US
 Serial.print("distance: ");
 Serial.print(distance);
 Serial.println("cm");
 delay(20);                                   //单次测离完成后加20mS的延时再进行下次测量。防止近距离测量时，测量到上次余波，导致测量不准确。
 delay(500);                                  //500mS测量一次
} 
void  Motor(int a,int s)//
{
  if(a==1)
  {
    if(s==0)
    {
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
    }
    else if(s>0)
    {
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      analogWrite(ENB,s);
    }    
    else
    {
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      analogWrite(ENB,-s);
    }    
  }
  else if(a==2)
  {
    if(s==0)
    {
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
    }
    else if(s>0)
    {
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      analogWrite(ENA,s);
    }    
    else
    {
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      analogWrite(ENA,-s);  
    }    
  }
}



int Read()//
{
  String zy;
  int ct;
  for(ct=1;ct<=100;ct++)
    {
    zy="";
    if(Serial1.available()>0)
      {
        zy+=char(Serial1.read());
        Serial.println(zy);
        if(zy[0]=='2')return 2;//you
        else if(zy[0]=='1')return 1;
      };
    }
  return 0;
}
     
void Stop()//
{
  Motor(1,0);
  Motor(2,0);
  Serial.println("        STOP");
  delay(500);
}


//--------------------------------------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600); 
  Serial1.begin(9600);
  pinMode(hw1,INPUT);
  pinMode(echo,INPUT);                       //设置echo为输入脚
  pinMode(trig,OUTPUT);                      //设置trig为输出脚
  pinMode(laser,OUTPUT);
  
}

void loop() 
{
  digitalWrite(laser,HIGH);
  ss();
  
  }
             
             


