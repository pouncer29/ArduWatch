#ifndef Compass_h	
#define Compass_h

#include <Arduino.h>
#include "Needle.h"
#include "Magnet.h"
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
		Compass(float,Adafruit_NeoPixel); //TODO maybe change from float but hey, maybe not.
		void trackHeading(float);
		void placeNeedle(uint8_t);
		void setCompassHeading(float);
		void removeTail(float);

		float curHeading;
		uint8_t curHeadIdx;
		uint8_t prevHeadIdx;
};

#endif

