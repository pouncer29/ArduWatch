/*
	Author: Ben Lewis 
	Date: May 10th, 2018
	Synopsis: The Ring interface for Speedometer Compass_Needle
*/

#ifndef Compass_Needle_h
#define	Compass_Needle_h

#ifndef CI
	#include <Adafruit_NeoPixel.h>
	#include <RingInterface.h>
#else
	#include <Adafruit_NeoPixel_MOCK.h>
	#include <RingInterface_MOCK.h>
#endif


/** Compass_Needle
   --------------
	The Compass_Needle class is the Compass Equivilent of Face. It is responsible for providing a steady northern Index (0) and a
	varying needle index. It will interpret the readings from the magnet class much like Face does from the Gears class.

*/
class Compass_Needle: public RingInterface{
	
	public:
		//Methods
		Compass_Needle();
};
#endif
		
		
