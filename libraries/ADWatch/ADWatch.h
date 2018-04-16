#ifndef ADWatch_h
#define ADWatch_h

#include <Arduino.h>
#include <TimeLib.h>
#include <Adafruit_NeoPixel.h>


/* ADWatch
   -----------
	After Complications arose with trying to put everything in seperate modules (as they SHOULD BE), I decided to just
	chuck everything into this one header file. 

	ADWatch Contains Class Definitions for:
	----------------------------------------
	0) ADWatch - the Union of Face and gears
	
	1) Gears - The class responsible for communicating time_t* objects to their appropriate indexes

	2) Face - The class responsible for communicating with the Neopixel ring to determine colour.
	
*/
class ADWatch{
	public:
		//Classes
		class Gears;
		class Face;
		
		//Attributes
		Adafruit_NeoPixel strip;
		time_t trackMe;
		Face* face;
		Gears* gears;
		
		//Methods
		ADWatch(time_t,Adafruit_NeoPixel);
		void trackTime(time_t);
		void placeHands(uint8_t,uint8_t,uint8_t);
		void setWatchTime(uint8_t,uint8_t,time_t);
		void removeTail(uint8_t,uint8_t,uint8_t,uint8_t);
};

/* Gears
   --------------
	- Contains methods to get indecies for the Hour, Minute and Second hands which are used internally to their postition relative
      to the time it has been give to track!
*/
class ADWatch::Gears{
	public:	
		//Methods
		Gears(time_t*);
		uint8_t getHourIndex(void);
		uint8_t getMinuteIndex(void);
		uint8_t getSecondIndex(void);
		time_t getCurTime(void);	
		void updateTime(time_t);		
			
	private:
	//Attributes
	time_t curTime;
};

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


	- Contains the Hard-Coded colour values for the hands as well as other special colours like
	  "reset time Colour" and if you're feeling adventerous, "blank" as well as defines methods
	  to be used by the ADWatch to aid in state representation and time tracking
*/
class ADWatch::Face{
	public:
		//Attributes
		Adafruit_NeoPixel ring;
		uint32_t hrColour;
		uint32_t minColour;
		uint32_t secColour;
		uint32_t rstTimeColour;
		uint32_t blank;
		
		//Methods
		Face(Adafruit_NeoPixel);
		uint32_t getAverageCross(uint32_t,uint32_t);
		void modMinColour(time_t);
		void clearStrip(void);
		void colorWipe(uint32_t, uint16_t);
		void showAvg(uint32_t,uint32_t);
	
};



#endif

