/**
	Author: Ben Lewis
	Date: July 27th, 2018
	Synopsis: Implementation for GPS interacting functions
*/

#include <GPSTools.h>

/** GPSTools()
   precond: none
   postcond: none
   parametes: the reference to our GPS module
   
	Synopsis: pulls info from the gps and transforms them to meaningful array indicies

   return: nothing
 */
GPSTools::GPSTools(int32_t adj){
	this->adjust = adj;
}

//Handles the UTC timezones with our given degrees
int32_t GPSTools::tzAdjust(float deg){

	int32_t	adjustment = 0;
	///The adjustment +/- 1 is because of my goofed timezone. It should maybe be removed.
	if(deg < 0) {
		adjustment = ((-1 * deg) / 15) * -1;
		return adjustment+1; //Saskatoon is -6, this fn gives -7... So I cheated
	}
	else {
		return adjustment = deg / 15;
	}
}

/** grabTime()
	precond: gps is initialized
	postcond: a time_t of the current time is produced

	Parameters: gps - the Adafruit GPS to pull the time off of 

	Synopsis: Takes apart the GPS time and puts it into a fresh time_t object

	return: the current time according to the GPS module as a time_t
*/
time_t GPSTools::grabTime(Adafruit_GPS gps){
	uint8_t hour = gps.hour;
	uint8_t minute = gps.minute;
	uint8_t seconds = gps.seconds;

	//If we are about to set an invalid time, return the current time.
	if(hour > 24 || minute > 60 || seconds > 60){
		return now();
	}

	int32_t adj = tzAdjust(gps.longitudeDegrees);
	if(adj != this->adjust){
			this->adjust = adj;
	}
	///this is Jarrods magic 24hour converter. It works similar to how the 24 hour converter works in the clock app
	hour = (((gps.hour + adjust)%24)+24) % 24;
	setTime(hour,minute,seconds,gps.day,gps.month,gps.year);

	return now();
}

/** grabSpeed()
	precond: gps has been initialized and we have a fix
	postcond: speed is produced as a float from GPS
	
	Parameters: gps - the Adafruit_GPS we will pull the speed form
	
	Synopsis: grabs speed reading in knots from gps, converts and returns it as a kmph value

	return: a float from the GPS module readings
*/
float GPSTools::grabSpeed(Adafruit_GPS gps){
	float speed = gps.speed * 1.852;
	if(speed < 0)
		return 0;	
	else if (gps.speed > 200)
		return 200;
	else
		return speed;
}

/** grabHeading()
	precond: GPS readings are initialized
	postcond: None

	Parameters: gps - The AdafruitGPS we will pull the heading data from
	
	Synopsis: produces an array index value from a GPS reading

	return: nothing
*/
float GPSTools::grabHeading(Adafruit_GPS gps){
	float angle = gps.angle;
	if(angle < 0)
		return 0;
	else if(angle > 360)
		return 0;
	else
		return angle;

}

/** hasFix()
	precond: GPS is initialized
	postcond: the tracked variable is updated

	Parameters: gps - The AdafruitGPS we will pull the fix data from
	
	Synopsis: Keeps the tracked gps reading up to date

	return: nothing
*/
bool GPSTools::hasFix(Adafruit_GPS gps){
	return gps.fix;
}

