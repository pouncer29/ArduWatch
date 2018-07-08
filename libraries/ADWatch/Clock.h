#ifndef Clock_h	
#define Clock_h

#include <Arduino.h>
#include <TimeLib.h>
#include "Face.h"
#include "Gears.h"
#include <Adafruit_NeoPixel.h>


/* Clock
   -----------
	The union of Gears and Face that collects a time_t on creation and assigns array offsets to each of the hands which
	are colour coded (dynamically in some cases) by the Face (subset of Ringinterface) to show the current time.
	
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
		void setWatchTime(uint8_t,uint8_t,time_t); //Considering that we may not need to set. method may be donezo
		void removeTail(uint8_t,uint8_t,uint8_t,uint8_t);
};

#endif

