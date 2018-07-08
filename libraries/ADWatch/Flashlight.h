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
		//Attributes		
		uint32_t lightColour;
		//Methods
		Flashlight(Adafruit_NeoPixel); //TODO maybe change from float but hey, maybe not.
		void on(void);
		void off(void);
		void strobe(uint8_t);
};

#endif

