/*
	Author: Ben Lewis
	Date: May 10th, 2018
	
	Synopsis: Implementation for Dial.h
*/

#include "Dial.h"

/* Dial()
   precond: Leds initialized
   postcond: New Dial is created
   
   Parameters: leds - the chain of Neopixels that will serve as our Dial
  
   Synopsis: assigns special colours and inits ring to the LEDs
  
   return: a new Dial Object
 */
Dial::Dial(){
	//Instantiate Attributes;
	
	//Define special Colours
	regionAColour = ring->Color(1,188,1,0); //green
	regionBColour = ring->Color(155,247,35); //yellow
	regionCColour = ring->Color(255,39,28); //red
	blank = ring->Color(0,0,0,0);
	errorColour = ring->Color(255,0,0,0);
}	


