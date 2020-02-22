/*
	Author: Ben Lewis 
	Date: May 10th, 2018
	Synopsis: The Ring interface for Speedometer Needle
*/

#ifndef Speed_Dial_h
#define	Speed_Dial_h

#ifndef CI
	#include <Adafruit_NeoPixel.h>
	#include <RingInterface.h>
#else
	#include <Adafruit_NeoPixel_MOCK.h>
	#include <RingInterface_MOCK.h>
#endif

/** Speed_Dial
   --------------
	The Speed_Dial class is the Speedometer Equivalent of Face.
*/
class Speed_Dial: public RingInterface{
	
	public:
		//Methods
		Speed_Dial();
};
#endif
		
		
