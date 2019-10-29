/*
	Author: Ben Lewis 
	Date: January 23rd, 2018
	Synopsis: This is the headerfile I really wanted to make work but didn't know that 
			  you need to include <Arduino.h>. Makes sense to me now. This is the Interface
			  between time and the ring of leds.
*/

#ifndef Clock_Face_h
#define	Clock_Face_h

#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include <RingInterface.h>

/* Face
   -------------- 
   *******************************************************************************************
   Look, Nobody can get it right the first time. I just wanted a working watch. Now that I kind
   of have that, It's time to rethink our architecture. That is what this branch is for. 
   Why? Because unless you can tell me why we are setting the time and the colours for the
   hands in the same class, I'm going to stick with my gut and say it was a poor design 
   choice. 
   
   This class now has but one purpose: Manage colours. It will still be the interface between
   time and the ring but now that time and it's indices will be coming from elsewhere. 
   It is going to be a right nasty refactor but I think is for the best!
   *******************************************************************************************

	Kept the above comment block for comedic purposes. This class had a lot of weight taken off of it's shoulders
	during the architecture update. Now it is a subclass of 'RingInterface' which holds some of the bulkier and more
	trivial functions that all feature classes must use on the ring. Defines Hand colours and the 'modMinColour' function
	that is so crucial to the clock function
*/
class Clock_Face: public RingInterface{
	
	public:
	//Methods
		Clock_Face();
		void modMinColour(time_t,Adafruit_NeoPixel*);
};

#endif
		
		
