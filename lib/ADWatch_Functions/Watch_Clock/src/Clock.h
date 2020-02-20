/*
Author: Ben Lewis
Date: May 10th, 2018

Synopsis: outline for the Clock function.

*/
#ifndef Clock_h
#define Clock_h

#ifndef CI
	#include <TimeLib.h>
	#include <Adafruit_NeoPixel.h>
#else
	#include <TimeLib_MOCK.h>
	#include <Adafruit_NeoPixel_MOCK.h>
#endif 

#include <Clock_Face.h>
#include <Clock_Gears.h>


/** Watch_Clock
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

