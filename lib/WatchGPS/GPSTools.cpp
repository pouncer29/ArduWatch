/*
	Author: Ben Lewis
	Date: July 27th, 2018
	Synopsis: Implementation for GPS interacting functions
*/

#include "GPSTools.h"

/* GPSTools()
   precond: none
   postcond: none
   parametes: the reference to our GPS module
   
	Synopsis: pulls info from the gps and transforms them to meaningful array indicies

   return: nothing
 */
GPSTools::GPSTools(Adafruit_GPS* myGPS){
	gps = myGPS;
	prev_adjust = 0;
}


//Handles the UTC timezones with our given degrees
int GPSTools::tzAdjust(float deg, char16_t EW){

	uint8_t	adjustment;
	float upperBound = deg + 7.5;
	float lowerBound = deg -7.5;

	switch (adjustment){
		case (upperBound <= UTC_0_H && UTC_0_L > 7.5) :
			adjustment = UTC_0;
			break;
	}





/* grabTime()
	precond: gps is initialized
	postcond: a time_t of the current time is produced
	
	Parameters: None
	
	Synopsis: Takes apart the GPS time and puts it into a fresh time_t object

	return: the current time according to the GPS module as a time_t
*/
time_t GPSTools::grabTime(void){
	setTime(gps.hour,gps.minute,gps.seconds,gps.day,gps.month,gps.year)		
	return now();
}

/* grabTime()
	precond: gps has been initialized
	postcond: speed is produced as a float from GPS
	
	Parameters: none
	
	Synopsis: grabs speed reading in knots from gps, converts and returns it as a kmph value

	return: a float from the GPS module readings
*/
float grabSpeedKMPH(void){
	return gps.speed * 1.852;
}

/* grabHeading()
	precond: GPS readings are initialized
	postcond: None

	Parameters: None
	
	Synopsis: produces an array index value from a GPS reading

	return: nothing
*/
float grabHeading(void)
	return gps.angle
}

/* update()
	precond: GPS is initialized
	postcond: the tracked variable is updated

	Parameters: None
	
	Synopsis: Keeps the tracked gps reading up to date

	return: nothing
*/
void update(void){
	return;
}

