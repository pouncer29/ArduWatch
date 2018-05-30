#ifndef ADWatch_h
#define ADWatch_h

#include <Arduino.h>
#include <TimeLib.h>
#include "Clock.h"
#include "Compass.h"
#include "Speedometer.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GPS.h>

/* ADWatch
   -----------
	
*/
class ADWatch{
	public:
		
		//Attributes
		
		//Implements
		Adafruit_NeoPixel ring;
		//Adafruit_GPS gps;	
		Compass* compass;
		Speedometer* speedo;

		//****Methods*****/
		//Initializers
		//ADWatch(Adafuit_GPS, Adafruit_NeoPixel); //For when GPS is incorperated
		ADWatch(time_t, Adafruit_NeoPixel);
		
		//Views
		void showTime(time_t);//Can probably be void when GPS gets here!
		void showSpeed(float);
		void showHeading(float);
	
		//Internal Features
		void flashlight(void);
		void strobe(bool);
		void setPixels(uint32_t);

		//Flow tools
		void flourish(uint32_t,uint32_t);
		void clearRing(void);
		
	private:
		//Features
		Clock* clock;
	//	Speedometer* speedo;
	//	Compass* compass;

};

#endif
