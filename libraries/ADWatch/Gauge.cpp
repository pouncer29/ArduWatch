/*
Author: Ben Lewis
Date: May 25th, 2018

Synopsis: Gauge: The means of moving a compass needle.

*/

#include "Gauge.h"

//****************************************************************************************
//Gauge//
//****************************************************************************************

/*
 *Gauge()
 * precond: none
 * postcond: a Dial object is created
 * 
 * paramaters: 
 * 
 * 
 */
Gauge::Gauge(float kn){
	curSpeed = kn;	
}

float Gauge::getCurSpeed(void){
	return curSpeed * 1.852;//Conversion factor from knots to Kilometers/hr
}


uint8_t Gauge::getSpeedIndex(void) {
	float speed = getCurSpeed();
	uint8_t idx = 0;

	if (speed <= 120)
		idx= -1 * ((-1 * speed/20) - 6);
	else
		idx = (speed/20) - 6;
	return idx;
}

void Gauge::updateSpeed(float newSpeed){
	curSpeed = newSpeed;
}



	
