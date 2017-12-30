#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>

/*From the RGBW TESTS*/
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 12
#define BRIGHTNESS 20

//For Time?
#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

//For Flow

//ShowTimeButton
const uint8_t startWatchPin = 8;// the number of the pushbutton pin INPUT
boolean on = false;         //current output state
int buttonState = 0;       //the current flow through the button.

bool flourish = true;     //whether or not to do the light show on button press

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
  
  //Test Time for testing.
  setTime(1,14,45,12,28,2017);


}

void loop() {
  time_t t =now();
  
 //Start Watch Button checker 
  buttonState=digitalRead(startWatchPin);
  if(buttonState == HIGH){
     if(on == true)
       on = false;
     else
       on = true;
  }

  //Start watch button code.
  if(on == true){
      t=now();
      if(flourish){
         modMinColour(t);           //1. get the flourish colour
         colorWipe(minColour,400);  //2. do the colour wipe
         clearStrip();              //3. reset ring to blank
         strip.show();              //4. push the blank ring
         delay(700);                
         flourish = false;          //5. remember not to florish every time we show the time.
      }
      trackTime(t);   
     
    }
   else{
    clearStrip();                   //1. Button must be off, clear the strip
    strip.show();                   //2. push the clear
    flourish = true;                //3. remember to flourish when we turn it back on.
   }

    delay(200);                     //Apparently good for 'debounce' whatever that is.
  
}

//No clue.
time_t requestSync(){
   Serial.write(TIME_REQUEST);
   return 0;
}


//****************FUNCTIONS*********************

//Time Index Functions

/* getHourIndex()
 *  precond: time is set
 *  postcond: none.
 *  
 *  Variables
 *    localTime: a time_t that we will harvest the hour from.
 *  
 *  return: The offset corresponding to the current hour with 0 being 12/2400 and 11 being 11/2300
 */
uint8_t getHourIndex(time_t localTime){

  uint8_t curHour = hour(localTime);

  // if the hour is negative (traveling backwards in time) return -1 for error.
  if(curHour < 0)
    return -1;
  else if(curHour >= 12)  // if it's >= than 12 (24hr format) just subract 12 from that sucker
    return curHour - 12;
  else
    return curHour;      // if its not >=12 it must be before 12:00 so it has a reasonable index.
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

