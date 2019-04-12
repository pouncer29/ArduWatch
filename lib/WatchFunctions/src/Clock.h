#ifndef Clock_h	
#define Clock_h

#include <Arduino.h>
#include <TimeLib.h>
#include "Clock_Face.h"
#include "Clock_Gears.h"
#include <Adafruit_NeoPixel.h>


/* Clock
   -----------
	The union of Gears and Face that collects a time_t on creation and assigns array offsets to each of the hands which
	are colour coded (dynamically in some cases) by the Face (subset of Ringinterface) to show the current time.
	
*/
class Clock{
	public:
		//Attributes
		time_t trackMe;
		Clock_Face* face;
		Clock_Gears* gears;
		
		//Methods
		Clock();
		void trackTime(time_t,Adafruit_NeoPixel*);
		void placeHands(uint8_t,uint8_t,uint8_t, Adafruit_NeoPixel*);
		void setWatchTime(uint8_t,uint8_t,time_t,Adafruit_NeoPixel*); //Considering that we may not need to set. method may be donezo
		void removeTail(uint8_t,uint8_t,uint8_t,uint8_t,Adafruit_NeoPixel*);
};

#endif

