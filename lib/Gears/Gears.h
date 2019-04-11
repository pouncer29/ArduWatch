/*
	Author: Ben Lewis 
	Date: January 30th, 2018
	Synopsis: This is the headerfile for the Gears object. It will track time maybe and get Indicies for sure
*/

#ifndef Gears_h
#define	Gears_h

//#include <Arduino.h>
//#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>

/* Gears
   --------------
   So I've decided to name the class that actually gets the time the "Gears" Class. This class should literally just give out the indicies
  for hours, minutes, and seconds. Should it track time? Probably. How can I do that? Not enirely sure. Will think about it. I could maybe 
  make some function that will set indecies at the time and just pass that somehow to the Face for it to display but we will worry about that
  later. For now I just want it to give me the proper indecies, and have NO IDEA about neopixels and no Idea about Arduino if possible.   
*/
class Gears{
	
	public:
		//Attributes
		
		//Methods
		Gears(time_t);
		uint8_t getHourIndex(void);
		uint8_t getMinuteIndex(void);
		uint8_t getSecondIndex(void);
		void updateTime(time_t);
		void trackTime(void);			
	private:
		//Attributes
		time_t curTime;
		//Methods
		

};

#endif
		
		
