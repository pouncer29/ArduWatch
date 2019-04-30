#ifndef ADWatch_h
#define ADWatch_h

#include <Arduino.h>
#include <TimeLib.h>
#include <Clock.h>
#include <Compass.h>
#include <Speedometer.h>
#include <Flashlight.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GPS.h>
#include <GPSTools.h>


/* src
   -----------
	-The union of all feature classes.
	
*/
class ADWatch{
	public:
		
		//Attributes
		uint32_t clock_colour;
		uint32_t speedo_colour;
		uint32_t compass_colour;
		uint32_t light_colour;
		uint32_t party_colour;
		uint32_t error_colour;
		uint32_t blank;
		
		//Implements
		Adafruit_NeoPixel* ring;
		/*
		GPSTools* parser;
		Adafruit_GPS* gps;
		*/
		//Features
		Clock* clock;
		Compass* compass;
		Speedometer* speedo;
		Flashlight* light;

		//Methods

		//Initializers
		//src(Adafuit_GPS, Adafruit_NeoPixel); //For when GPS is incorperated
		ADWatch(Adafruit_NeoPixel*);
		
		//Views (Features)
		void showTime(time_t);//Can probably be void when GPS gets here!
		void showSpeed(float);
		void showHeading(float);
		void showLight();
		void showStrobe(uint8_t);
		void showError(uint32_t);

		//Flow tools
		void flourish(uint32_t,uint32_t);
		void clearRing(void);
		void setPixels(uint32_t);
		void refresh(void);
	
	/*
		In the future, it may be a good refactor to make all of our features private and store
		the colours we need to pull from them in an internal array or something. If we need 	
		methods (which we shoudln't) we can just keep them public.
	*/

};

#endif
