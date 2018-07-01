#ifndef Speedometer_h	
#define Speedometer_h

#include <Arduino.h>
#include "Dial.h"
#include "Gauge.h"
#include <Adafruit_NeoPixel.h>


/* Speedometer
   - The union of Gauge and Dial. Takes a speed in knots from the gps, converts it to kmph,
	 and then displays it in 20kmph starting from index 6 (0kmph) to 4 ( > 180kmph).	
*/
class Speedometer{
	public:
		//Attributes
		Adafruit_NeoPixel strip;
		Dial* dial;
		Gauge* gauge;
		
		//Methods
		Speedometer(float,Adafruit_NeoPixel); //TODO maybe change from float but hey, maybe not.
		void trackSpeed(float);
		void setSpeed(float);
		void removeTail(float);
		void setDial(uint8_t);
		void setRegionA(uint8_t);
		void setRegionB(uint8_t);
		void setRegionC(uint8_t);

		float curSpeed;
		uint8_t curHeadIdx;
		uint8_t prevHeadIdx;
};

#endif

