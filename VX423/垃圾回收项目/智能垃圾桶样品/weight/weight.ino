/**
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
#include "HX711.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 10;  // HX711 dout pin
const int LOADCELL_SCK_PIN = 9;  // HX711 sck pin


HX711 scale;

void setup() {
  Serial.begin(38400);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(2280.f);                      
  scale.tare();				        
}

void loop() {
  Serial.print("weight reading:\t");
  Serial.print(scale.get_units(), 1);

  scale.power_down();			        // put the ADC in sleep mode
  delay(250);
  scale.power_up();
}
