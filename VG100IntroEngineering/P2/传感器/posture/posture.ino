#include <Wire.h>
#include <JY901.h>
void setup() 
{
  Serial.begin(115200);
  Serial1.begin(115200);
}
float posture()
{
  while (Serial1.available()) JY901.CopeSerialData(Serial1.read()); //Call JY901 data cope function
  return (float)JY901.stcAngle.Angle[2]/32768*180;
}
void loop() 
{
     Serial.println(posture());
}

