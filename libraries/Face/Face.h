/*
	Author: Ben Lewis 
	Date: January 23rd, 2018
	Synopsis: This is the headerfile I really wanted to make work but didn't know that 
			  you need to include <Arduino.h>. Makes sense to me now. This is the Interface
			  between time and the ring of leds.
*/

#ifndef Face_h
#define	Face_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>

/* Face
   --------------
   
   Look, Nobody can get it right the first time. I just wanted a working watch. Now that I kind
   of have that, It's time to rethink our architecture. That is what this branch is for. 
   Why? Becuase unless you can tell me why we are setting the time and the colours for the 
   hands in the same class, I'm going to stick with my gut and say it was a poor design 
   choice. 
   
   This class now has but one pupose: Manage colours. It will still be the interface between
   time and the ring but now that time and it's indices will be coming from elsewhere. 
   It is going to be a right nasty refactor but I think is for the best!
*/
class Face{
	
	public:
		//Attributes
		Adafruit_NeoPixel ring;
		uint32_t hrColour;
		uint32_t minColour;
		uint32_t secColour;
		uint32_t rstTimeColour;
		//Methods
		Face(Adafruit_NeoPixel);
		void modMinColour(time_t);
		void clearStrip(void);
		void colorWipe(uint32_t, uint16_t);
		
		
	private:
		uint32_t blank;
		uint32_t getAverageCross(uint32_t,uint32_t);
		

};

#endif
		
		