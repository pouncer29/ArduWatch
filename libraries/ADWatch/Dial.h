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
		//Methods
		Dial();
};
#endif
		
		
