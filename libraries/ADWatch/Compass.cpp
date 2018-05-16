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
Compass::Compass(float h, Adafruit_NeoPixel neoP){
	curHeading = h;
	strip = neoP;
	needle = new Needle(neoP);
	magnet = new Magnet(h);

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
void Compass::placeNeedle(uint8_t headingIdx){
	
	//Regular offset Assignment
	needle->ring.setPixelColor(headingIdx,needle->needleColour);
	needle->ring.setPixelColor(0,needle->northColour); 

	//Check for overlap
	if (headingIdx == 0)
		needle->ring.setPixelColor(0,needle->getAverageCross(needle->needleColour,needle->northColour));
		
	//Remove Tail
//	removeTail(headingIdx);

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
void Compass::removeTail(float h){

	//Store old Heading	
	prevHeadIdx = magnet->getHeadingIndex();
	//Grab New Time
	magnet->updateHeading(h);
	//Reset Current heading
	curHeadIdx = magnet->getHeadingIndex();

	//If we have a new heading, remove the old one.
	if(curHeadIdx != prevHeadIdx)
		needle->ring.setPixelColor(prevHeadIdx,needle->blank);
	
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
void Compass::trackHeading(float h){
	
	//Remvoe tail also handels update now.
	removeTail(h);
	
	//Assign colours to the appropriate indicies.	
	placeNeedle(magnet->getHeadingIndex());
	
	//magic 11
	if(curHeadIdx != 11)
		needle->ring.setPixelColor(11,needle->blank);
	//Display 
	needle->ring.show();
	
	needle->clearStrip();
	
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
void Compass::setCompassHeading(float newHeading){

	//blank the strip
	//face->clearStrip();
	//face->ring.show();
	
	//Set new time and pass it to Gears
	//setTime(hr,min,0,15,4,2012);
	magnet->updateHeading(newHeading);
		
	
	//Track the time being set.
	//TrackTime really just tracks hand placement. It is ideal for this!
	//trackTime(localTime);
	
	//Remove tail
	needle->clearStrip();
}

