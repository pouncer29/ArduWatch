/*
	Author: Ben Lewis
	Date: January 23rd, 2018

	Synopsis: Implementation for time-tracking methods.
*/

#include "RingInterface_MOCK.h"

/** RingInterface()
   @Synopsis: Defines interface specific display methods and allows universal colour definition.
 */
RingInterface::RingInterface(void){}


/** getAverageCross()
    precond: none
    postcond: none
    
    @param: colourA/B - Both are unsigned 32 bit unsigned integers that represent 2 colours who's RGBW values will be
							averaged and returned. Used for crossing indecies.
                 
    return: the uint32 average of the two colours.
   
 */
uint32_t RingInterface::getAverageCross(uint32_t colourA, uint32_t colourB){
  return((colourA+colourB)/2);
}

/** colorWipe()
   @Synopsis: This code is from Adafruit's NeoPixel Playground, I did not write it. It's what i use whith the modded min colour to create that
   epic activation sequence.
 */
void RingInterface::colorWipe(uint32_t c, uint16_t wait,Adafruit_NeoPixel* ring) {
  for(uint8_t i=0; i<12; i++) {
    ring->setPixelColor(i, c);    
    ring->show();
    delay(wait);
  }

}

	
