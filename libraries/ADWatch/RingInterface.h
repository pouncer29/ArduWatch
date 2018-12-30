/*
	Author: Ben Lewis 
	Date: May 10th, 2018
	Synopsis: The Superclass for all ring interfaces
*/

#ifndef RingInterface_h
#define	RingInterface_h
#include <Adafruit_NeoPixel.h>
/* RingInterface
	------------
	This class serves as the Interface with the Neopixel ring for all watch functions. Thats right. 
	Speedometer, Compass, Clock, Flashlight. They all need special colours, they for the most part all 
	implement average, clear, or wipe. This class provides them that.
*/
class RingInterface{
	
	public:
		//Attributes
		Adafruit_NeoPixel* ring;
		uint32_t blank;
		uint32_t errorColour;
		
		//Clock Colors
		uint32_t hrColour;
		uint32_t minColour;
		uint32_t secColour;

		//Compass
		uint32_t northColour;
		uint32_t needleColour;

		//Speedometer
		uint32_t regionAColour; //[0,60)
		uint32_t regionBColour; // [60,120)
		uint32_t regionCColour; // [120,180)

		//Flashlight
		uint32_t lightColour;
		uint32_t violet;
		uint32_t indigo;
		uint32_t blue;
		uint32_t green;
		uint32_t yellow;
		uint32_t orange;
		uint32_t red;

		//Methods
		RingInterface();
		uint32_t getAverageCross(uint32_t,uint32_t);
	    void colorWipe(uint32_t, uint16_t,Adafruit_NeoPixel*);
		void showAvg(uint32_t,uint32_t);

};

#endif
		
		
