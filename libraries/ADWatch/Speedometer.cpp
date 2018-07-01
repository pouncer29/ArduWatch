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
  
  	Synopsis: Saves and converts the current speed and creates a new NeoPixel ring connection
 */
Speedometer::Speedometer(float kn, Adafruit_NeoPixel neoP){
	curSpeed = convertSpeed(kn);
	strip = neoP;
	dial = new Dial(neoP);
	gauge = new Gauge(kn);
}


void Speedometer::setRegionA(uint8_t offsA){
	dial->ring.setPixelColor(11,dial->blank);
	for (uint8_t i = 6; i <= offsA;i++)
		dial->ring.setPixelColor(i,dial->regionAColour);
}

void Speedometer::setRegionB(uint8_t offsB){
	dial->ring.setPixelColor(11,dial->blank);
	for(uint8_t i=9;i < offsB;i++){ // Watch out for potential offset errors...
		dial->ring.setPixelColor(i,dial->regionBColour);
	}
}

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
void Speedometer::removeTail(float h){

	return;
}

/* trackSpeed()
	precond: speed is valid
    postcond: ring is activated to show the current speed.
  
    Paramaters: km -  the speed that we will be tracking

    Synopsis: grab a speed and set the dial to the appropriate index where it can be passed
			  to setDial to have the appropriate indicies illuminated via the Dial.
  
    return: nothing 		  
*/
void Speedometer::trackSpeed(float km){
	
	//Magic 11 fix.
	//Remvoe tail also handels update now.
	//Assign colours to the appropriate indicies.	
	gauge->updateSpeed(kn);
	setDial(gauge->getSpeedIndex());
	
	
	//Display 
	dial->ring.show();
	dial->clearStrip();
	
}

/*setSpeed()
  	 precond: speed is un-intialized or out o date
  	 postcond: speed atribute is updated
  
  	 paramaters: newSpeed - what we update speed to.
  
  	Synopsis: Takes in a speed in kn, converts it, then updates the speedometer with it.	
   
  	return: nothing
 */
void Speedometer::setSpeed(float newSpeed){
	newSpeed = convertSpeed(newSpeed);
	gauge->updateSpeed(newSpeed);
	dial->clearStrip();
}

/*
	precond: given speed is > 0
	postcond: none

	paramters: knSpeed - a speed in knots to be converted

	synopsis: Takes in a kn speed and converts it to a kmph speed
*/
float Speedometer::convertSpeed(float knSpeed){
	return knSpeed * 1.852;
}
