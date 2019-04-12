/*
Author: Ben Lewis
Date: May 16th, 2018

Synopsis: 

*/

#include "Compass.h"



//****************************************************************************************
//Compass//
//****************************************************************************************

/*
 *Compass()
 *
 *	precond: 
 * 	postcond: 
 *
 *	Paramaters: 
 *
 *	Synopsis: 
 */
Compass::Compass(){
	needle = new Compass_Needle();
	magnet = new Compass_Magnet(0);

	curHeadIdx = magnet->getHeadingIndex();
	prevHeadIdx = -1;
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
void Compass::placeNeedle(uint8_t headingIdx,Adafruit_NeoPixel* ring){
	
	//Regular offset Assignment
	ring->setPixelColor(headingIdx,needle->needleColour);
	ring->setPixelColor(0,needle->northColour); 

	//Check for overlap
	if (headingIdx == 0)
		ring->setPixelColor(0,needle->getAverageCross(needle->needleColour,needle->northColour));

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
void Compass::removeTail(float h,Adafruit_NeoPixel* ring){

	//Store old Heading	
	prevHeadIdx = magnet->getHeadingIndex();
	//Grab New Time
	magnet->updateHeading(h);
	//Reset Current heading
	curHeadIdx = magnet->getHeadingIndex();

	//If we have a new heading, remove the old one.
	if(curHeadIdx != prevHeadIdx)
		ring->setPixelColor(prevHeadIdx,needle->blank);
	
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
void Compass::trackHeading(float h,Adafruit_NeoPixel* ring){
	
	//Remvoe tail also handels update now.
	removeTail(h,ring);
	
	//Assign colours to the appropriate indicies.	
	placeNeedle(magnet->getHeadingIndex(),ring);
	
	//magic 11
	if(curHeadIdx != 11)
		ring->setPixelColor(11,needle->blank);
	//Display 
	ring->show();
	
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
void Compass::setCompassHeading(float newHeading, Adafruit_NeoPixel* ring){

	//Set new time and pass it to Gears
	magnet->updateHeading(newHeading);
		
	//Remove tail
	ring->clear();
}

