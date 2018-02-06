#ifndef ADWatch_h
#define ADWatch_h

#include <Arduino.h>
#include <TimeLib.h>
#include <Adafruit_NeoPixel.h>


/* ADWatch
   -----------
   After trying to use a separate module for each component of the watch I decide to say f it.
   I'll just put everything in one document. Probably a decent choice because I bought an
   Adafruit trinket to run this on and has far less memory on it.

*/
class ADWatch{
		
	public:
		//Classes
		/* Gears
		   --------------
		  So I've decided to name the class that actually gets the time the "Gears" Class. This class should literally just give out the indicies
		  for hours, minutes, and seconds. Should it track time? Probably. How can I do that? Not enirely sure. Will think about it. I could maybe 
		  make some function that will set indecies at the time and just pass that somehow to the Face for it to display but we will worry about that
		  later. For now I just want it to give me the proper indecies, and have NO IDEA about neopixels and no Idea about Arduino if possible.   
		*/
		class Gears;
		class Gears{
			public:
			//Attributes
			/*none*/
			
			//Methods
			Gears(time_t);
			uint8_t getHourIndex(void);
			uint8_t getMinuteIndex(void);
			uint8_t getSecondIndex(void);
			void updateTime(time_t);
			//void trackTime(void);			
	
			private:
			//Attributes
			time_t curTime;
			//Methods
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
	*/
		class Face;
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
				uint32_t getAverageCross(uint32_t,uint32_t);
				void modMinColour(time_t);
				void clearStrip(void);
				void colorWipe(uint32_t, uint16_t);
				void showAvg(uint32_t,uint32_t);
		
			private:
				uint32_t blank;
		};
		
		//Attributes
		//Adafruit_NeoPixel ring;
		Face face;
		Gears gears;
		//time_t trackMe;

	//Methods
		ADWatch(time_t,Adafruit_NeoPixel);
		void trackTime(time_t);
};

#endif

