/*
	Author: Ben Lewis 
	Date: December 30th, 2017
	Synopsis: This is the headerfile I really wanted to make work but didn't know that 
			  you need to include <Arduino.h>. Makes sense to me now. This is the Interface
			  between time and the ring of leds.
*/

#ifndef trackTime_h
#define	trackTime_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>

/* Face_Show_Time
   --------------
   
   This is the Ring-Time Interface. Or kind of at least. It contains all the tools needed
   to set the time-Colours, calculate the indicies, do cool effects. You name it. I'm more of
   a java guy WHEN it comes to Object Oriented code. I learned c++ in first year but we only
   did procedural c++ and some fancy work with structs. This is my first c++ object.
   
   It has an Adafruit_NeoPixel object as a paramater that I've named "ring" because I feel
   its a bit more descriptive. Why is it not given a time_t? because the way I have the ino 
   code written, that would mean re-instantiating the object every time the loop executed
   to track time accurately. I wasn't a huge fan of that, so for right now, I'm just going
   to updated it in the Arduino controller code.
*/
class Face_Show_Time{
	
	public:
		Adafruit_NeoPixel ring;
		uint32_t hrColour;
		uint32_t minColour;
		uint32_t secColour;
		uint32_t blank;
		Face_Show_Time(Adafruit_NeoPixel);
		void modMinColour(time_t);
		void trackTime(time_t);
		void colorWipe(uint32_t, uint16_t);
		void clearStrip(void);
		
		
	private:
		uint8_t getHourIndex(time_t);
		uint8_t getMinuteIndex(time_t);
		uint8_t getSecondIndex(time_t);
		uint32_t getAverageCross(uint32_t,uint32_t);
};

#endif
		
		