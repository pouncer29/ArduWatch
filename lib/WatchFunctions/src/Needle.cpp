/*
	Author: Ben Lewis
	Date: May 10th, 2018
	
	Synopsis: Implementation for Needle.h
*/

#include "Needle.h"

/* Needle()
   precond: none
   postcond: leds is initialized
   
   Parameters: leds - the chain of Adafruit_Neopixels that will represent our needle locations
  
   Synopsis: Assigns the special colours needed for the compass function. North Yellow, heading blue or someting.
  
   return: a new Needle Object
 */
Needle::Needle(){
	
	//Define special Colours
	northColour = ring->Color(255,100,0,5);
	needleColour = ring->Color(221,224,208,0);
	blank = ring->Color(0,0,0,0);

}	
