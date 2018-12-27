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
Flashlight::Flashlight(void){
	blank = ring.Color(0,0,0,0);
	lightColour = ring.Color(255,255,255,40);
}

void Flashlight::colorWipe(uint32_t c, uint8_t wait,Adafruit_NeoPixel* ring) {
  for(uint8_t i=0; i<12; i++) {
    ring->setPixelColor(i, c);    
    ring->show();
    //delay(wait);
  }
}



/* on()
   precond: strip has been instantiated
   postcond: all of the lights are turned on to the defined light colour
  
   paramaters: none
   Synopsis: Just turns the lights on guys.
   
	return: Nothing
 */
void Flashlight::on(Adafruit_NeoPixel* ring){
	colorWipe(lightColour,0,ring);

/*	for(uint8_t i=0; i<12; i++) {
		ring->setPixelColor(i, lightColour);    
		ring->show();
		//delay(0);
  	}*/

	return;
}




/* off()
	- actually just a wrapper for the clear function
 */
void Flashlight::off(Adafruit_NeoPixel* ring){
	ring->clear();
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
void Flashlight::strobe(uint8_t ceasePin, Adafruit_NeoPixel* ring){
	ring->setPixelColor(6,ring->Color(0,255,0,0));
	ring->show();
	while(digitalRead(ceasePin)==LOW){
		//Strobe Delay
		delay(30);


		//ring->setPixelColor(6,ring->Color(0,0,255,0));	
		//Start off
		//off(ring);
		ring->clear();
		ring->show();
		
		//Wait...?
		delay(100);
		
		on(ring);
	}
	return;
}

