#ifndef Gears_h
#define Gears_h

#include <Arduino.h>
#include <TimeLib.h>




/* Gears
   --------------
	- Contains methods to get indecies for the Hour, Minute and Second hands which are used internally to their postition relative
      to the time it has been give to track!
*/
class Gears{
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



#endif

