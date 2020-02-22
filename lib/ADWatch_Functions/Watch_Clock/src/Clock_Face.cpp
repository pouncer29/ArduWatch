/*
	Author: Ben Lewis
	Date: January 23rd, 2018
	
	Synopsis: Implementation for Watch_Clock Ring-Interface via 'face'
*/

#include <Clock_Face.h>

/** Clock_Face()
   @Synopsis: assigns the Clock_Faces ring to the ledRing and assigns special colours
 */
Clock_Face::Clock_Face(){
	
	//Define special Colours
	hrColour = ring->Color(255,100,0,5);
	minColour = ring->Color(0,255,95,0);
	secColour = ring->Color(0,160,255,0);
	blank = ring->Color(0,0,0,0);
}

/** minModColour()
    @precond: time is set
    @postcond: minuteColour global variable is updated.
    
    @param: localTime -  a time_t that will give us the current minute.
    @param: ring - the NeoPixel ring we will access colour from.


   @Synopsis:
    You trolls thought I forgot didn't you? you were all like "Ben, what the farts? What good is a watch that only
    tracks 5 minute intervals? Look, I was thinking the exact same thing, so I decided that minutes should start at
    their beautiful green and then, as the minute progresses, get slowly more red to finish with a beautiful purple
    at all of your hh:m9 and hh:m4 minutes. YOU'RE WELCOME. 
    
    How does it work?
      You take the remainder of whatever minute it is and 5, multiply it by 64 (to get a max val of 256 and min of 0)
      and use it to add to the minHands mined out Red and subtract from its maxed out Green.  
    
 */
void Clock_Face::modMinColour(time_t localTime,Adafruit_NeoPixel* ring){

  //minMod: Takes the remainder of the minute and 5 to cycle through values of 0-4
  uint16_t minMod = ((minute(localTime)%5)*64);
  if(minMod > 0)
    minMod--;   //So that subtract 1 from 256 to prevent wrapping and not from 0 to go out of bounds on the strip array.

  //Minute becomes more red and less green as it progresses.
  minColour = ring->Color(0+minMod,255-minMod,95,0);
  ring->setPixelColor(11,blank); //The original Magic 11 appearance.
  return;
}

