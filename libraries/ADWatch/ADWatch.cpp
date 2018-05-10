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

ADWatch::ADWatch(time_t trackMe, Adafruit_NeoPixel ring){
	clock = new Clock(trackMe,ring);
	return;
}

//Views
//TODO implement
void ADWatch::showTime(void){return;}

//TODO implement
void ADWatch::showSpeed(void){return;}

//TODO implement
void ADWatch::showHeading(void){return;}

//TODO implement
void ADWatch:: flashlight(void){return;}


//Flow tools
void ADWatch::flourish(void){
		clock->face->modMinColour(clock->gears->getCurTime()); //Can maybe be replaced with a direct GPS pull
		clock->face->colorWipe(clock->face->minColour,100);
		clock->face->clearStrip(); //Could maybe use fn() below! It's just an accessor fn().
		clock->face->ring.show();
}

void ADWatch::clearStrip(void){
	strip.clear();
	strip.show();
}

//Component init tools
void ADWatch::initRing(uint8_t brightness){
	strip.setBrightness(brightness);
	strip.begin();
	clearStrip();
	strip.show(); //Supposedly initilizes all to off
}
