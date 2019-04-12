/*
Author: Ben Lewis
Date: May 16th, 2018

Synopsis: Compass_Magnet: The means of moving a compass needle.

*/

#include "Compass_Magnet.h"

//****************************************************************************************
//Compass_Magnet//
//****************************************************************************************

/* Compass_Magnet()
   precond: none
   postcond: a Gears object is created
   
   paramaters: time_t* t - a pointer to the time we need to track
   
   
 */
Compass_Magnet::Compass_Magnet(float h){
	curHeading = h;	
}
/* getCurHeading()
	- A simple getter method for the private attribute 'curHeading'
 */
float Compass_Magnet::getCurHeading(void){
	return curHeading;
}

/* updateHeading()
   precond: none
   postcond: Heading curHeading attribute has been updated
  
   Paramaters: newHeading - a float representing the direction we will update our heading to
  
   Synopsis: Changes the Compass_Magnets heading  to a specified value
  
   return: nothing
 */
void Compass_Magnet::updateHeading(float newHeading){
	curHeading = newHeading;
}

/* getHeadingIndex()
   precond: Heading has a value
   postcond: none
   
   Synopsis: Takes in a floating point heading in range [0,360] and produces the array offset [0,11] that it maps to.
			 in intervals of 30 degrees
   
   return: nothing.
 */
uint8_t Compass_Magnet::getHeadingIndex(void){
	if(curHeading >= 360)
		return 0; //TODO throw an exception. the magic 11 bug will eat you!

	return uint8_t(curHeading/30);
}








	
