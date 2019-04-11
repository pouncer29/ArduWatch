/*
	Author: Ben Lewis
	Date: January 30th, 2018
	
	Synopsis: Implementation of Index getter "Gears"
*/

#include "Gears.h"


Gears::Gears(time_t localTime){
	
	curTime = localTime;	
}

/*
 getHourIndex()
	- Checks whether or not the index is in 24 hour notation and returns the appropriate hour index for time "curTime".
*/
uint8_t Gears::getHourIndex(void){
  	//store hour
	uint8_t	hr = hour(curTime);
	
	//determine index
	if(hr < 0)
		return -1;
	else if (hr >= 12)	//Handles 24hr time (no 24th neopixel)
		return hr - 12;
	else
		return hr;
}

/*
 getMinuteIndex()
	- takes the minute value of the instance time "curTime" and returns a valid clock offset for it.
*/
uint8_t Gears::getMinuteIndex(void){
	return minute(curTime)/5;
}

/*
 getSecondIndex()
	- takes the second value of the instance time "curTime" and returns a valid clock offset for it.
*/
uint8_t Gears::getSecondIndex(void){
	return second(curTime)/5;
}

/*
 updateTime()
	- takes in a time_t and updates its curTime attribute to be it.
*/
void Gears::updateTime(time_t newTime){
	curTime = newTime;
}

void Gears::trackTime(void){
	return;
}
	
	
	
