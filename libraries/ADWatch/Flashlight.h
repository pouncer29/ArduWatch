/* Author: Ben Lewis
   Date: June 27th, 2018
   Synopsis: The flashlight.
 */

#ifndef Flashlight_h
#define Flashlight_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "RingInterface.h"

/* Flashlight
   -----------
	- A simple class to handle the setting of all lights on the ring to on (and sometimes off and on really fast)
	
*/
class Flashlight: public RingInterface{
	public:
		//Methods
		Flashlight(void); //TODO maybe change from float but hey, maybe not.
		void on(Adafruit_NeoPixel*);
		void off(Adafruit_NeoPixel*);
		void strobe(uint8_t,Adafruit_NeoPixel*);
		void colorWipe(uint32_t,uint8_t,Adafruit_NeoPixel*);
};

#endif

