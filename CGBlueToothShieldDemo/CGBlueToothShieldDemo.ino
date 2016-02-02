#include <CGShield.h>
#include <Wire.h>         // Require for I2C communication
#include <IRremote.h>

CGShield CS;

#define LEDFRAME 0X41

#define BUZZERFRAME 0X42

#define BUTTONFRAME 0X43

#define SENSORFRAME 0X45



#define RFRAME 0X47
#define GFRAME 0X48
#define BFRAME 0X49
#define IRFRAME 0x50

#define ACKFRAME 0X59 //Y
#define SYNCFRAME 0X5A //Z

#define FRAMELENGTH 0X05

boolean packetStarted=false;
boolean packetComplete=false;
uint8_t redIntensity=0, greenIntensity=0,blueIntensity=0;
boolean buttonL, buttonR;

void setup() {

 Serial.begin(115200);
  /*Serial.write(0xFF);
  Serial.write(0X44);
  Serial.write(0x57);
  Serial.write(0x01);
  Serial.write(0xFF);
*/
}

void loop()
{

  serialEvent();
  //Serial.println(round(light()*100/1024),DEC);
  //delay(100);


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
         //Serial.println("PacketRecieved");
          uint8_t requestType=serialStream[1];

             if(requestType==LEDFRAME)
             {
                  //Serial.println("LEDFrame Detected");
                  uint8_t ledNumber=serialStream[2];
                  uint8_t ledState=serialStream[3];
                 //Serial.print("LED Number: ");
                  //Serial.println(ledNumber, DEC);
                  if(ledState==0x01)
                  {
                    //Serial.println("LED State High");
                    LED(ledNumber, HIGH);
                  }
                  else
                  {
                    //Serial.println("LED State LOW");
                    LED(ledNumber, LOW);
                  }
             }

                 if(requestType==BUZZERFRAME)
             {
                  //Serial.println("BuzzerFrame Detected");
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
                  //Serial.println("Red Color Frame Detected");
                  redIntensity=serialStream[2];
                  RGB(redIntensity,greenIntensity,blueIntensity);

                }

                if(requestType==GFRAME)
                {
                  //Serial.println("Green Color Frame Detected");
                  greenIntensity=serialStream[2];
                  RGB(redIntensity,greenIntensity,blueIntensity);

                }

                if(requestType==BFRAME)
                {
                  //Serial.println("Blue Color Frame Detected");
                  blueIntensity=serialStream[2];
                  RGB(redIntensity,greenIntensity,blueIntensity);

                }

                if(requestType==SENSORFRAME)
                {
                  //Serial.println("Temp Color Frame Detected");
                   int lightVal=light();
                   int trimVal=trim();
                   uint8_t buttonval = 0X0F;
                   uint8_t right = 0XFE, left = 0XFD;
                   buttonL = button(LEFT);
                   buttonR = button(RIGHT);
                   if (!buttonR){
                    buttonval = buttonval&right;
                   }
                   if (!buttonL){
                    buttonval = buttonval&left;
                   }
                   //float lightValPercent=(lightVal/1024)*100;
                   Serial.write(0xFF);
                   Serial.write(SENSORFRAME);
                   Serial.write(round(temp()));
                   Serial.write(round(floor(lightVal/256)));
                   Serial.write(round(lightVal%256));
                   Serial.write(round(floor(trimVal/256)));
                   Serial.write(round(trimVal%256));
                   Serial.write(buttonval);
                   Serial.write(0xFF);
                }

                 if(requestType==BUZZERFRAME)
                {
                    //Serial.println("Buzzer Frame Detected");

                    uint8_t highByteFreq=serialStream[2];
                    uint8_t lowByteFreq=serialStream[3];
                     //Serial.println(highByteFreq, DEC);
                    //Serial.println(lowByteFreq, DEC);
                    int buzzerFrequency=(highByteFreq<<8) +lowByteFreq;
                    speaker(buzzerFrequency,500);
                }


     }

    }

}
