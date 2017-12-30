/* Welcome to Ben's ArduWatch project!
 * -----------------------------------
 * Look, I know i wasn't the first person to get this idea but I'm trying to make this watch fairly pretty and kind of unique.
 * 
 * Basically I'm trying to use an Adafruit neopixel ring of 12 leds to display the time pulled from the NIST radio time clock (though that
 * is looking more like a stretch goal every day).
 * 
 * Things you should know:
 *  1. I spell colour the way it makes sense and Adafruit spells it "color" like a bunch of yankees. Oh well, lets see how you like to conform 
 *  America.
 *  
 *  2. I am a computer science student. I don't know much besides how to write code, circuits and boards and all this hardware talk has me sh***ing my pants.
 *     So I will try to make up for my lack of hardware knowledge with well documented, clear, and with any luck efficient code though all these infinite loops
 *     make me nervous, so expect some funky functions.
 *  
 *  
 * 
 */

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
         colorWipe(minColour,100);  //2. do the colour wipe
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

//Hand-Index Functions///////////////////////////////////////

/* getHourIndex()
 *  precond: time is set
 *  postcond: none.
 *  
 *  Paramaters
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

/* getMinuteIndex()
 *  precond: time is set;
 *  postcond: none.
 *  
 *  Paramaters
 *    localTime: a time_t that we will harvest the minute from.
 *    
 *  return: The offset corresponding to the current 5 minute interval.
 * 
 */
uint8_t getMinuteIndex(time_t localTime){
    return minute(localTime)/5;
}

/* getSecondIndex()
 *  precond: time is set.
 *  postcond: none.
 *  
 *  Paramaters
 *    localTime: You guessed it, its a time_t that we will use to harvest seconds.
 *    
 *  return: the offset corresponding to the current 5 minute interval.
 * 
 */
uint8_t getSecondIndex(time_t localTime){
  return second(localTime)/5;
}

//Colour modifying functions///////////////////////////////////

/* clearStrip()
 *  precond: strip is not null
 *  postcond: all pixels in ring are set to blank 
 *  
 *  I love adafruit but I couldn't get their .show() to clear the ring like they said it would.
 *  maybe should consider adding the .show() to the end of this one but that could be a mess.
 *  
 *  return: nothing
 * 
 */
void clearStrip(){
  for(uint8_t i = 0; i < strip.numPixels(); i++)
    strip.setPixelColor(i,blank);
}


/* getAverageCross()
 *  precond: none
 *  postcond: none
 *  
 *  Paramaters
 *    colourA/B: Both are unsigned 32 bit unsigned integers that represent 2 colours who's RGBW values will 
 *               be averaged why? Because what else would happen when two clock hands cross?
 *               
 *  return: the uint32 average of the two colours.
 * 
 */
uint32_t getAverageCross(uint32_t colourA, uint32_t colourB){
  return((colourA+colourB)/2);
}


/* minModColour()
 *  precond: time is set
 *  postcond: minuteColour global variable is updated.
 *  
 *  Paramaters
 *    localTime: a time_t that will give us the current minute.
 *  
 *  You trolls thought I forgot didn't you? you were all like "Ben, what the farts? What good is a watch that only
 *  tracks 5 minute intervals? Look, I was thinking the exact same thing, so I decided that minutes should start at
 *  their beautiful green and then, as the minute progresses, get slowly more red to finish with a beautiful purple
 *  at all of your hh:m9 and hh:m4 minutes. YOU'RE WELCOME. 
 *  
 *  How does it work?
 *    You take the remainder of whatever minute it is and 5, multiply it by 64 (to get a max val of 256 and min of 0)
 *    and use it to add to the minHands mined out Red and subtract from its maxed out Green.  
 *  
 *  return: nothing 
 */
void modMinColour(time_t localTime){

  //minMod: Takes the remainder of the 
  uint16_t minMod = ((minute(localTime)%5)*64);
  if(minMod > 0)
    minMod--;   //So that subtact 1 from 256 to prevent wrapping and not from 0 to go out of bounds on the strip array.

  //Minute becomes more red as it progresses.
  minColour = strip.Color(0+minMod,255-minMod,95,0);
  return;
}

/* colorWipe
 *  Took this from the adafruit neopixel playground. It's what i use whith the modded min colour to create that 
 *  epic activation sequence.
 */
void colorWipe(uint32_t c, uint16_t wait) {
  for(uint8_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);    
    strip.show();
    delay(wait);
  }
}

//Controllers//////////////////////////////////////////////////////////

/* trackTime()
 *  precond: time is set
 *  postcond: time is output with stunning style and beauty (i mean, its ok)
 *  
 *  paramaters
 *    localTime: the time we will desplay
 *    
 *  look guys (and guy-etts), this is where the work is done. it gets the clockHand indicies, sets the colours,
 *  determines crossing indexes, and then clears it.
 * 
 */
void trackTime(time_t localTime){

  //Grab our clockHand indecies
  uint8_t hrIdx  = getHourIndex(localTime);
  uint8_t minIdx = getMinuteIndex(localTime);
  uint8_t secIdx = getSecondIndex(localTime);

  //Track minutes with minHand.
  modMinColour(localTime); 
  
  //Assign colours accordingly
  
  //Base case: No Overlap regualr 
  strip.setPixelColor(hrIdx,hrColour);
  strip.setPixelColor(minIdx,minColour);
  strip.setPixelColor(secIdx,secColour);
 
  // Otherwise: If Hands Cross, Their indicies will be the same so I average their set colours.
  if (secIdx == minIdx && minIdx == hrIdx)
    strip.setPixelColor(minIdx,getAverageCross((getAverageCross(secColour,minColour)),hrColour));
  else if(secIdx == minIdx)
    strip.setPixelColor(minIdx,getAverageCross(secColour,minColour));
  else if(secIdx == hrIdx)
    strip.setPixelColor(hrIdx,getAverageCross(secColour,hrColour));
  else if(hrIdx == minIdx)
    strip.setPixelColor(hrIdx, getAverageCross(hrColour,minColour));

  //Display and clear.
  strip.show();
  clearStrip();
}

