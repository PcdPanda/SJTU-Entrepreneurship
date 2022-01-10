#define sensor 0//绾㈠娴嬭窛
int d;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //pinMode(sensor,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  d=analogRead(sensor);
  Serial.println(d);
  delay(200);
}

