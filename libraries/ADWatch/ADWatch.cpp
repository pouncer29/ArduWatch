/*
Author: Ben Lewis
Date: February 6th

Synopsis: The union of Gears and Face. ADWatch

*/

#include "ADWatch.h"



//****************************************************************************************
//AD WATCH//
//*************************************************************
ADWatch::ADWatch(time_t t, Adafruit_NeoPixel neoP){
	trackMe = t;
	strip = neoP;
	
	face = new Face(strip);
	gears = new Gears(trackMe);
	


}

void ADWatch::trackTime(time_t t){
	return;
	/*
  	gears.updateTime(t);

	uint8_t hrIdx  = gears.getHourIndex();
	uint8_t minIdx = gears.getMinuteIndex();
	uint8_t secIdx = gears.getSecondIndex();

	//Track minutes with minHand.
	face.modMinColour(t); 

	//Assign colours accordingly

	//Base case: No Overlap regualr 
	face.ring.setPixelColor(hrIdx,hrColour);
	face.ring.setPixelColor(minIdx,minColour);
	face.ring.setPixelColor(secIdx,secColour);

	// Otherwise: If Hands Cross, Their indicies will be the same so I average their set colours.
	//This particuairly nasty block is only so nasty because I take the average of an average. will work on shortening 
	if (secIdx == minIdx && minIdx == hrIdx)
		face.ring.setPixelColor(minIdx,face.getAverageCross((face.getAverageCross(face.secColour,face.minColour)),face.hrColour));
	else if(secIdx == minIdx)
		face.ring.setPixelColor(minIdx,face.getAverageCross(face.secColour,face.minColour));
	else if(secIdx == hrIdx)
		face.ring.setPixelColor(hrIdx,face.getAverageCross(face.secColour,face.hrColour));
	else if(hrIdx == minIdx)
		face.ring.setPixelColor(hrIdx, face.getAverageCross(face.hrColour,face.minColour));

  //Display 
  face.ring.show();*/
}


//****************************************************************************************
//GEARS//
//****************************************************************************************

ADWatch::Gears::Gears(time_t* t){
	
	curTime = t;	
}

/*
 getHourIndex()
	- Checks whether or not the index is in 24 hour notation and returns the appropriate hour index for time "curTime".
*/
uint8_t ADWatch::Gears::getHourIndex(void){
  	//store hour
	uint8_t	hr = hour(curTime);
	
	//determine index
	if(hr < 0)
		return -1;
	else if (hr >= 12)	//Handles 24hr time (no 24th neopixel)
		return hr - 12;
	else
		return hr;
}

/*
 getMinuteIndex()
	- takes the minute value of the instance time "curTime" and returns a valid clock offset for it.
*/
uint8_t ADWatch::Gears::getMinuteIndex(void){
	return minute(curTime)/5;
}

/*
 getSecondIndex()
	- takes the second value of the instance time "curTime" and returns a valid clock offset for it.
*/
uint8_t ADWatch::Gears::getSecondIndex(void){
	return second(curTime)/5;
}

/*
 updateTime()
	- takes in a time_t and updates its curTime attribute to be it.
*/
void ADWatch::Gears::updateTime(time_t newTime){
	curTime = newTime;
}

// void ADWatch::Gears::trackTime(void){
// 	return;
// }

//****************************************************************************************
//FACE//
//****************************************************************************************

ADWatch::Face::Face(Adafruit_NeoPixel* s){
	
	//Instantiate Attributes;
	ring = s;
	
	//Define special Colours
    hrColour = ring.Color(255,100,0,5);
    minColour = ring.Color(0,255,95,0);
	secColour = ring.Color(0,160,255,0);
	rstTimeColour = ring.Color(255,0,0,0);
	blank = ring.Color(0,0,0,0);
}

/* clearStrip()
 *  precond: ring is not null
 *  postcond: all pixels in ring are set to blank 
 *  
 *  I love adafruit but I couldn't get their .show() to clear the ring like they said it would.
 *  maybe should consider adding the .show() to the end of this one but that could be a mess.
 *  
 *  return: nothing
 * 
 */
void ADWatch::Face::clearStrip(void){
  for(uint8_t i = 0; i < 12; i++)
    ring.setPixelColor(i,blank);
}

/* getAverageCross()
 *  precond: none
 *  postcond: none
 *  
 *  Paramaters
 *    colourA/B: Both are unsigned 32 bit unsigned integers that represent 2 colours who's RGBW values will 
 *               be averaged why? Because what else would happen when two clock hands cross?
 *               
 *  return: the uint32 average of the two colours.
 * 
 */
uint32_t ADWatch::Face::getAverageCross(uint32_t colourA, uint32_t colourB){
  return((colourA+colourB)/2);
}

/* minModColour()
 *  precond: time is set
 *  postcond: minuteColour global variable is updated.
 *  
 *  Paramaters
 *    localTime: a time_t that will give us the current minute.
 *  
 *  You trolls thought I forgot didn't you? you were all like "Ben, what the farts? What good is a watch that only
 *  tracks 5 minute intervals? Look, I was thinking the exact same thing, so I decided that minutes should start at
 *  their beautiful green and then, as the minute progresses, get slowly more red to finish with a beautiful purple
 *  at all of your hh:m9 and hh:m4 minutes. YOU'RE WELCOME. 
 *  
 *  How does it work?
 *    You take the remainder of whatever minute it is and 5, multiply it by 64 (to get a max val of 256 and min of 0)
 *    and use it to add to the minHands mined out Red and subtract from its maxed out Green.  
 *  
 *  return: nothing 
 */
void ADWatch::Face::modMinColour(time_t localTime){

  //minMod: Takes the remainder of the 
  uint16_t minMod = ((minute(localTime)%5)*64);
  if(minMod > 0)
    minMod--;   //So that subtact 1 from 256 to prevent wrapping and not from 0 to go out of bounds on the strip array.

  //Minute becomes more red as it progresses.
  minColour = ring.Color(0+minMod,255-minMod,95,0);
  return;
}

/* colorWipe
 *  This code is from Adafruit's NeoPixel Playground, I di not write it. It's what i use whith the modded min colour to create that 
 *  epic activation sequence.
 */
void ADWatch::Face::colorWipe(uint32_t c, uint16_t wait) {
  for(uint8_t i=0; i<12; i++) {
    ring.setPixelColor(i, c);    
    ring.show();
    delay(wait);
  }
  clearStrip();
  ring.show();
}

//FOR TESTING ONLY
void ADWatch::Face::showAvg(uint32_t A, uint32_t B){
	colorWipe(getAverageCross(A,B),200);
	return;
}







	