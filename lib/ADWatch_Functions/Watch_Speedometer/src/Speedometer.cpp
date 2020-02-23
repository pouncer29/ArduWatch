/*
Author: Ben Lewis
Date: May 25th, 2018

Synopsis: The implementation for Speedometer.h
*/

#include "Speedometer.h"



//****************************************************************************************
//Speedometer//
//****************************************************************************************

/** Speedometer()
  	@Synopsis: Sets current speed and creates a new NeoPixel ring connection
 */
Speedometer::Speedometer(){
	dial = new Speed_Dial();
	gauge = new Speed_Gauge(0.0);
}

/** setRegionA()
	@precond: offsA is a valid array offset
	@postcond: Pixels are set for region A

	@param: offsA - an integer that corresponds to the current speed.
	@param: ring - the ring of led's to set the region on.

	@Synopsis: Clears the magic 11 bug then sets pixels from 6 (0km/h) to the provided
			  Index in regionAColour(green)
	
*/
void Speedometer::setRegionA(uint8_t offsA,Adafruit_NeoPixel* ring){
	
	ring->setPixelColor(11,dial->blank);
	for (uint8_t i = 6; i <= offsA;i++)
		ring->setPixelColor(i,dial->regionAColour);
}


/** setRegionB()
	@precond: offsB is a valid array offset
	@postcond: Pixels are set for region B

	@param: offsB - an integer that corresponds to the current speed
	@param: ring - the ring to set the region on

	@Synopsis: Clears the magic 11 bug then sets pixels from 9 (60km/h) to the provided
			  Index in regionBColour(Yellow).
	
*/
void Speedometer::setRegionB(uint8_t offsB,Adafruit_NeoPixel* ring){
	ring->setPixelColor(11,dial->blank);
	for(uint8_t i=9;i < offsB;i++){ // Watch out for potential offset errors...
		ring->setPixelColor(i,dial->regionBColour);
	}
}

/** setRegionC()
	@precond: offsC is a valid array offset
	@postcond: Pixels are set for region C

	@param: offsC - an integer that corresponds to the current speed
	@param: ring - the ring to set the region on

	@Synopsis: Clears the magic 11 bug then sets pixels from 0 (120km/h) to the provided
			  Index in regionCColour(red)
	
*/
void Speedometer::setRegionC(uint8_t offsC,Adafruit_NeoPixel* ring){
	for(uint8_t i=0; i <= offsC; i++)		//Using < in place will reduce to 3 if you change your mind
		ring->setPixelColor(i,dial->regionCColour);
}

/** placeNeedle()
	@precond: speed is set
	@postcond: speed is displayed
  
	@param: speedIdx - the index at which our current speed is mapped to.
 						 - speed in kilometers per hour
	@param: ring - the ring to set the dial on.

	@Synopsis: Takes a speed in and puts it through a series of if statements to determine
			  which speed quadrants need to be illuminated.
			  Note- with each progressive region, the overlap is overwritten by the higher speed's colour.
 */
void Speedometer::setDial(uint8_t speedIdx,Adafruit_NeoPixel* ring){	
	
	//Regular offset Assignment
	if(speedIdx >= 6 && speedIdx < 9){
		setRegionA(speedIdx,ring);
	}
	else if(speedIdx >= 9 && speedIdx < 12){
		setRegionA(8,ring);
		setRegionB(speedIdx,ring);
	}
	else if(speedIdx >= 0 && speedIdx < 4){
		setRegionA(8,ring);
		setRegionB(12,ring); // ensuring complete zone coverage by giving upper range bound
		setRegionC(speedIdx,ring); 
	}	
	return;
}

/**
	a vestigial method as no tail is left by this one.... I think.
*/
void Speedometer::removeTail(float h,Adafruit_NeoPixel* r){
	return;
}

/** trackSpeed()
	@precond: speed is valid
    @postcond: ring is activated to show the current speed.
  
    @param: kmph -  the speed that we will be tracking
    @param: ring - the ring to display the speed on.

    @Synopsis: grab a speed and set the dial to the appropriate index where it can be passed
			  to setDial to have the appropriate indicies illuminated via the Dial.
  
*/
void Speedometer::trackSpeed(float kmph,Adafruit_NeoPixel* ring){
	
	//Magic 11 fix.
	//Remove tail also handels update now.
	//Assign colours to the appropriate indicies.	
	gauge->updateSpeed(kmph);
	setDial(gauge->getSpeedIndex(),ring);
	
	//Display 
	ring->show();
}

/** setSpeed()
  	 @precond: speed is un-intialized or out o date
  	 @postcond: speed atribute is updated
  
  	 @param: kmph - the speed in kmph to update our gaguge to find an index for
  
  	@Synopsis: Takes in a speed then updates the speedometer with it.
   
 */
void Speedometer::setSpeed(float kmph){
	gauge->updateSpeed(kmph);
}

