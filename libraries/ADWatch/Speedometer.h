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
		void setDial(uint8_t);
		void setSpeed(float);
		void removeTail(float);

		float curSpeed;
		uint8_t curHeadIdx;
		uint8_t prevHeadIdx;
};

#endif

