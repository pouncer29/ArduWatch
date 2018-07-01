#ifndef ADWatch_h
#define ADWatch_h

#include <Arduino.h>
#include <TimeLib.h>
#include "Clock.h"
#include "Compass.h"
#include "Speedometer.h"
#include "Flashlight.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GPS.h>

/* ADWatch
   -----------
	-The union of all feature classes.
	
*/
class ADWatch{
	public:
		
		//Attributes
		
		//Implements
		Adafruit_NeoPixel ring;
		//Adafruit_GPS gps;	
		
		//Features
		Clock* clock;
		Compass* compass;
		Speedometer* speedo;
		Flashlight* light;

		//Methods

		//Initializers
		//ADWatch(Adafuit_GPS, Adafruit_NeoPixel); //For when GPS is incorperated
		ADWatch(time_t, Adafruit_NeoPixel);
		
		//Views (Features)
		void showTime(time_t);//Can probably be void when GPS gets here!
		void showSpeed(float);
		void showHeading(float);
		void showLight(void);
		void showStrobe(uint8_t);

		void setPixels(uint32_t);
		//Flow tools
		void flourish(uint32_t,uint32_t);
		void clearRing(void);
	
	/*
		In the future, it may be a good refactor to make all of our features private and store
		the colours we need to pull from them in an internal array or something. If we need 	
		methods (which we shoudln't) we can just keep them public.
	*/
	//private:

};

#endif
