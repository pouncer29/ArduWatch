/*
	Author: Ben Lewis
	Date: January 23rd, 2018
	
	Synopsis: Implementation for time-tracking methods.
*/

#include "RingInterface.h"

/*
 *RingInterface()
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
RingInterface::RingInterface(){
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
void RingInterface::clearStrip(void){
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
uint32_t RingInterface::getAverageCross(uint32_t colourA, uint32_t colourB){
  return((colourA+colourB)/2);
}

/* colorWipe
 *  This code is from Adafruit's NeoPixel Playground, I did not write it. It's what i use whith the modded min colour to create that 
 *  epic activation sequence.
 */
void RingInterface::colorWipe(uint32_t c, uint16_t wait) {
  for(uint8_t i=0; i<12; i++) {
    ring.setPixelColor(i, c);    
    ring.show();
    delay(wait);
  }
  clearStrip();
  ring.show();
}

//FOR TESTING ONLY
void RingInterface::showAvg(uint32_t A, uint32_t B){
	colorWipe(getAverageCross(A,B),200);
	return;
}

	
