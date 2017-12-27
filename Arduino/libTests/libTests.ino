#include <Adafruit_NeoPixel.h>
//#include "arduinoTools.h"
#include <TimeLib.h>

/*From the RGBW TESTS (not everything)*/
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

#define NUM_LEDS 12

#define BRIGHTNESS 30

//For Time
#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

const uint8_t buttonPin = 8;     // the number of the pushbutton pin
//const uint8_t ledPin =  6;      // the number of the LED pin
// variables will change:
uint8_t buttonState = 0;         // variable for reading the pushbutton status

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);



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

  setTime(4,37,45,12,12,2017);

}

void loop() {
  // put your main code here, to run repeatedly:
  time_t t = now();

  //My function that calls my index functions;

  //Tests Time
  //initStrip(t);

  trackTime(t);
  
  //clear Strip
//  delay(3000);
//  clearStrip();
//  strip.show();
//
//  //check index 3
//  strip.setPixelColor(3,strip.Color(70,255,70,10));
//  strip.show();
  
//  delay(3000);
//  clearStrip();
//  strip.show();

//  // check Index 1;
//  strip.setPixelColor(1,strip.Color(70,70,255,50));
//  strip.show();
//
//  delay(3000);
//  clearStrip();
//  strip.show();

//  learnOffsets(200);

//  delay(3000);
//  clearStrip();
//  strip.show();


  
}


time_t requestSync(){
   Serial.write(TIME_REQUEST);
   return 0;
}


//My Functions
void initStrip(time_t curTime){
  uint8_t hrIdx = getHourIndex(curTime);
  uint8_t minIdx = getMinuteIndex(curTime);
  uint8_t secIdx = getSecondIndex(curTime);
//
  strip.setPixelColor(hrIdx,strip.Color(255,255,70,10));
  strip.setPixelColor(minIdx,strip.Color(30,245,95,10));
  strip.setPixelColor(secIdx,strip.Color(56,94,234,10));
  strip.show();
  
}

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


void trackSeconds(time_t localTime){
  uint8_t secIdx = getSecondIndex(localTime);

  //Clear the previous second to blank (0,0,0,0)
  if(secIdx == 0)
    strip.setPixelColor(11,strip.Color(0,0,0,0));
  else
    strip.setPixelColor(secIdx -1,strip.Color(0,0,0,0));

  //Update the seconds;
  strip.setPixelColor(secIdx,strip.Color(56,94,234,10));
}

void trackMinutes(time_t localTime){
  uint8_t minIdx = getMinuteIndex(localTime);
  
  //set previous strip to 0;
  if(minIdx == 0)
    strip.setPixelColor(11,strip.Color(0,0,0,0));
  else
    strip.setPixelColor(minIdx -1,strip.Color(0,0,0,0));

  strip.setPixelColor(minIdx,strip.Color(30,245,95,10));
}


//set previous hour to blank;
void trackHours(time_t localTime){
  uint8_t hrIdx = getHourIndex(localTime);
  
  if(hrIdx == 0)
    strip.setPixelColor(11,strip.Color(0,0,0,0));
  else
    strip.setPixelColor(hrIdx -1,strip.Color(0,0,0,0));

  strip.setPixelColor(hrIdx,strip.Color(255,255,70,10));
  
}

void trackTime(time_t localTime){
  trackHours(localTime);
  trackMinutes(localTime);
  trackSeconds(localTime);

  strip.show();
}

