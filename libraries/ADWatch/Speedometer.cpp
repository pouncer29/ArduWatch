/*
Author: Ben Lewis
Date: May 25th, 2018

Synopsis: The implementation for Speedometer.h
*/

#include "Speedometer.h"



//****************************************************************************************
//Speedometer//
//****************************************************************************************

/* Speedometer()
  
  	precond: speed > 0
   	postcond: Speedometer is born
  
  	Paramaters: kn - the raw speed from the gps in knots
				neoP - the neopixel ring/strip/face/iMadeBadDecisionsNaming
  
  	Synopsis: Sets current speed and creates a new NeoPixel ring connection
 */
Speedometer::Speedometer(float kmph, Adafruit_NeoPixel neoP){
	curSpeed = kmph; //convertSpeed(kn);
	strip = neoP;
	dial = new Dial(neoP);
	gauge = new Gauge(kmph*1.825);
}

/* setRegionA()
	precond: offsA is a valid array offset
	postcond: Pixels are set for region A

	Parameters: offsA - an integer that corresponds to the current speed
	
	Synopsis: Clears the magic 11 bug then sets pixels from 6 (0km/h) to the provided
			  Index in regionAColour(green)
	
	return: nothing
*/
void Speedometer::setRegionA(uint8_t offsA){
	dial->ring.setPixelColor(11,dial->blank);
	for (uint8_t i = 6; i <= offsA;i++)
		dial->ring.setPixelColor(i,dial->regionAColour);
}


/* setRegionB()
	precond: offsB is a valid array offset
	postcond: Pixels are set for region B

	Parameters: offsB - an integer that corresponds to the current speed
	
	Synopsis: Clears the magic 11 bug then sets pixels from 9 (60km/h) to the provided
			  Index in regionBColour(Yellow).
	
	return: nothing
*/
void Speedometer::setRegionB(uint8_t offsB){
	dial->ring.setPixelColor(11,dial->blank);
	for(uint8_t i=9;i < offsB;i++){ // Watch out for potential offset errors...
		dial->ring.setPixelColor(i,dial->regionBColour);
	}
}

/* setRegionC()
	precond: offsC is a valid array offset
	postcond: Pixels are set for region C

	Parameters: offsC - an integer that corresponds to the current speed
	
	Synopsis: Clears the magic 11 bug then sets pixels from 0 (120km/h) to the provided
			  Index in regionCColour(red)
	
	return: nothing
*/
void Speedometer::setRegionC(uint8_t offsC){
	for(uint8_t i=0; i <= offsC; i++)		//Using < in place will reduce to 3 if you change your mind
		dial->ring.setPixelColor(i,dial->regionCColour);
}

/* placeNeedle()
	precond: speed is set
	postcond: speed is displayed
  
	Paramaters: speedIdx - the index at which our current speed is mapped to
  
	Synopsis: Takes a speed in (kmph) and puts it through a series of if statemetns to determine
			  which speed quadrents need to be illuminated.
			  Note- with each progressive region, the overlap is overwritten by the higher speed's colour.
  
	return: nothing
  
 */
void Speedometer::setDial(uint8_t speedIdx){	
	
	//Regular offset Assignment
	if(speedIdx >= 6 && speedIdx < 9){
		setRegionA(speedIdx);
	}
	else if(speedIdx >= 9 && speedIdx < 12){
		setRegionA(8);
		setRegionB(speedIdx);
	}
	else if(speedIdx >= 0 && speedIdx < 4){
		setRegionA(8);
		setRegionB(12); // ensuring complete zone coverage by giving upper range bound
		setRegionC(speedIdx); 
	}

	dial->ring.setPixelColor(speedIdx,dial->errorColour);//Was This for debug??	
	dial->ring.show();
	
	return;
}

/*
	a vestigial method as no tail is left by this one.... I think.
*/
void Speedometer::removeTail(float h){
	return;
}

/* trackSpeed()
	precond: speed is valid
    postcond: ring is activated to show the current speed.
  
    Paramaters: kmph -  the speed that we will be tracking

    Synopsis: grab a speed and set the dial to the appropriate index where it can be passed
			  to setDial to have the appropriate indicies illuminated via the Dial.
  
    return: nothing 		  
*/
void Speedometer::trackSpeed(float kmph){
	
	//Magic 11 fix.
	//Remvoe tail also handels update now.
	//Assign colours to the appropriate indicies.	
	gauge->updateSpeed(kmph);
	setDial(gauge->getSpeedIndex());
	
	
	//Display 
	dial->ring.show();
	dial->clearStrip();
	
}

/*setSpeed()
  	 precond: speed is un-intialized or out o date
  	 postcond: speed atribute is updated
  
  	 paramaters: newSpeed - what we update speed to.
  
  	Synopsis: Takes in a speed then updates the speedometer with it.	
   
  	return: nothing
 */
void Speedometer::setSpeed(float kmph){
	gauge->updateSpeed(kmph);
	dial->clearStrip();
}

