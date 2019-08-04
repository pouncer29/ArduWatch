/*
	Author: Ben Lewis
	Date: July 27th, 2018
	Synopsis: Implementation for GPS interacting functions
*/

#include <GPSTools.h>

/* GPSTools()
   precond: none
   postcond: none
   parametes: the reference to our GPS module
   
	Synopsis: pulls info from the gps and transforms them to meaningful array indicies

   return: nothing
 */
GPSTools::GPSTools(Adafruit_GPS* myGPS){
	this->gps = myGPS;
	this->prev_adjust = -6; // My Local TZ

	/*Setup from GPS example*/
}

//Handles the UTC timezones with our given degrees
int GPSTools::tzAdjust(float deg, char16_t EW){

	int8_t	adjustment;
	if(deg > 180)
		return -50;

	// The offset is just integer division with the blood thing
	adjustment = deg / 1500;
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
time_t GPSTools::grabTime(Adafruit_GPS adGps){
	int hour;
	//Arduino is super weird. If you don't set it here, the instance will stay OMG it's a pointer issue.

	///If we are West of greenwitch, we do mathamagic to handle - adjustments.
	if(this->prev_adjust < 0){
		if(adGps.hour >= (prev_adjust * -1)) {
			hour = adGps.hour - prev_adjust;
		} else{
			hour = adGps.hour + (prev_adjust * -1) + 12;
		}
	///Otherwise, we are East of grenwhich and must handle + adjustents
	}else{
		int adjustDiff = 12 - prev_adjust;
		if(adGps.hour >= (12+adjustDiff)){
			hour = adGps.hour - (12 + adjustDiff);
		} else{
			hour = adGps.hour + prev_adjust;
		}
	}

	/**
	 * Both scenarios may end up creating negative but correct values, negate them
	 */
	if(hour < 0){
		hour *= -1;
	}


	setTime(hour,adGps.minute,adGps.seconds,adGps.day,adGps.month,adGps.year);

	time_t time = now();
	return time;
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

