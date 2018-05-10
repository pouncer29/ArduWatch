/*
	Author: Ben Lewis 
	Date: May 10th, 2018
	Synopsis: The Superclass for all ring interfaces
*/

#ifndef RingInterface_h
#define	RingInterface_h

#include <Adafruit_NeoPixel.h>
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
class RingInterface{
	
	public:
		//Attributes
		Adafruit_NeoPixel ring;
		uint32_t blank;
		//Methods
		RingInterface();
		uint32_t getAverageCross(uint32_t,uint32_t);
		void clearStrip(void);
	    void colorWipe(uint32_t, uint16_t);
		void showAvg(uint32_t,uint32_t);
		
		

};

#endif
		
		
