#ifndef Speedometer_h	
#define Speedometer_h

#include <Arduino.h>
#include "Dial.h"
#include "Gauge.h"
#include <Adafruit_NeoPixel.h>


/* Speedometer
   -----------
	
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

