/*
Author: Ben Lewis
Date: February 6th

Synopsis: The union of Gears and Face. ADWatch

*/

#include "ADWatch.h"



//****************************************************************************************
//AD WATCH//
//****************************************************************************************

/*
 *ADWatch()
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
ADWatch::ADWatch(time_t t, Adafruit_NeoPixel neoP){
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
void ADWatch::placeHands(uint8_t hrIdx,uint8_t minIdx,uint8_t secIdx){
	
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
void ADWatch::removeTail(uint8_t tailIdx,uint8_t hrIdx,uint8_t minIdx, uint8_t secIdx){
	
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
void ADWatch::trackTime(time_t t){

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
void ADWatch::setWatchTime(uint8_t hr, uint8_t min, time_t localTime){

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



//GEARS//

/*
 *Gears()
 * precond: none
 * postcond: a Gears object is created
 * 
 * paramaters: time_t* t - a pointer to the time we need to track
 * 
 * 
 
ADWatch::Gears::Gears(time_t* t){
	curTime = t;	
}


 *getHourIndex()
 * precond: curTime is set
 * postcond: none
 * 
 * Synopsis: Accesses the hour of the time object we are tracking and use % 12 to get
 * 			 the appropriate index for the hour hand.
 *
 * return: Array index for the Hour hand
 *
uint8_t ADWatch::Gears::getHourIndex(void){
  	//store hour
	//uint8_t	hr = hour(curTime);
	
	//determine index
	return hour(curTime) % 12;
}


 *getMinuteIndex()
 * pecond: curtime is set
 * postcond: none
 * 
 * Synopsis: Accesses the minute of the time we are tracking and rely on integer division to give us a 
 * 			 valid hand position/array index.
 *
 * return: Array index for the Minute hand
 *
uint8_t ADWatch::Gears::getMinuteIndex(void){
	return minute(curTime)/5;
}

*
 *getSecondIndex()
 * precond: curtime is set
 * postcond: none
 * 
 * Synopsis: Accesses the second of the time we are tracking and uses integer division to determine a 
 * 			 valid hand position/array index.i
 *
 * return: Array index for the seond hand 
 *
uint8_t ADWatch::Gears::getSecondIndex(void){
	return second(curTime)/5;
}

*
 getCurTime()
	- A simple getter method for the private attribute 'curTime'
time_t ADWatch::Gears::getCurTime(void){
	return curTime;
}
 *updateTime()
 * precond: none
 * postcond: Gears curTime attribute has been updated
 *
 * Paramaters:
 *     time_t newTime - the time we will update our gears to
 *
 * Synopsis: Changes the Gears time value to a specified value
 *
 * return: nothing
void ADWatch::Gears::updateTime(time_t newTime){
	curTime = newTime;
}


//FACE//

 *Face()
 * precond: none
 * postcond: a new Face object is created
 * 
 * Parameters:
 *    Adafruit_Neopixel leds - the chain of Neopixels that will serve as our face.
 *
 * Synopsis: assigns the Faces ring to the ledRing and assigns special colours
 *
 * return: a new Face Object
ADWatch::Face::Face(Adafruit_NeoPixel leds){
	
	//Instantiate Attributes;
	ring = leds;
	
	//Define special Colours
	hrColour = ring.Color(255,100,0,5);
	minColour = ring.Color(0,255,95,0);
	secColour = ring.Color(0,160,255,0);
	rstTimeColour = ring.Color(255,0,0,0);
	blank = ring.Color(0,0,0,0);
}

clearStrip()
 *  precond: none
 *  postcond: all pixels in ring are set to blank 
 *  
 *	Synopsis: clears all of the colours from the rings indicies.
 * 
 *  return: nothing
 * 
void ADWatch::Face::clearStrip(void){
	ring.clear();
}

getAverageCross()
 *  precond: none
 *  postcond: none
 *  
 *  Paramaters:
 *    uint32_t colourA - one hand's colour
 * 	  uint32_t colourB - another hand's colour
 *  
 * 	synopsis: Takes the colour values of two hands and creates an average of the two. why? because what
 * 			  better way is there to represent crossing hands?
 *    
 *  return: the uint32 average of the two colours.
 * 
uint32_t ADWatch::Face::getAverageCross(uint32_t colourA, uint32_t colourB){
  return((colourA+colourB)/2);
}

minModColour()
 *  precond: time is set
 *  postcond: minuteColour global variable is updated.
 *  
 *  Paramaters:
 *    time_t localTime -  the current minute.
 *  
 * 	Synopsis: 
 *  	You trolls thought I forgot didn't you? you were all like "Ben, what the farts? What good is a watch that only
 *  	tracks 5 minute intervals? Look, I was thinking the exact same thing, so I decided that minutes should start at
 *  	their beautiful green and then, as the minute progresses, get slowly more red to finish with a beautiful purple
 *  	at all of your hh:m9 and hh:m4 minutes. YOU'RE WELCOME. 
 *  
 *  	How does it work?
 *    	You take the remainder of whatever minute it is and 5, multiply it by 64 (to get a max val of 256 and min of 0)
 *    	and use it to add to the minHands mined out Red and subtract from its maxed out Green.  
 *  
 *  return: nothing 
void ADWatch::Face::modMinColour(time_t localTime){

  //minMod the index of the minute hand * 64
  uint16_t minMod = ((minute(localTime)%5)*64);
  if(minMod > 0)
    minMod--;   //So that subtact 1 from 256 to prevent wrapping and not from 0 to go out of bounds on the strip array.

  //Minute becomes more red and less green as it progresses.
  minColour = ring.Color(0+minMod,255-minMod,95,0);
  ring.setPixelColor(11,blank); // Band-aid for magic 11 bug.
  return;
}

colorWipe
 *  This code is from Adafruit's NeoPixel Playground, I di not write it. It's what i use whith the modded min colour to create that 
 *  epic activation sequence.
void ADWatch::Face::colorWipe(uint32_t c, uint16_t wait) {
  for(uint8_t i=0; i<12; i++) {
    ring.setPixelColor(i, c);    
    ring.show();
    delay(wait);
  }
  ring.clear();
  ring.show();
}
*/
// FOR TESTING ONLY
// void ADWatch::Face::showAvg(uint32_t A, uint32_t B){
// 	colorWipe(getAverageCross(A,B),200);
// 	return;
// }







	
