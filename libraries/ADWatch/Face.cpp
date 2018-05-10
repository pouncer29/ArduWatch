/*
	Author: Ben Lewis
	Date: January 23rd, 201ljkj:jkjkjkjkjjkjklljhhljkkjkjk8
	
	Synopsis: Implementation for time-tracking methods.
*/

#include "Face.h"

/*
 *Face()
 * precond: none
 * postcond: a new Face object is created
 * 
 * Parameters:
 *    Adafruit_Neopixel leds - the chain of Neopixels that will serve as our face.
 *
 * Synopsis: assigns the Faces ring to the ledRing and assigns special colours
 *
 * return: a new Face Object
 */
Face::Face(Adafruit_NeoPixel leds){
	
	//Instantiate Attributes;
	ring = leds;
	
	//Define special Colours
	hrColour = ring.Color(255,100,0,5);
	minColour = ring.Color(0,255,95,0);
	secColour = ring.Color(0,160,255,0);
	rstTimeColour = ring.Color(255,0,0,0);
	blank = ring.Color(0,0,0,0);
}


/*
clearStrip()
 *  precond: none
 *  postcond: all pixels in ring are set to blank 
 *  
 *	Synopsis: clears all of the colours from the rings indicies.
 * 
 *  return: nothing
 */
void Face::clearStrip(void){
	ring.clear();
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
uint32_t Face::getAverageCross(uint32_t colourA, uint32_t colourB){
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
void Face::modMinColour(time_t localTime){

  //minMod: Takes the remainder of the 
  uint16_t minMod = ((minute(localTime)%5)*64);
  if(minMod > 0)
    minMod--;   //So that subtact 1 from 256 to prevent wrapping and not from 0 to go out of bounds on the strip array.

  //Minute becomes more red as it progresses.
  minColour = ring.Color(0+minMod,255-minMod,95,0);
  ring.setPixelColor(11,blank);
  return;
}

/* colorWipe
 *  This code is from Adafruit's NeoPixel Playground, I did not write it. It's what i use whith the modded min colour to create that 
 *  epic activation sequence.
 */
void Face::colorWipe(uint32_t c, uint16_t wait) {
  for(uint8_t i=0; i<12; i++) {
    ring.setPixelColor(i, c);    
    ring.show();
    delay(wait);
  }
  clearStrip();
  ring.show();
}

//FOR TESTING ONLY
void Face::showAvg(uint32_t A, uint32_t B){
	colorWipe(getAverageCross(A,B),200);
	return;
}


	
	
	
