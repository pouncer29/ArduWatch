/*
Author: Ben Lewis
Date: May 25th, 2018

Synopsis: The GPS interface for the speedometer class
*/

#ifndef Speed_Gauge_h
#define Speed_Gauge_h
#include <Arduino.h>




/** Speed_Gauge
	- The liason between gps and speedometer, takes in a speed IN KMPH and gives back meaningful
	  array offsets for the read speeds.
*/
class Speed_Gauge{
	public:	
		//Methods
		Speed_Gauge(float);
		float getCurSpeed(void);	
		uint8_t getSpeedIndex(void);
		void updateSpeed(float);		
			
	private:
		//Attributes
		float curSpeed; //KMPH
};



#endif

