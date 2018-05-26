/*
Author: Ben Lewis
Date: May 25th, 2018

Synopsis: 

*/

#include "Speedometer.h"



//****************************************************************************************
//Speedometer//
//****************************************************************************************

/*
 *Speedometer()
 *
 *	precond: 
 * 	postcond: 
 *
 *	Paramaters: 
 *
 *	Synopsis: 
 */
Speedometer::Speedometer(float kn, Adafruit_NeoPixel neoP){
	curSpeed = kn;
	strip = neoP;
	dial = new Dial(neoP);
	gauge = new Gauge(kn);

//	curHeadIdx = gauge->getSpeedIndex();
	//prevHeadIdx = -1;
}


void Speedometer::setRegionA(uint8_t offsA){
	for (uint8_t i = 6; i <= offsA;i++)
		dial->ring.setPixelColor(i,dial->regionAColour);
}

void Speedometer::setRegionB(uint8_t offsB){
	for(uint8_t i=9;i < offsB;i++){ // Watch out for potential offset errors...
		dial->ring.setPixelColor(i,dial->regionBColour);
	}
}

void Speedometer::setRegionC(uint8_t offsC){
	for(uint8_t i=0; i <= offsC; i++)		//Using < in place will reduce to 3 if you change your mind
		dial->ring.setPixelColor(i,dial->regionCColour);
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
	
	
	dial->ring.show();
	//Remove Tail

	return;
}
void Speedometer::removeTail(float h){

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
void Speedometer::trackSpeed(float kn){
	
	//Remvoe tail also handels update now.
	//Assign colours to the appropriate indicies.	
	setDial(3);
	
	//magic 11
//	if(curHeadIdx < 11)
//		dial->ring.setPixelColor(11,dial->blank);
	
	//Display 
	dial->ring.show();
	
	dial->clearStrip();
	
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
void Speedometer::setSpeed(float newSpeed){
	gauge->updateSpeed(newSpeed);
	dial->clearStrip();
}

