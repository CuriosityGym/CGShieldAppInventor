#include <CGShield.h>
#include <Wire.h>         // Require for I2C communication

CGShield CS;  

#define LEDFRAME 0X41 

#define BUZZERFRAME 0X42 

#define BUTTONFRAME 0X43 

#define LIGHTFRAME 0X44 

#define TEMPFRAME 0X45 

#define TRIMFRAME 0X46 

#define RFRAME 0X47 
#define GFRAME 0X48 
#define BFRAME 0X49 

#define ACKFRAME 0X59 //Y
#define SYNCFRAME 0X5A //Z

#define FRAMELENGTH 0X05

boolean packetStarted=false;
boolean packetComplete=false;
uint8_t redIntensity=0, greenIntensity=0,blueIntensity=0;


void setup() {

 Serial.begin(115200);
  Serial.write(0xFF);
  Serial.write(0x00);
  Serial.write(0x06);
  Serial.write(0x01);
  Serial.write(0xFF);

}

void loop()
{
 
  serialEvent();
 

}

void serialEvent()
{


   if(Serial.available()> FRAMELENGTH-1)
    {
      packetComplete=false;
      uint8_t serialStream[FRAMELENGTH]={};  
      for(uint8_t dataCounter=0;dataCounter<FRAMELENGTH;dataCounter++)
      {
        serialStream[dataCounter]=(uint8_t)Serial.read();
      }  

      if(serialStream[0]==0xFF && serialStream[FRAMELENGTH-1]==0xFF)
     {
         Serial.println("PacketRecieved");
          uint8_t requestType=serialStream[1];

             if(requestType==LEDFRAME)
             {
                  Serial.println("LEDFrame Detected");
                  uint8_t ledNumber=serialStream[2];
                  uint8_t ledState=serialStream[3];
                  Serial.print("LED Number: ");
                  Serial.println(ledNumber, DEC);
                  if(ledState==0x01)
                  {
                    Serial.println("LED State High");
                    LED(ledNumber, HIGH);
                  }
                  else
                  {
                    Serial.println("LED State LOW");
                    LED(ledNumber, LOW);
                  }
             }

                 if(requestType==BUZZERFRAME)
             { 
                  Serial.println("BuzzerFrame Detected");
                  //uint8_t ledNumber=serialStream[2];
                  uint8_t buzzerState=serialStream[3];
                  if(buzzerState==0x01)
                  {
                   //TODO 
                   //LED(ledNumber, HIGH);
                  }
                  else
                  {
                    //TODO
                    //LED(ledNumber, LOW);
                  }
             }

              
                if(requestType==RFRAME)
                {
                  Serial.println("Red Color Frame Detected");
                  redIntensity=serialStream[2];
                  RGB(redIntensity,greenIntensity,blueIntensity);
                 
                }

                if(requestType==GFRAME)
                {
                  Serial.println("Green Color Frame Detected");
                  greenIntensity=serialStream[2];
                  RGB(redIntensity,greenIntensity,blueIntensity);
                 
                }

                if(requestType==BFRAME)
                {
                  Serial.println("Blue Color Frame Detected");
                  blueIntensity=serialStream[2];
                  RGB(redIntensity,greenIntensity,blueIntensity);
                 
                } 
          
     }
      
    }
  
}

