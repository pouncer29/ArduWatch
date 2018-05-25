/*
Author: Ben Lewis
Date: May 25th, 2018

Synopsis: 

*/

#include "Speedometer.h"



//****************************************************************************************
//Speedometer//
//****************************************************************************************

/*
 *Speedometer()
 *
 *	precond: 
 * 	postcond: 
 *
 *	Paramaters: 
 *
 *	Synopsis: 
 */
Speedometer::Speedometer(float kn, Adafruit_NeoPixel neoP){
	curSpeed = kn;
	strip = neoP;
	dial = new Dial(neoP);
	gauge = new Gauge(kn);

//	curHeadIdx = gauge->getSpeedIndex();
	//prevHeadIdx = -1;
}

/*
 *placeNeedle()
 * precond: none
 * postcond: 
 *
 * Paramaters: 
 *
 * Synopsis: 
 *
 * return: nothing
 *
 */
void Speedometer::setDial(uint8_t headingIdx){
	
	//Regular offset Assignment
	dial->setRegions();
	//Check for overlap
	dial->ring.show();
	//Remove Tail

	return;
}

/*
 *removeTail()
 *
 * precond:none
 * postcond: Removed the residual illumination left by passing hands
 *
 * paramaters: uint8_t's tailIdx - the index who's tail e will remove
 *
 * Synopsis: Goes to an index, if it isn't important, blank it.
 * return: nothing
*/
void Speedometer::removeTail(float h){

	return;
}

/*
 *trackHeading()
 * precond: none
 * postcond: ring is activated to show the current heading.
 *
 * Paramaters: float h - the heading we will be tracking
 *
 * Synopsis:
 *
 * return: nothing 		  
 */
void Speedometer::trackSpeed(float kn){
	
	//Remvoe tail also handels update now.
	
	//Assign colours to the appropriate indicies.	
	setDial(gauge->getSpeedIndex());
	
	//magic 11
	if(curHeadIdx < 11)
		dial->ring.setPixelColor(11,dial->blank);
	
	//Display 
	dial->ring.show();
	
	dial->clearStrip();
	
}

/*setCompassHeading()
 *	precond: 
 *	postcond: 
 *
 *	paramaters:
 *		float newHeading - what we update heading to...
 *
 *	Synopsis: Updates the watch's tracking time to the given hour and minute.	
 * 
 *	return: nothing
 */
void Speedometer::setSpeed(float newSpeed){
	gauge->updateSpeed(newSpeed);
	dial->clearStrip();
}

