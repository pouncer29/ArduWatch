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
		Clock(float,Adafruit_NeoPixel); //TODO maybe change from float but hey, maybe not.
		void trackHeading(float);
		void placeNeedle(uint8_t);
		//void setWatchTime(uint8_t,uint8_t,time_t);
		void removeTail(uint8_t,uint8_t,uint8_t,uint8_t);
};

#endif

