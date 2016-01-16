#include <CGShield.h>
#include <Wire.h>
CGShield fs; 
void setup() {
 
Serial.begin(9600);
}

void loop() {
   int lightVal = light();
   
  int lightMap=map(lightVal, 0,1023, 0,255);
   
  LEDByte(lightMap);
   
  
	

}