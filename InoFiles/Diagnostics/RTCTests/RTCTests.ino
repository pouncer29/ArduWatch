#include "RTClib.h"
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <ADWatch.h>
#include <TimeLib.h>


/**
 *  WATCH SETUP BEGIN
 */

#define PIN 6
#define NUM_LEDS 12
#define BRIGHTNESS 10

enum Feats {Off = 0,Clock,Compass,Speedometer,Flashlight,Strobe,Set,FeatCount = 7}; // Remember to update count if features are added

//For Ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel* ring = &strip;
RTC_Millis rtc;

//Button Setup 
const int buttonPin = 12;
uint8_t buttonState = 0;
boolean settingTime = false;




//Using a master watch Class
ADWatch watch = ADWatch(ring);

//For Flow

//Flourish Colours
uint32_t compassColour;
uint32_t speedoColour;
uint32_t clockColour;
uint32_t flashColour;
uint32_t partyColour;
uint32_t errorColour;
uint32_t blank;
uint32_t  err = ring->Color(255,0,0,0);

uint32_t Colours[FeatCount];
int curFeat;
int prevFeat;

/** END WATCH SETUP */

void setup()
{

  Serial.begin(57600);

  //SETUP RTC
  #ifndef ESP8266
   while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif

   rtc.begin(DateTime(F(__DATE__), F(__TIME__)));

   //SETUP BUTTON
   pinMode(buttonPin, INPUT);

 
  //INIT RING
    ring->setBrightness(BRIGHTNESS);
    ring->begin();
    ring->clear();
    ring->show(); //Supposedly initilizes all to off
    

    //Init Flourish Colours & Cycler
    clockColour = watch.clock_colour;
    compassColour = watch.compass_colour;
    speedoColour = watch.speedo_colour;
    flashColour = watch.light_colour;
    partyColour = watch.party_colour;
    errorColour = watch.error_colour;
    blank = watch.blank;

    Colours[Off] = blank;
    Colours[Clock] =clockColour;
    Colours[Compass] = compassColour;
    Colours[Speedometer] = speedoColour;
    Colours[Flashlight] = flashColour;
    Colours[Strobe] = partyColour;
    Colours[Set] = errorColour;

    curFeat = 0;
    prevFeat = 0;
    /**END WATCH SETUP*/
}


void loop()                   
{
    /** WATCH LOOP*/
    if(settingTime == false){
    curFeat = getFeat();
    if(curFeat != prevFeat){
        //If Turning on for the first time
        if(prevFeat == Off) {
            //setTime(gTools.grabTime());
        }
        ring->clear();
        prevFeat = curFeat;
        watch.flourish(Colours[curFeat],100);
        delay(800);
    }else{
        Serial.print("CurFeat: ");
        if(curFeat == Off){
          ring->clear();
          ring->show();
          
        } else if (curFeat == Clock){
            Serial.println("CLOCK");
            time_t curTime = rtc.now().unixtime();
            watch.showTime(curTime);
        } else if (curFeat == Flashlight){
            Serial.println("LIGHT");
            watch.showLight();
            ring->show();
          
        } else if (curFeat == Strobe){ 
            Serial.println("STROBE");
            watch.showStrobe(6);
        } else if (curFeat == Set){
            Serial.println("IN SET");
            configureTime(watch);
            settingTime= false;
        } else { 
           Serial.println(curFeat);
           watch.showError(partyColour);
        }
//        switch (curFeat){
//            case Off:
//                ring->clear();
//                ring->show();
//                break;
//            case Clock :
//                Serial.println("CLOCK");
//                time_t curTime = rtc.now().unixtime();
//                watch.showTime(curTime);
//                break;
//            case Compass:
//                break;
//            case Speedometer:
//                break;
//            case Flashlight:
//                Serial.println("LIGHT");
//                watch.showLight();
//                ring->show();
//                break;
//            case Strobe:
//                Serial.println("STROBE");
//                watch.showStrobe(6);
//                break;
//            case Set:
//                Serial.println("IN SET");
//                watch.flourish(Colours[Strobe],50);
//           
//                //uint32_t _hour = configureTime(watch,watch.clock_colour_hr);
//                //uint32_t _minute = 0;
//                //uint32_t _second = 0;
//                //Serial.println(_hour); 
//                break;
//            default:
//                Serial.println(curFeat);
//                watch.showError(partyColour);
//                break;
//        }
        delay(500);
    }
    }
}

void configureTime(ADWatch w){
  uint8_t clickCount = 0;
  settingTime = true;
  uint8_t idx = 0;
  uint32_t timeColours[] = {w.clock_colour_hr, w.clock_colour_min, w.clock_colour_sec};
  uint8_t timeValues[] = {0,0,0};
 while(clickCount < 2) {
  Serial.print("ClickCount: "); Serial.println(clickCount);
  idx = (analogRead(A0) / 10) % 12;
  ring->clear();
  ring->setPixelColor(idx,timeColours[clickCount]);
  ring->show();
  delay(10);
  if(digitalRead(buttonPin) == HIGH){
    timeValues[clickCount] = idx;
    Serial.print("Set To:"); Serial.println(idx);
    clickCount++;
    delay(10);
  }
  delay(100);
 }

 DateTime newTime = DateTime(2022,3,6,timeValues[0],timeValues[1],timeValues[2]);
 rtc.adjust(newTime);

}

/** Gets the Current Feat based on dial position*/
Feats getFeat(){
  int reading = analogRead(A0);
  int featId = watch.getWatchFunction(reading);
  Serial.print("FeatId: ");Serial.println(featId);
  Feats feat = (Feats) featId;
  Serial.print("Feat is: "); Serial.println(feat);
  return feat;
}
