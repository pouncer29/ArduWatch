/*
Author: Ben Lewis
Date: February 6th

Synopsis: Clock_Gears for the watch

*/

#include "Clock_Gears.h"

//****************************************************************************************
//GEARS//
//****************************************************************************************

/* Clock_Gears()
   precond: none
   postcond: a Clock_Gears object is created
   
   paramaters: time_t* t - a pointer to the time we need to track
   
 	return: a New gears object that tracks time t  
 */
Clock_Gears::Clock_Gears(){
	curTime = now();
}

/* getHourIndex()
   precond: curTime is set
   postcond: none
   
   Synopsis: Accesses the hour of the time object we are tracking and use % 12 to get
   			 the appropriate index for the hour hand.
  
   return: Array index for the Hour hand
 */
uint8_t Clock_Gears::getHourIndex(void){
	return hour(curTime) % 12;
}

/* getMinuteIndex()
   pecond: curtime is set
   postcond: none
   
   Synopsis: Accesses the minute of the time we are tracking and rely on integer division to give us a 
   			 valid hand position/array index.
  
   return: Array index for the Minute hand
 */
uint8_t Clock_Gears::getMinuteIndex(void){
	return minute(curTime)/5;
}

/* getSecondIndex()
   precond: curtime is set
   postcond: none
   
   Synopsis: Accesses the second of the time we are tracking and uses integer division to determine a 
   			 valid hand position/array index.i
  
   return: Array index for the seconds hand 
 */
uint8_t Clock_Gears::getSecondIndex(void){
	return second(curTime)/5;
}

/*
 getCurTime()
	- A simple getter method for the private attribute 'curTime'
 */
time_t Clock_Gears::getCurTime(void){
	return curTime;
}

/* updateTime()
   precond: none
   postcond: Clock_Gears curTime attribute has been updated
  
   Paramaters: newTime - the time_t object we will update our gears to.
  
   Synopsis: Changes the Clock_Gears time value to a specified value.
  
   return: nothing
 */
void Clock_Gears::updateTime(time_t newTime){
	curTime = newTime;
}

