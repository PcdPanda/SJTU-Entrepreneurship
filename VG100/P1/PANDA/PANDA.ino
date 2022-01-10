
#define hwr 7
#define hwl 44
#define hwh 9
#define hwR 22
#define hwL 10
#define redpin 46
#define greenpin 47
#define bluepin 48
#define IN1 5
#define IN2 6
#define IN3 3
#define IN4 4
#define ENA 12 /*right motor*/
#define ENB 13  /*left motor*/

int RL=1;//1 left
int ZY=1;
void hw()
{
  while(1)
  {
      int r =digitalRead(hwr);
      int l =digitalRead(hwl);
      int h=digitalRead(hwh);
      int r1=digitalRead(hwR);
      int l1=digitalRead(hwL);
      Serial.print("l=");
      Serial.println(l);
      Serial.print("h=");
      Serial.println(h);
      Serial.print("r=");
      Serial.println(r);
      Serial.print("l1=");
      Serial.println(l1);
      Serial.print("r1=");
      Serial.println(r1);      
      delay(200);
  }
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

void setColor(int red, int green, int blue)
{
  analogWrite(redpin, red);
  analogWrite(greenpin, green);
  analogWrite(bluepin, blue);  
}

void Led(int a)//�
{
  if(a==1)setColor(255, 0, 0);
  else if(a==2)setColor(0, 255, 0);
  else if(a==3)setColor(0, 0, 255);   
  else setColor(0,0,0);
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

void Forward(int t)//
{
  Motor(1,150);
  Motor(2,125);
  Serial.println("         Forward");              
  delay(t);
  Stop();
}

void Right90()
{
    Stop();
    Motor(1,150);
    Motor(2,-150);
    Serial.println("          RIGHT90");
    delay(550);
    Stop();
 }

void Left90()
{
    Stop();
    Motor(1,-150);
    Motor(2,150);
    Serial.println("          LEFT90");
    delay(550);
    Stop();
}

void right()
{
  Motor(1,125);
  Motor(2,25);
  Serial.println("Turning right");  
}

void left()
{
  Motor(1,25);
  Motor(2,100);
  Serial.println("Turning right");  
}
//--------------------------------------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600); 
  Serial1.begin(9600);
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT); 
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(hwr,INPUT);
  pinMode(hwl,INPUT);
  pinMode(hwh,INPUT);
  pinMode(hwR,INPUT);
  pinMode(hwL,INPUT);
}

void loop() 
{
  int r =digitalRead(hwr);
  int l =digitalRead(hwl);
  int h=digitalRead(hwh);
  int r1=digitalRead(hwR);
  int l1=digitalRead(hwL);
  //hw();
//---------------------------------------------------------------------------------------------
  if(l1==0)RL=1;
  if(r1==0)RL=2;
  if(h==0)
  {
    Stop();
    if(r==0)
    {
      RL=2;
      Left90();
    }
    else 
    {
      RL=1;
      Right90();
    }
  }
  else
  {
    Led(0);
    if(r==1&&l==1)
    {
      Stop();
      if(digitalRead(hwr)==0||digitalRead(hwl)==0)return;
      ZY=0;
      while(digitalRead(hwh)==1)
      {
        if(Read()==1)
        {
          ZY=1;
          Led(1);
        }
        Motor(1,140);
        Motor(2,100);
      }
      Stop();
      if(ZY==1)
      {
        Left90();
        RL=2;
      }
      else 
      {
        Right90();
        RL=1;
      }
    }    
    else if(RL==2)
    { 
      Led(2);
      if(r==0)
      {
        if(digitalRead(hwR)==0)left();
        else right();
      }
      else
      {
        if(l1=digitalRead(hwL)==0)right();
        else left();
      }
    }
    else
    { 
      Led(3);
      if(l==0)
      {
        if(l1=digitalRead(hwL)==0)right();
        else left();
      }
      else
      {
        if(digitalRead(hwR)==1)right();
        else left();
      }
    }
  }
}
             
             


