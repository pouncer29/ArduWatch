/*
Author: Ben Lewis
Date: May 10th

Synopsis: 
*/

#include "ADWatch.h"



//****************************************************************************************
//AD WATCH//
//****************************************************************************************
//Initializers
/*
 *ADWatch()
 *
 *	precond: timeT is a valid time and Neopixel is instantiated
 * 	postcond: A new ADWatch object is created
 *
 *	Paramaters: 
 *
 *	Synopsis:
 */
//ADWatch::ADWatch(Adafruit_GPS g, Adafruit_NeoPixel neoP){} //For when GPS is incorperated

ADWatch::ADWatch(time_t trackMe, Adafruit_NeoPixel strip){
	ring = strip;
	ring.setBrightness(20);
	clock = new Clock(trackMe,ring);
	return;
}

//Views
//TODO implement
void ADWatch::showTime(time_t t){
	clock->trackTime(t); 
}

//TODO implement
void ADWatch::showSpeed(void){return;}

//TODO implement
void ADWatch::showHeading(void){return;}

//TODO implement
void ADWatch:: flashlight(void){return;}


//Flow tools
void ADWatch::flourish(void){
		//setTime(1,30,0,15,4,2012);
		clock->face->modMinColour(clock->gears->getCurTime()); //Can maybe be replaced with a direct GPS pull
		clock->face->modMinColour(now());
		clock->face->colorWipe(clock->face->minColour,100);
		clearRing(); //Could maybe use fn() below! It's just an accessor fn().
		ring.show();
}

void ADWatch::clearRing(void){
	ring.clear();
//	ring.show();
}

