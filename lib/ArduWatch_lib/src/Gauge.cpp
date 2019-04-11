/*
Author: Ben Lewis
Date: May 25th, 2018

Synopsis: the implementation for Gauge.h

*/

#include "Gauge.h"

//****************************************************************************************
//Gauge//
//****************************************************************************************

/* Gauge()
	precond: speed given is in kmph and gt 0
    postcond: a Gauge object is created
   
    paramaters: km - a speed in kmph we will initialize to.
   
	synopsis: initializes a Gauge object

	return: a new Gauge object
 */
Gauge::Gauge(float km){
	curSpeed = km;	
}

/* getCurSpeed()
	precond: speed is not null
	postcond: none

	paramaters: none

	synopsis: retrieves our currenltly tracked speed in kmph

	return: the current speed in kmph
*/
float Gauge::getCurSpeed(void){
	return curSpeed;
}

/* getSpeedIndex(void)
	precond: speed is set
	postcond: none
	
	parameters: none

	synopsis: returns the speed index deemed appropriate by our hash function to represent
			  our current speed on the watch (6 is 0)

	return: an array index
*/
uint8_t Gauge::getSpeedIndex(void) {
	
	//encapsulate speed and init index
	float speed = getCurSpeed();
	uint8_t idx = 0;

	//Put through hash function based on 20kmph/index indexing from 6 (0)- 4(10).
	if (speed <= 120)
		idx= -1 * ((-1 * speed/20) - 6);
	else
		idx = (speed/20) - 6;
	return idx;
}

/* updateSpeed()
	precond: given speed is -gt 0
	postcond: internal speed is updated
	
	parameters: newSpeed - the speed that will become our tracked speed

	synopsis: resets our tracked speed to newSped

	return: nothing
*/
void Gauge::updateSpeed(float newSpeed){
	curSpeed = newSpeed;
}



	
