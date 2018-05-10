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
		Adafruit_NeoPixel ring;
		//Adafruit_GPS gps;	
		
		//****Methods*****/
		//Initializers
		//ADWatch(Adafuit_GPS, Adafruit_NeoPixel); //For when GPS is incorperated
		ADWatch(time_t, Adafruit_NeoPixel);
		
		//Views
		void showTime(time_t);//Can probably be void when GPS gets here!
		void showSpeed(void);
		void showHeading(void);
		void flashlight(void);

		//Flow tools
		void flourish(void);
		void clearRing(void);


	private:
		//Features
		Clock* clock;
		//Speedometer* speedo;
		//Compass* compass;
		//FlashLight* flash;

};

#endif
