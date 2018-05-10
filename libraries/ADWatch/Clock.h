#ifndef Clock_h	
#define Clock_h

#include <Arduino.h>
#include <TimeLib.h>
#include "Face.h"
#include "Gears.h"
#include <Adafruit_NeoPixel.h>


/* Clock
   -----------
	
*/
class Clock{
	public:
		//Attributes
		Adafruit_NeoPixel strip;
		time_t trackMe;
		Face* face;
		Gears* gears;
		
		//Methods
		Clock(time_t,Adafruit_NeoPixel);
		void trackTime(time_t);
		void placeHands(uint8_t,uint8_t,uint8_t);
		void setWatchTime(uint8_t,uint8_t,time_t);
		void removeTail(uint8_t,uint8_t,uint8_t,uint8_t);
};

#endif

