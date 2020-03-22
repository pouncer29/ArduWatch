/*
Author: Ben Lewis
Date: May 25th, 2018

Synopsis: the implementation for Speed_Gauge.h

*/

#include "Speed_Gauge.h"

//****************************************************************************************
//Speed_Gauge
//****************************************************************************************

/** Speed_Gauge()
	@precond: speed given is in kmph and gt 0
    @postcond: a Speed_Gauge object is created

    @param: km - a speed in kmph we will initialize to.

	@synopsis: initializes a Speed_Gauge object

 */
Speed_Gauge::Speed_Gauge(float km){
	curSpeed = km;	
}

/** getCurSpeed()
	precond: speed is not null
	postcond: none

	paramaters: none

	synopsis: retrieves our currenltly tracked speed in kmph

	return: the current speed in kmph
*/
float Speed_Gauge::getCurSpeed(void){
	return curSpeed;
}

/** getSpeedIndex(void)
	@precond: speed is set
	@postcond: none
	
	@synopsis: returns the speed index deemed appropriate by our hash function to represent
			  our current speed on the watch (6 is 0)

	@return: an array index for the  current speed.
*/
uint8_t Speed_Gauge::getSpeedIndex(void) {
	
	//encapsulate speed and init index
	float speed = getCurSpeed();
	uint8_t idx = 0;

	//Put through hash function based on 20kmph/index indexing from 6 (0)- 4(10).
	if (speed < 120)
		idx= -1 * ((-1 * speed/20) - 6);
	else
		idx = (speed/20) - 6;
	return idx;
}

/** updateSpeed()
	@precond: given speed is -gte 0
	@postcond: internal speed is updated
	
	@parameters: newSpeed - the speed that will become our tracked speed

	@synopsis: resets our tracked speed to newSped
*/
void Speed_Gauge::updateSpeed(float newSpeed){
	curSpeed = newSpeed;
}



	
