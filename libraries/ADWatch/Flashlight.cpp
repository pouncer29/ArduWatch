/*
Author: Ben Lewis
Date: June 27th, 2018

Synopsis: The implementation for the flashlight class. Assigns colours and activates lights

*/

#include "Flashlight.h"



//****************************************************************************************
//Flashlight//
//****************************************************************************************

/* Flashflight()
  	precond: none 
   	postcond: none
  
  	Paramaters: neoP - a neopixel ring that will become our flashlight.
  
  	Synopsis: Initializes fancy colours
 */
Flashlight::Flashlight(Adafruit_NeoPixel neoP){
	ring = neoP;
	lightColour = ring.Color(0,0,0,255);
	blank = ring.Color(0,0,0,0);

}

/* on()
   precond: strip has been instantiated
   postcond: all of the lights are turned on to the defined light colour
  
   paramaters: none
   Synopsis: Just turns the lights on guys.
   
	return: Nothing
 */
void Flashlight::on(void){
	colorWipe(lightColour,0);
	return;
}

/* off()
	- actually just a wrapper for the clear function
 */
void Flashlight::off(void){
	ring.clear();
	return;
}


/* strobe()
	precond: ceasePin is attached to a button that will change state
	postcond: light strobes
	
	parameters: ceasePin- the ID number of the pin that we will watch for a cease in strobe.
	
	Synopsis: While the button/switch has not been activeated, rapidly turn the lights from
			  full white to full off. strobe.

	return: nothing
*/	
void Flashlight::strobe(uint8_t ceasePin){
	while(digitalRead(ceasePin)==LOW){
		//Strobe Delay
		delay(30);
		
		//Start off
		off();
		ring.show();
		
		//Wait...?
		delay(100);
		
		on();
	}
	return;
}

