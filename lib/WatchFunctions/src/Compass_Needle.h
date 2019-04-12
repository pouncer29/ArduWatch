/*
	Author: Ben Lewis 
	Date: May 10th, 2018
	Synopsis: The Ring interface for Speedometer Needle
*/

#ifndef Compass_Needle_h
#define	Compass_Needle_h

#include <Adafruit_NeoPixel.h>
#include "RingInterface.h"

/* Needle
   --------------
	The Needle class is the Compass Equivilent of Face. It is responsible for providing a steady northern Index (0) and a 
	varying needle index. It will interpret the readings from the magnet class much like Face does from the Gears class.

*/
class Needle: public RingInterface{
	
	public:
		//Attributes
		//Methods
		Needle();
};
#endif
		
		
