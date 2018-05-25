/*
	Author: Ben Lewis 
	Date: May 10th, 2018
	Synopsis: The Ring interface for Speedometer Needle
*/

#ifndef Dial_h
#define	Dial_h

#include <Adafruit_NeoPixel.h>
#include "RingInterface.h"

/* Dial
   --------------
	The Dial class is the Speedometer Equivilent of Face.  

*/
class Dial: public RingInterface{
	
	public:
		//Attributes
		uint32_t regionAColour; //[0,60)
		uint32_t regionBColour; // [60,120)
		uint32_t regionCColour; // [120,180)
		uint32_t blank;

		//Methods
		Dial(Adafruit_NeoPixel);
		void setRegions(void);
};
#endif
		
		
