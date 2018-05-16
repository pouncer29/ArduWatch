/*
Author: Ben Lewis
Date: May 16th, 2018

Synopsis: Magnet: The means of moving a compass needle.

*/

#include "Magnet.h"

//****************************************************************************************
//Magnet//
//****************************************************************************************

/*
 *Magnet()
 * precond: none
 * postcond: a Gears object is created
 * 
 * paramaters: time_t* t - a pointer to the time we need to track
 * 
 * 
 */
Magnet::Magnet(float h){
	curHeading = h;	
}
/*
 getCurTime()
	- A simple getter method for the private attribute 'curTime'
 */
float Heading::getCurHeading(void){
	return curHeading;
}

/*
 *updateHeading()
 * precond: none
 * postcond: Heading curHeading attribute has been updated
 *
 * Paramaters:
 *     float newHeading - the direction we will update our heading to
 *
 * Synopsis: Changes the Magnets heading  to a specified value
 *
 * return: nothing
 */
void Magnet::updateHeading(float newHeading){
	curHeading = newHeading;
}

/*getHeadingIndex()
 * precond: Heading has a value
 * postcond: none
 * 
 * Synopsis: Takes in a floating point heading in range [0,360] and produces an array offset [0,11] that it maps to.
 * 
 * return: nothing.
 */
uint8_t Magnet::getHeadingIndex(void){
	return curHeading/30;
}








	
