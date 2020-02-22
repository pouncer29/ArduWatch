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
	#include <SoftwareSerial.h>
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
		Adafruit_GPS* gps;
		int adjust;
		//Methods
		GPSTools(Adafruit_GPS*,int32_t);
		time_t grabTime();
		float grabSpeed(void);
		float grabHeading(void);
		void update(void);
		bool hasFix(void);

	private:
		//Methods
		int32_t tzAdjust(float);

};

#endif
		
		
