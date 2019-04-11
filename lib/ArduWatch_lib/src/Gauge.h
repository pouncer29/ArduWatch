/*
Author: Ben Lewis
Date: May 25th, 2018

Synopsis: The GPS interface for the speedometer class
*/

#ifndef Gauge_h
#define Gauge_h
#include <Arduino.h>




/* Gauge
	- The liason between gps and speedometer, takes in a speed IN KMPH and gives back meaningful
	  array offsets for the read speeds.
*/
class Gauge{
	public:	
		//Methods
		Gauge(float);
		float getCurSpeed(void);	
		uint8_t getSpeedIndex(void);
		void updateSpeed(float);		
			
	private:
		//Attributes
		float curSpeed; //KMPH
};



#endif

