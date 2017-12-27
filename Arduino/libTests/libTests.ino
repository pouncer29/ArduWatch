#include <Adafruit_NeoPixel.h>
//#include "arduinoTools.h"
#include <TimeLib.h>

/*From the RGBW TESTS (not everything)*/
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

#define NUM_LEDS 12

#define BRIGHTNESS 20

//For Time
#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

//For Flow
const uint8_t buttonPin = 8;     // the number of the pushbutton pin
//const uint8_t ledPin =  6;      // the number of the LED pin
// variables will change:
uint8_t buttonState = 0;         // variable for reading the pushbutton status

//For Ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);


//Special Colors
uint32_t hrColour = strip.Color(255,255,70,10);
uint32_t minColour = strip.Color(30,245,95,10);
uint32_t secColour = strip.Color(56,94,234,10);
uint32_t blank = strip.Color(0,0,0,0);
void setup() {

    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.begin(9600);
  //pinMode(13, OUTPUT);
  setSyncProvider(requestSync);  //set function to call when sync required
  //Serial.println("Waiting for sync message");

  setTime(11,54,30,12,27,2017);

}

void loop() {
  // put your main code here, to run repeatedly:
  time_t t = now();

  //My function that calls my index functions;

  //Tests Time
  //initStrip(t);

  trackTime(t);
  
  
}


time_t requestSync(){
   Serial.write(TIME_REQUEST);
   return 0;
}


//My Functions

//Resets all nodes to be off... Even though thats what show is supposed to do.
// Because Who Cares about O(n) time anyway? it's only 12.
void clearStrip(){
  for(uint8_t i = 0; i < strip.numPixels(); i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));
}

void learnOffsets(uint16_t wait){
  for(uint8_t i = 0; i<strip.numPixels();i++){
     clearStrip();
     strip.setPixelColor(i,strip.Color(15,(i*5),150,50));
     delay(wait);
     strip.show();
  }
}

uint32_t getAverageCross(uint32_t colorA, uint32_t colorB){
  return((colorA+colorB)/2);
}

//Time Functions
uint8_t getHourIndex(time_t localTime){

  uint8_t curHour = hour(localTime);

  if(curHour < 0)
    return 0;
  else if(curHour >= 12)
    return curHour - 12;
  else
    return curHour;
}

uint8_t getMinuteIndex(time_t localTime){
    return minute(localTime)/5;
}

uint8_t getSecondIndex(time_t localTime){
  return second(localTime)/5;
}

//When the hands advance, remove their trail. it is a gross nest of if statements 
//and if I find a better solution, I will be sure to update it.
void cleanupTrail(uint8_t hrIdx, uint8_t minIdx, uint8_t secIdx){

  //Seconds Cleanup. (case we are at 0th index)/////////////////////
  if((secIdx-1) < 0){
     if(11 == hrIdx)
      strip.setPixelColor(hrIdx, strip.getPixelColor(hrIdx));
    else if(11 == minIdx)
      strip.setPixelColor(minIdx,strip.getPixelColor(minIdx));
    else
      strip.setPixelColor(11, blank);
  }

  //Case we are not at 0th index
  if((secIdx-1) == hrIdx)
    strip.setPixelColor(hrIdx, strip.getPixelColor(hrIdx));
  else if((secIdx-1) == minIdx)
    strip.setPixelColor(minIdx, strip.getPixelColor(minIdx));
  else
    strip.setPixelColor(secIdx-1, blank);

  ///////////////////////////////////////////////////////////

  //Cleanup Minute Trail///////////////////////////////////////////////
    if((minIdx-1) < 0){
     if(11 == hrIdx)
      strip.setPixelColor(hrIdx, strip.getPixelColor(hrIdx));
     else if(11 == secIdx)
      strip.setPixelColor(secIdx, strip.getPixelColor(secIdx));
     else
      strip.setPixelColor(11, blank);
  }

  //Case we are not at 0th index
  if((minIdx-1) == hrIdx)
    strip.setPixelColor(hrIdx, strip.getPixelColor(hrIdx));
  else if((minIdx-1) == secIdx)
    strip.setPixelColor(secIdx, strip.getPixelColor(secIdx));
  else
    strip.setPixelColor(minIdx-1, blank);

 //Cleanup Hour trail////////////////////////////////////////////////

  if((hrIdx-1) < 0){
     if(11 == minIdx)
      strip.setPixelColor(minIdx, strip.getPixelColor(minIdx));
     else if(11 == secIdx)
      strip.setPixelColor(secIdx, strip.getPixelColor(secIdx));
     else
      strip.setPixelColor(11, blank);
  }

  //Case we are not at 0th index
  if((hrIdx-1) == minIdx)
    strip.setPixelColor(minIdx, strip.getPixelColor(minIdx));
  else if((hrIdx-1) == secIdx)
    strip.setPixelColor(secIdx, strip.getPixelColor(secIdx));
  else
    strip.setPixelColor(hrIdx-1, blank);
  
}
void trackTime(time_t localTime){
  uint8_t hrIdx  = getHourIndex(localTime);
  uint8_t minIdx = getMinuteIndex(localTime);
  uint8_t secIdx = getSecondIndex(localTime);


  //No Overlap regualr 
  strip.setPixelColor(hrIdx,hrColour);
  strip.setPixelColor(minIdx,minColour);
  strip.setPixelColor(secIdx,secColour);
  // Overlap
  if (secIdx == minIdx && minIdx == hrIdx){
    strip.setPixelColor(minIdx,getAverageCross((getAverageCross(secColour,minColour)),hrColour));
  }
  else if(secIdx == minIdx){
    strip.setPixelColor(minIdx,getAverageCross(secColour,minColour));
  }
  else if(secIdx == hrIdx){
    strip.setPixelColor(hrIdx,getAverageCross(secColour,hrColour));
  }
  else if(hrIdx == minIdx){
    strip.setPixelColor(hrIdx, getAverageCross(hrColour,minColour));
    strip.setPixelColor(minIdx, getAverageCross(minColour,hrColour)); //Should only need one but things are goofy.
  }

  cleanupTrail(hrIdx,minIdx,secIdx);
//    strip.setPixelColor(hrIdx,hrColour);
//    strip.setPixelColor(minIdx,minColour);
//    strip.setPixelColor(secIdx,secColour);

  strip.show();
}

