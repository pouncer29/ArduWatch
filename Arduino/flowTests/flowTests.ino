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

//ShowTimeButton
const uint8_t startWatchPin = 8;     // the number of the pushbutton pin INPUT
//const uint8_t watchPin =  6;      // the number of the LED pin OUTPUT
boolean on = false;         //current output state
int buttonState = 0;

//For Flourish
bool flourish = true;

//For Ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);


//Special Colors
uint32_t hrColour = strip.Color(255,100,0,5);
uint32_t minColour = strip.Color(0,255,95,0);
uint32_t secColour = strip.Color(0,160,255,0);
uint32_t blank = strip.Color(0,0,0,0);

//Preconditions
void setup() {

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  //For LED ring
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  //For god knows what
  Serial.begin(9600);
  setSyncProvider(requestSync);  //set function to call when sync required
  //Serial.println("Waiting for sync message");

  //For Buttons
  pinMode(startWatchPin,INPUT);
 // pinMode(watchPin, OUTPUT);
  
  //Test Time for testing.
  setTime(1,14,45,12,28,2017);


}

void loop() {
  // put your main code here, to run repeatedly:
  time_t t =now();
  

  buttonState=digitalRead(startWatchPin);

  if(buttonState == HIGH){
     if(on == true)
       on = false;
     else
       on = true;
  }

  if(on == true){
      t=now();
      
      if(flourish){
         modMinColour(t);
         colorWipe(minColour,400);
         clearStrip();
         strip.show();
         delay(700);
         flourish = false;
      }
      trackTime(t);
     
    }
   else{
    clearStrip();
    strip.show();
    flourish = true;
   }

    delay(200);
  
}


time_t requestSync(){
   Serial.write(TIME_REQUEST);
   return 0;
}


//****************FUNCTIONS*********************

//Time Index Functions
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

//Colour modifying functions
void clearStrip(){
  for(uint8_t i = 0; i < strip.numPixels(); i++)
    strip.setPixelColor(i,strip.Color(0,0,0,0));
}

uint32_t getAverageCross(uint32_t colorA, uint32_t colorB){
  return((colorA+colorB)/2);
}

void modMinColour(time_t localTime){
    //modify Minutes colour
  uint32_t minMod = ((minute(localTime)%5)*64);
  if(minMod > 0)
    minMod--;

  //Minute becomes more red as it progresses.
  minColour = strip.Color(0+minMod,255-minMod,95,0);
  return;
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint8_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);    
    strip.show();
    delay(wait);
  }
}

//Controllers
void trackTime(time_t localTime){
  uint8_t hrIdx  = getHourIndex(localTime);
  uint8_t minIdx = getMinuteIndex(localTime);
  uint8_t secIdx = getSecondIndex(localTime);
 
  modMinColour(localTime); 
  //No Overlap regualr 
  strip.setPixelColor(hrIdx,hrColour);
  strip.setPixelColor(minIdx,minColour);
  strip.setPixelColor(secIdx,secColour);
 
  // If Hands Cross, Their indicies will be the same so I average their set colours.
  if (secIdx == minIdx && minIdx == hrIdx)
    strip.setPixelColor(minIdx,getAverageCross((getAverageCross(secColour,minColour)),hrColour));
  else if(secIdx == minIdx)
    strip.setPixelColor(minIdx,getAverageCross(secColour,minColour));
  else if(secIdx == hrIdx)
    strip.setPixelColor(hrIdx,getAverageCross(secColour,hrColour));
  else if(hrIdx == minIdx)
    strip.setPixelColor(hrIdx, getAverageCross(hrColour,minColour));
  
  strip.show();
  clearStrip();
}

