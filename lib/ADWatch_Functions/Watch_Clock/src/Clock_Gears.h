/*
Author: Ben Lewis
Date: February 6th, 2018

Synopsis: Clock_Gears for the watch

*/
#ifndef Clock_Gears_h
#define Clock_Gears_h

#include <Arduino.h>
#include <TimeLib.h>

/* Gears
   --------------
	- Contains methods to get indecies for the Hour, Minute and Second hands which are used internally to their position relative
      to the time it has been give to track!
*/
class Clock_Gears{
	public:	
		//Methods
		Clock_Gears();
		uint8_t getHourIndex(void);
		uint8_t getMinuteIndex(void);
		uint8_t getSecondIndex(void);
		time_t getCurTime(void);	
		void updateTime(time_t);		
			
	private:
		//Attributes
		time_t curTime;
};

#endif

