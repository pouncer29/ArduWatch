/*
	Author: Ben Lewis 
	Date: December 30th, 2017
	Synopsis: This is the headerfile I really wanted to make work but didn't know that 
			  you need to include <Arduino.h>. Makes sense to me now.
*/

#ifndef trackTime_h
#define	trackTime_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>

class Time_Tracker{
	
	public:
		Adafruit_NeoPixel strip;
		uint32_t hrColour;
		uint32_t minColour;
		uint32_t secColour;
		uint32_t blank;
		Time_Tracker(Adafruit_NeoPixel);
		void modMinColour(time_t);
		void trackTime(time_t);
		
		
	private:
		uint8_t getHourIndex(time_t);
		uint8_t getMinuteIndex(time_t);
		uint8_t getSecondIndex(time_t);
		void clearStrip(void);
		void colorWipe(uint32_t, uint16_t);
		uint32_t getAverageCross(uint32_t,uint32_t);
};

#endif
		
		