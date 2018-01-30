#ifndef ADWatch_h
#define ADWatch_h

#include <Arduino.h>
#include <TimeLib.h>
#include <Adafruit_NeoPixel.h>
#include <Face.h>
#include <Gears.h>


class ADWatch{
		
	public:
		//Attributes
		//Adafruit_NeoPixel ring;
		Face face(Adafruit_NeoPixel);
		Gears gears(time_t);
		//time_t trackMe;

	//Methods
		ADWatch(time_t,Adafruit_NeoPixel);
		void trackTime(time_t);
};

#endif
