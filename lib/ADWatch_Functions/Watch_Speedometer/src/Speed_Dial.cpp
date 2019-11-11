/*
	Author: Ben Lewis
	Date: May 10th, 2018
	
	Synopsis: Implementation for Speed_Dial.h
*/

#include <Speed_Dial.h>

/** Speed_Dial()
   precond: Leds initialized
   postcond: New Speed_Dial is created

   @Synopsis: assigns special colours and inits ring to the LEDs
  
 */
Speed_Dial::Speed_Dial(){
	//Instantiate Attributes;
	
	//Define special Colours
	regionAColour = ring->Color(1,188,1,0); //green
	regionBColour = ring->Color(155,247,35); //yellow
	regionCColour = ring->Color(255,39,28); //red
	blank = ring->Color(0,0,0,0);
	errorColour = ring->Color(255,0,0,0);
}	


