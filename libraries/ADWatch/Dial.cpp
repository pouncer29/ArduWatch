/*
	Author: Ben Lewis
	Date: May 10th, 2018
	
	Synopsis: Implementation for Needle.h
*/

#include "Dial.h"

/*
 *Dial()
 * precond: none
 * postcond: 
 * 
 * Parameters:
 *    Adafruit_Neopixel leds - the chain of Neopixels that will serve as our needle
 *
 * Synopsis: assigns the Faces ring to the ledRing and assigns special colours
 *
 * return: a new Needle Object
 */
Dial::Dial(Adafruit_NeoPixel leds){
	//Instantiate Attributes;
	ring = leds;
	
	//Define special Colours
	regionAColour = ring.Color(1,188,1,0); //green
	regionBColour = ring.Color(155,247,35); //yellow
	regionCColour = ring.Color(255,39,28); //red
	blank = ring.Color(0,0,0,0);
}	

