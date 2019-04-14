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
	prev_adjust = -7; // My Local TZ
}


//Handles the UTC timezones with our given degrees
int GPSTools::tzAdjust(float deg, char16_t EW){

	int8_t	adjustment;
	if(deg > 180)
		return -50;

	// The offset is just integer division withthe blood thing
	adjustment = deg / 15;
	//If we are west of Greenwitch, we must subtract the adjustment, else add
	if (EW == 'W')
		return  adjustment * -1;
	else if (EW == 'E')
		return adjustment;
	else
		return -50;

	}

/* grabTime()
	precond: gps is initialized
	postcond: a time_t of the current time is produced

	Parameters: None

	Synopsis: Takes apart the GPS time and puts it into a fresh time_t object

	return: the current time according to the GPS module as a time_t
*/
time_t GPSTools::grabTime(void){
	int8_t adjustment;
	if(gps->fix) {
		adjustment = tzAdjust(gps->longitudeDegrees, gps->lon);
		prev_adjust = adjustment;
	}
	else
		adjustment = prev_adjust;

	setTime((gps->hour + adjustment),gps->minute,gps->seconds,gps->day,gps->month,gps->year);
	return now();
}

/* grabSpeed()
	precond: gps has been initialized and we have a fix
	postcond: speed is produced as a float from GPS
	
	Parameters: none
	
	Synopsis: grabs speed reading in knots from gps, converts and returns it as a kmph value

	return: a float from the GPS module readings
*/
float GPSTools::grabSpeed(void){
	if(gps->fix)
		return gps->speed * 1.852;
	else
		return 0;
}

/* grabHeading()
	precond: GPS readings are initialized
	postcond: None

	Parameters: None
	
	Synopsis: produces an array index value from a GPS reading

	return: nothing
*/
float GPSTools::grabHeading(void){
	if(gps->fix)
		return gps->angle;
	else
		return 0;

}

/* hasFix()
	precond: GPS is initialized
	postcond: the tracked variable is updated

	Parameters: None
	
	Synopsis: Keeps the tracked gps reading up to date

	return: nothing
*/
bool GPSTools::hasFix(void){
	return gps->fix;
}

