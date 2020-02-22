/*
   Author: Ben Lewis
   Date: June 27th, 2018
   Synopsis: The flashlight.
 */

#ifndef Flashlight_h
#define Flashlight_h
#ifndef CI
	#include <Arduino.h>
	#include <RingInterface.h>
#else
	#include <Arduino_MOCK.h>
	#include <RingInterface_MOCK.h>
#endif

/** Flashlight
   -----------
	- A simple class to handle the setting of all lights on the ring to on (and sometimes off and on really fast)
*/
class Flashlight: public RingInterface{
	public:

		//Attributes
		uint32_t colours[8]; //holds the party colours 

		//Methods
		Flashlight(void);
		void on(Adafruit_NeoPixel*);
		void off(Adafruit_NeoPixel*);
		void strobe(bool,Adafruit_NeoPixel*);
		void colorWipe(uint32_t,uint8_t,Adafruit_NeoPixel*);
		uint32_t party(Adafruit_NeoPixel*);
};

#endif

