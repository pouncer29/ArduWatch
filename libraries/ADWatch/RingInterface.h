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
		Adafruit_NeoPixel ring;
		uint32_t blank;
		uint32_t errorColour;
		//Methods
		RingInterface();
		uint32_t getAverageCross(uint32_t,uint32_t);
		void clearStrip(void);
	    void colorWipe(uint32_t, uint16_t);
		void showAvg(uint32_t,uint32_t);
		
		

};

#endif
		
		
