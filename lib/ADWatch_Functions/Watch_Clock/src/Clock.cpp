/*
Author: Ben Lewis
Date: May 10th, 2018

Synopsis: The Controller for the clock. passes read data to gears to generate an index to be shown on the
  			ring via the Clock_Face.

*/

#include "Clock.h"



//****************************************************************************************
//Clock
//****************************************************************************************

/** Clock()
  	@Synopsis: The Controller for the clock feature parses data in Gears, Displays in Face
 */
Clock::Clock(){
	face = new Clock_Face();
	gears = new Clock_Gears();
}

/** placeHands()
   @precond:  None
   @postcond: Color values are assigned to their designated indicies (times)
  
   @param: hrIdx - representing the position of the hour hand on our ring.
   @param: minIdx - representing the position of the minute hand on our ring.
   @param: secIdx - representing the position of the second hand on our ring.
   @param  ring - the NeoPixel ring to display the time on.
  
   @Synopsis: Grabs the current time from gears and uses it to modify the minute colour. then
   		     assigns the appropriate colour of hand to each 'hand' or 'index' in the ring.
  	         in the case that the hands overlap we call getAverageCross() with the two (or sometimes
  	         three) colour values of the hands that intersect there.

 */
void Clock::placeHands(uint8_t hrIdx,uint8_t minIdx,uint8_t secIdx,Adafruit_NeoPixel* ring){

	//Grab our modified minute colour.
	face->modMinColour(gears->getCurTime(),ring); 

	//Assign colours accordingly
	//Base case: No Overlap regular
	ring->setPixelColor(hrIdx,face->hrColour);
	ring->setPixelColor(minIdx,face->minColour);
	ring->setPixelColor(secIdx,face->secColour);

	// Otherwise: If Hands Cross, Their indicies will be the same so I average their set colours.
	//This particularly nasty block is only so nasty because I take the average of an average. will work on shortening
	if (secIdx == minIdx && minIdx == hrIdx)
		ring->setPixelColor(minIdx,face->getAverageCross((face->getAverageCross(face->secColour,face->minColour)),face->hrColour));
	else if(secIdx == minIdx)
		ring->setPixelColor(minIdx,face->getAverageCross(face->secColour,face->minColour));
	else if(secIdx == hrIdx)
		ring->setPixelColor(hrIdx,face->getAverageCross(face->secColour,face->hrColour));
	else if(hrIdx == minIdx)
		ring->setPixelColor(hrIdx, face->getAverageCross(face->hrColour,face->minColour));
	
	//Remove Tail
	removeTail(hrIdx-1,hrIdx,minIdx,secIdx,ring);
	removeTail(minIdx-1,hrIdx,minIdx,secIdx,ring);
	removeTail(secIdx-1,hrIdx,minIdx,secIdx,ring);
	
	ring->show();	
	return;
}

/** removeTail()
   @precond: None
   @postcond: Removed the residual illumination left by passing hands
  
   @param: uint8_t's tailIdx - the index who's tail will remove
   @param: hrIdx - the index occupied by hour hand
   @param: minIdx - the index occupied by minute hand
   @param: secIdx - the index occupied by the seconds hand
   @param: ring - the NeoPixel ring to display the time on.

   @Synopsis: Goes to an index, if it isn't important, blank it.
*/
void Clock::removeTail(uint8_t tailIdx,uint8_t hrIdx,uint8_t minIdx, uint8_t secIdx,
						Adafruit_NeoPixel* ring){
	
	//At 12:00 v !@12.
	tailIdx = tailIdx % 12;
	
	//Don't blank important indicies.
	if (tailIdx == hrIdx || tailIdx == minIdx || tailIdx == secIdx)
		return;

	//Blank the tail
	ring->setPixelColor(tailIdx,face->blank);
	return;
}

/** trackTime()
   @precond: none
   @postcond: ring is activated to show the current time.
  
   @param: t - representing the time we will be tracking.
   @param: ring - the NeoPixel ring to display the time on.

   @Synopsis: over-writes whatever the previous time was using 'updateTime()' and then with
   		     the updated time, it places, and assigns colours to the hands before showing the
   		  	 time as a set of up to 3 coloured led's on the ring!
 */
void Clock::trackTime(time_t t,Adafruit_NeoPixel* ring){
	
	//Grab New Time
	gears->updateTime(t);

	//Assign colours to the appropriate indicies.	
	placeHands(gears->getHourIndex(),gears->getMinuteIndex(),gears->getSecondIndex(),ring);

	//Display 
	ring->show();
}

/** setWatchTime()
  	@precond: hr & min are > 0, localTime is set
  	@postcond: localTime tracks the hour and minute that are given.
  
    @param: uint8_t hr - that will be our hour value.
    @param: uint8_t min -  that will be our minute value.

    TODO maybe add a year for when we get the gps. but I don't think that will change anything.
    @param: time_t localTime - that is we will track while setting.
    @param: ring - the NeoPixel ring to display the time on.

  	@Synopsis: Updates the watch's tracking time to the given hour and minute.
 */
void Clock::setWatchTime(uint8_t hr, uint8_t min, time_t localTime, Adafruit_NeoPixel* ring){

	//blank the strip
	ring->clear();
	ring->show();
	
	//Set new time and pass it to Gears
	setTime(hr,min,0,15,4,2012);
	gears->updateTime(now());
	
	//Track the time being set.
	//TrackTime really just tracks hand placement. It is ideal for this!
	trackTime(localTime,ring);
	
	//Remove tail
	ring->clear();
}

