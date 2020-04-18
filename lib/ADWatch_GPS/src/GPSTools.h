/*
	Author: Ben Lewis 
	Date: July 26th, 2018
	Synopsis: A toolkit to grab any and all info we may need from the gps
*/

#ifndef GPSTools_h
#define	GPSTools_h

#ifndef CI
	#include <Adafruit_GPS.h>
	#include <TimeLib.h>
	#include <Arduino.h>
#else
	#include <TimeLib_MOCK.h>
	#include <Adafruit_GPS_MOCK.h>
	#include <Arduino_MOCK.h>
#endif

/** GPSTools
   --------------
	- A toolkit class that should be imported into watch_function classes to provide necessary
	  GPS data
*/
class GPSTools{
	
	public:
		//Attributes
		int adjust;
		//Methods
		GPSTools(int32_t);
		int grabTime(time_t,float);
		float grabSpeed(Adafruit_GPS);
		float grabHeading(Adafruit_GPS);
		bool hasFix(Adafruit_GPS);

	private:
		//Methods
		int32_t tzAdjust(float);

};

#endif
		
		
