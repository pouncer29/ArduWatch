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

enum Feats {Off = 0,Clock,Compass,Speedometer,Flashlight,Strobe,Refresh,FeatCount = 7}; // Remember to update count if features are added

//For Ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel* ring = &strip;
RTC_Millis rtc;



//Using a master watch Class
ADWatch watch = ADWatch(ring);

//For Flow
//ShowTimeButton
const uint8_t startWatchPin = 8;// the number of the pushbutton pin INPUT
boolean on = false;         //current output state
int buttonState = 0;       //the current flow through the button.
bool isRunning = false;     //whether or not to do the light show on button press
bool initialRun = true;

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

 
  // flow setup
  initialRun = true;


  //INIT RING
    ring->setBrightness(BRIGHTNESS);
    ring->begin();
    ring->clear();
    ring->show(); //Supposedly initilizes all to off
    
    //For Buttons
    pinMode(startWatchPin,INPUT);
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
    Colours[Refresh] = errorColour;

    curFeat = 0;
    prevFeat = 0;
    /**END WATCH SETUP*/
}


void loop()                   
{
    /** WATCH LOOP*/
    Serial.print("Reading is: "); Serial.print(analogRead(A0)); Serial.print(" Feat is: "); Serial.println(curFeat);
    
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
        switch (curFeat){
            case Off:
                ring->clear();
                ring->show();
                break;
            case Clock :
                Serial.println(curFeat);
                time_t curTime = rtc.now().unixtime();
                watch.showTime(curTime);
                break;
            case Compass:
                break;

            case Speedometer:

                break;
            case Flashlight:
                Serial.println(curFeat);
                watch.showLight();
                ring->show();
                break;
            case Strobe:
                Serial.println(curFeat);
                watch.showStrobe(startWatchPin);
                break;
            case Refresh:
                Serial.println(curFeat);
                //watch.refresh(!gTools.hasFix());
                break;
            default:
                Serial.println(curFeat);
                watch.showError(partyColour);
                break;
        }
        delay(500);
    }
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
