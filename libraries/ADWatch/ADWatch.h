#ifndef ADWatch_h
#define ADWatch_h

#include <Arduino.h>
#include <TimeLib.h>
#include "Clock.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GPS.h>

/* ADWatch
   -----------
	
*/
class ADWatch{
	public:
		
		//Attributes
		//Implements
		Adafruit_NeoPixel strip;
		Adafruit_GPS gps;	
		
		/****Methods*****/
		//Initializers
		ADWatch(Adafuit_GPS,Adafruit_NeoPixel);
		ADWatch(time_t,Adafruit_NeoPixel);
		
		//Views
		void showTime(void);
		void showSpeed(void);
		void showHeading(void);
		void flashlight(void);

		//Flow tools
		void flourish(void);
		void clearStrip(void);

		//Component init tools
		void initRing(uint8_t);

	private:
		//Features
		Clock* clock;
		//Speedometer* speedo;
		//Compass* compass;
		//FlashLight* flash;

};

#endif
