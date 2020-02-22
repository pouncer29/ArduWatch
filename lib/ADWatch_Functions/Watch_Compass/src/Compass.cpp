/*
Author: Ben Lewis
Date: May 16th, 2018

Synopsis: Implementation for the compass. Controller for Needle and Magnet

*/

#include <Compass.h>

//****************************************************************************************
//Compass
//****************************************************************************************

/** Compass()
  	@Synopsis: Creates a needle and magnet for our Compass and initializes indicies
 */
Compass::Compass(){
	needle = new Compass_Needle();
	magnet = new Compass_Magnet();

	curHeadIdx = magnet->getHeadingIndex();
	prevHeadIdx = -1;
}

/** placeNeedle()
  @precond: ring is intitalized, heading is in range [0,11]
  @postcond: pixel color is set for the proper indicies.

  @param: uint8_t headingIdx - the index of the angle we are measuring.
  @param: NeoPixel* ring - the ring we will set our index colours on.

  Synopsis: Determines whici indicies need to be set for colours and which
            colours need be set.

  return: nothing

 */
void Compass::placeNeedle(uint8_t headingIdx, Adafruit_NeoPixel* ring){
	
	//Regular offset Assignment
	ring->setPixelColor(headingIdx,needle->needleColour);
	ring->setPixelColor(0,needle->northColour); 

	//Check for overlap
	if (headingIdx == 0)
		ring->setPixelColor(0,needle->getAverageCross(needle->needleColour,needle->northColour));

	return;
}

/** removeTail()
 
  @precond:none
  @postcond: Removed the residual illumination left by passing hands
 
  @param: uint8_t tailIdx - the index who's tail e will remove
  @param: NeoPixel* ring - the ring to set colours on
 
  @Synopsis: Goes to an index, if it isn't important, blank it.
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

/** trackHeading()
  @precond: none
  @postcond: ring is activated to show the current heading.
 
  @param: float h - the heading we will be tracking
  @param: NeoPixel* - the ring we will set the colours on
 
  @Synopsis: Given a value in degrees, determine an the proper indicies to
            display and their colours to display compass heading to the watch
 
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

/** setCompassHeading()
 	@precond: ring is initialized
 	@postcond: the heading for the watch has been updated
 
 	@param: float newHeading - heading read from the watch
    @param: NeoPixel* ring - the ring we will clear once the heading has been set.
 
 	@Synopsis: Updates the watch's tracking time to the given hour and minute.
  
 */
void Compass::setCompassHeading(float newHeading, Adafruit_NeoPixel* ring){

	//Set new time and pass it to Gears
	magnet->updateHeading(newHeading);
		
	//Remove tail
	ring->clear();
}

