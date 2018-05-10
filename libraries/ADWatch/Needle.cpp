/*
	Author: Ben Lewis
	Date: May 10th, 2018
	
	Synopsis: Implementation for Needle.h
*/

#include "Needle.h"

/*
 *Needle()
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
Needle::Needle(Adafruit_NeoPixel leds){
	
	//Instantiate Attributes;
	ring = leds;
	
	//Define special Colours
}	
