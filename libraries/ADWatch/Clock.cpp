/*
Author: Ben Lewis
Date: May 10th, 2018

Synopsis: 

*/

#include "Clock.h"



//****************************************************************************************
//Clockd//
//****************************************************************************************

/*
 *Clock()
 *
 *	precond: timeT is a valid time and Neopixel is instantiated
 * 	postcond: A new ADWatch object is created
 *
 *	Paramaters: 
 *		time_t trackMe - the Time we will track with our Gears
 *		Adafruit_NeoPixel neoP - the neoPixel ring that will serve as our Face
 *
 *	Synopsis: Uses the time to create the *Gears* for the watch and *neoP* to set a face for the watch
 */
Clock::Clock(time_t t, Adafruit_NeoPixel neoP){
	trackMe = t; // Do we really need these things?
	strip = neoP;
	face = new Face(neoP);
	gears = new Gears(t);
}

/*
 *placeHands()
 * precond: none
 * postcond: Color values are assigned to their designated indicies (times)
 *
 * Paramaters: uint_8's hrIdx - representing the position of the hour hand on our ring.
 * 					  minIdx - representing the position of the minute hand on our ring.
 *					  secIdx - representing the postion of the second hand on our ring.
 *
 * Synopsis: Grabs the current time from gears and uses it to modify the minute colour. then
 * 		     assigns the appropriate colour of hand to each 'hand' or 'index' in the ring.
 *	         in the case that the hands overlap we call getAverageCross() with the two (or sometimes
 *	         three) colour values of the hands that intersect there.
 *
 * return: nothing
 *
 */
void Clock::placeHands(uint8_t hrIdx,uint8_t minIdx,uint8_t secIdx){
	
	//Grab our modified minute colour.
	face->modMinColour(gears->getCurTime()); 

	//Assign colours accordingly
	//Base case: No Overlap regualr 
	face->ring.setPixelColor(hrIdx,face->hrColour);
	face->ring.setPixelColor(minIdx,face->minColour);
	face->ring.setPixelColor(secIdx,face->secColour);
	


	// Otherwise: If Hands Cross, Their indicies will be the same so I average their set colours.
	//This particuairly nasty block is only so nasty because I take the average of an average. will work on shortening 
	if (secIdx == minIdx && minIdx == hrIdx)
		face->ring.setPixelColor(minIdx,face->getAverageCross((face->getAverageCross(face->secColour,face->minColour)),face->hrColour));
	else if(secIdx == minIdx)
		face->ring.setPixelColor(minIdx,face->getAverageCross(face->secColour,face->minColour));
	else if(secIdx == hrIdx)
		face->ring.setPixelColor(hrIdx,face->getAverageCross(face->secColour,face->hrColour));
	else if(hrIdx == minIdx)
		face->ring.setPixelColor(hrIdx, face->getAverageCross(face->hrColour,face->minColour));
	
	//Remove Tail
	removeTail(hrIdx-1,hrIdx,minIdx,secIdx);
	removeTail(minIdx-1,hrIdx,minIdx,secIdx);
	removeTail(secIdx-1,hrIdx,minIdx,secIdx);
	
	
	return;
}

/*
 *removeTail()
 *
 * precond:none
 * postcond: Removed the residual illumination left by passing hands
 *
 * paramaters: uint8_t's tailIdx - the index who's tail e will remove
 *			 		   hrIdx - the index occupied by hour hand
 *					   minIdx - the index occupied by minute hand
 *					   secIdx - the inex occupied by the secons hand
 *
 * Synopsis: Goes to an index, if it isn't important, blank it.
 * return: nothing
*/
void Clock::removeTail(uint8_t tailIdx,uint8_t hrIdx,uint8_t minIdx, uint8_t secIdx){
	
	//At 12:00 v !@12.
	//handIdx--; //become the tail!
	tailIdx = tailIdx % 12;
	
	//Don't blank important indicies.
	if (tailIdx == hrIdx || tailIdx == minIdx || tailIdx == secIdx)
		return;

	//Blank the tail
	face->ring.setPixelColor(tailIdx,face->blank);
	return;
}

/*
 *trackTime()
 * precond: none
 * postcond: ring is activated to show the current time.
 *
 * Paramaters: time_t t - representing the time we will be tracking.
 *
 * Synopsis: over-writes whatever the previous time was using 'updateTime()' and then with
 * 		  the updated time, it places, and assigns colours to the hands before showing the
 * 		  time as a set of up to 3 coloured led's on the ring!
 *
 * return: nothing 		  
 */
void Clock::trackTime(time_t t){

	//Grab New Time
	gears->updateTime(t);

	//Assign colours to the appropriate indicies.	
	placeHands(gears->getHourIndex(),gears->getMinuteIndex(),gears->getSecondIndex());
	
	//Display 
	face->ring.show();
}

/*setWatchTime()
 *	precond: hr & min are > 0, localTime is set
 *	postcond: localTime tracks the hour and minute that are given.
 *
 *	paramaters:
 *		uint8_t hr - that will be our hour value.
 *		uint8_t min -  that will be our minute value.
 *		time_t localTime - that is we will track while setting.
 *
 *	Synopsis: Updates the watch's tracking time to the given hour and minute.	
 * 
 *	return: nothing
 */
void Clock::setWatchTime(uint8_t hr, uint8_t min, time_t localTime){

	//blank the strip
	face->clearStrip();
	face->ring.show();
	
	//Set new time and pass it to Gears
	setTime(hr,min,0,15,4,2012);
	gears->updateTime(now());
	
	
	//Track the time being set.
	//TrackTime really just tracks hand placement. It is ideal for this!
	trackTime(localTime);
	
	//Remove tail
	face->clearStrip();
}

