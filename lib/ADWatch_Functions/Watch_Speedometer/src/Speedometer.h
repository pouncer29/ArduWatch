/*
Author: Ben Lewis
Date: May 25th, 2018

Synopsis: The implementation for Speedometer.h
*/
#ifndef Speedometer_h
#define Speedometer_h

#ifndef CI
	#include <Arduino.h>
#endif
#include <Speed_Dial.h>
#include <Speed_Gauge.h>
#include <Adafruit_NeoPixel.h>


/** Speedometer
   - The union of Gauge and Dial. Takes a speed in knots from the gps, converts it to kmph,
	 and then displays it in 20kmph starting from index 6 (0kmph) to 4 ( > 180kmph).	
*/
class Speedometer{
	public:
		//Attributes
		Speed_Dial* dial;
		Speed_Gauge* gauge;
		
		//Methods
		Speedometer(); //TODO maybe change from float but hey, maybe not.
		void trackSpeed(float,Adafruit_NeoPixel*);
		void setSpeed(float);
		void removeTail(float,Adafruit_NeoPixel*);
		void setDial(uint8_t,Adafruit_NeoPixel*);
		void setRegionA(uint8_t,Adafruit_NeoPixel*);
		void setRegionB(uint8_t,Adafruit_NeoPixel*);
		void setRegionC(uint8_t,Adafruit_NeoPixel*);

		float curSpeed;
		uint8_t curHeadIdx;
		uint8_t prevHeadIdx;
};

#endif

