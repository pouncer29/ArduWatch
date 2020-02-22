/*
Author: Ben Lewis
Date: May 16th, 2018

Synopsis: Compass_Magnet: The means of moving a compass needle.

*/
#ifndef Compass_Magnet_h
#define Compass_Magnet_h

#include <Arduino.h>




/** Compass_Magnet
   --------------
	- Contains methods to map a degree heading [0,360] to an array offset [0,11]
*/
class Compass_Magnet{
	public:	
		//Methods
		Compass_Magnet(void);
		float getCurHeading(void);	
		uint8_t getHeadingIndex(void);
		void updateHeading(float);		
			
	private:
		//Attributes
		float curHeading;
};

#endif

