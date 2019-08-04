/*
	Author: Ben Lewis 
	Date: July 26th, 2018
	Synopsis: A toolkit to grab any and all info we may need from the gps
*/

#ifndef GPSTools_h
#define	GPSTools_h

#include <Adafruit_GPS.h>
#include <TimeLib.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

/* GPSTools
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
		GPSTools(Adafruit_GPS*);
		time_t grabTime();
		float grabSpeed(void);
		float grabHeading(void);
		void update(void);
		bool hasFix(void);
		void gpsSetup();

	private:
		//Methods
		int tzAdjust(float, char16_t);

};

#endif
		
		
