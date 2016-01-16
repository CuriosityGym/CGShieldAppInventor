// sets up and initialize CGShield
#include <CGShield.h>
#include <Wire.h>         // Require for I2C communication
CGShield fs;        

void setup() {
   Serial.begin(9600);     // Setup serial communications for troubleshooting
  Serial.println("FS_06_Temp_Sensors.ino");

}

void loop() {
   int tempVal = temp();
   Serial.println(tempVal);
  
  delay(1000);

}