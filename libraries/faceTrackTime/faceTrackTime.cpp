/*
	Author: Ben Lewis
	Date: December 30th, 2017
	
	Synopsis: Implementation for time-tracking methods.
*/

#include "faceTrackTime.h"


Face_Show_Time::Face_Show_Time(Adafruit_NeoPixel strip){
	
	//Instantiate Attributes;
	ring = strip;
	
    hrColour = ring.Color(255,100,0,5);
    minColour = ring.Color(0,255,95,0);
	secColour = ring.Color(0,160,255,0);
	blank = ring.Color(0,0,0,0);
}

/* getHourIndex()
 *  precond: time is set
 *  postcond: none.
 *  
 *  Paramaters
 *    localTime: a time_t that we will harvest the hour from.
 *  
 *  return: The offset corresponding to the current hour with 0 being 12/2400 and 11 being 11/2300
 */
uint8_t Face_Show_Time::getHourIndex(time_t localTime){

 uint8_t curHour = hour(localTime);

  // if the hour is negative (traveling backwards in time) return -1 for error.
  if(curHour < 0)
    return -1;
  else if(curHour >= 12)  // if it's >= than 12 (24hr format) just subract 12 from that sucker
    return curHour - 12;
  else
    return curHour;      // if its not >=12 it must be before 12:00 so it has a reasonable index.
}

/* getMinuteIndex()
 *  precond: time is set;
 *  postcond: none.
 *  
 *  Paramaters
 *    localTime: a time_t that we will harvest the minute from.
 *    
 *  return: The offset corresponding to the current 5 minute interval.
 * 
 */
uint8_t Face_Show_Time::getMinuteIndex(time_t localTime){
    return minute(localTime)/5;
}

/* getSecondIndex()
 *  precond: time is set.
 *  postcond: none.
 *  
 *  Paramaters
 *    localTime: You guessed it, its a time_t that we will use to harvest seconds.
 *    
 *  return: the offset corresponding to the current 5 minute interval.
 * 
 */
uint8_t Face_Show_Time::getSecondIndex(time_t localTime){
  return second(localTime)/5;
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
void Face_Show_Time::clearStrip(void){
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
uint32_t Face_Show_Time::getAverageCross(uint32_t colourA, uint32_t colourB){
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
void Face_Show_Time::modMinColour(time_t localTime){

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
void Face_Show_Time::colorWipe(uint32_t c, uint16_t wait) {
  for(uint8_t i=0; i<12; i++) {
    ring.setPixelColor(i, c);    
    ring.show();
    delay(wait);
  }
}

/* trackTime()
 *  precond: time is set
 *  postcond: time is output with stunning style and beauty (i mean, its ok)
 *  
 *  paramaters
 *    localTime: the time we will desplay
 *    
 *  look guys (and guy-etts), this is where the work is done. it gets the clockHand indicies, sets the colours,
 *  determines crossing indexes, and then clears it.
 * 
 */
void Face_Show_Time::trackTime(time_t localTime){

  //Grab our clockHand indecies
  uint8_t hrIdx  = getHourIndex(localTime);
  uint8_t minIdx = getMinuteIndex(localTime);
  uint8_t secIdx = getSecondIndex(localTime);

  //Track minutes with minHand.
  modMinColour(localTime); 
  
  //Assign colours accordingly
  
  //Base case: No Overlap regualr 
  ring.setPixelColor(hrIdx,hrColour);
  ring.setPixelColor(minIdx,minColour);
  ring.setPixelColor(secIdx,secColour);
 
  // Otherwise: If Hands Cross, Their indicies will be the same so I average their set colours.
  if (secIdx == minIdx && minIdx == hrIdx)
    ring.setPixelColor(minIdx,getAverageCross((getAverageCross(secColour,minColour)),hrColour));
  else if(secIdx == minIdx)
    ring.setPixelColor(minIdx,getAverageCross(secColour,minColour));
  else if(secIdx == hrIdx)
    ring.setPixelColor(hrIdx,getAverageCross(secColour,hrColour));
  else if(hrIdx == minIdx)
    ring.setPixelColor(hrIdx, getAverageCross(hrColour,minColour));

  //Display and clear.
  ring.show();
  clearStrip();
}




	