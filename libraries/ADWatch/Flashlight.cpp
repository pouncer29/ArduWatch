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
	blank = ring->Color(0,0,0,0);
	lightColour = ring->Color(255,255,255,40);
	violet = ring->Color(148,0,211,0);
	indigo = ring->Color(75,0,130,0);
	blue = ring->Color(0,0,255,0); 
	green = ring->Color(0,255,0,0);
	yellow = ring->Color(255,255,0,0);
	orange = ring->Color(255,127,0,0);
	red = ring->Color(255,0,0,0);
	
	//store the colours.
	colours[0] = lightColour;
	colours[1] = violet;
	colours[2] =indigo;
	colours[3] = blue;
	colours[4] = green;
	colours[5] = yellow;
	colours[6] = orange;
	colours[7] = red;
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
		
	return;
}




/* off()
	- actually just a wrapper for the clear function
 */
void Flashlight::off(Adafruit_NeoPixel* ring){
	ring->clear();
	return;
}

/*party()
	-Jazzy colour version of on
*/
uint32_t Flashlight::party(Adafruit_NeoPixel* ring){
	static uint16_t count = 0;	
	count++;
	if(count > 8)
		count = 0;

	return colours[count%8];
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
	uint8_t flip = 0;
	uint32_t colour = lightColour;
	while(digitalRead(8)==LOW){
		//Strobe Delay
		delay(30);

		//Start off
		//off(ring);
		ring->clear();
		ring->show();
		
		//Wait...?
		delay(100);
		flip++;
		
		if(flip > 25){
			flip =0;
			//pick random color
			colour = party(ring);
		}	
	
		colorWipe(colour,0,ring);
	}
	return;
}

