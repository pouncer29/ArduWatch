#ifndef Compass_h	
#define Compass_h

#include <Arduino.h>
#include "Compass_Needle.h"
#include "Compass_Magnet.h"
#include <Adafruit_NeoPixel.h>


/* Compass
   -----------
	
*/
class Compass{
	public:
		//Attributes
		Adafruit_NeoPixel strip;
		Needle* needle;
		Magnet* magnet;
		
		//Methods
		Compass(); //TODO maybe change from float but hey, maybe not.
		void trackHeading(float,Adafruit_NeoPixel*);
		void placeNeedle(uint8_t,Adafruit_NeoPixel*);
		void setCompassHeading(float,Adafruit_NeoPixel*);
		void removeTail(float,Adafruit_NeoPixel*);

		float curHeading;
		uint8_t curHeadIdx;
		uint8_t prevHeadIdx;
};

#endif

