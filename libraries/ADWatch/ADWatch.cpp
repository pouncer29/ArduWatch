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
	strip.setBrightness(20);
	ring = strip;
	//ring.setBrightness(20);
	//clock = new Clock(trackMe,strip);
	//compass = new Compass(0,strip);
	speedo = new Speedometer(0,strip);
	return;
}

//Views
//TODO test
void ADWatch::showTime(time_t t){
	clock->trackTime(t); 
}

//TODO implement
void ADWatch::showSpeed(float s){
	speedo->setSpeed(s);
	speedo->trackSpeed(s);
}

//TODO test
void ADWatch::showHeading(float h){
	compass->trackHeading(h);
}

//TODO implement
void ADWatch:: flashlight(void){return;}


//Flow tools
void ADWatch::flourish(uint32_t colour){
		for(uint8_t i=0; i <12;i++){
			ring.setPixelColor(i,colour);
			ring.show();
			delay(100);
			}
		ring.clear(); //Could maybe use fn() below! It's just an accessor fn().
		ring.show();
}

void ADWatch::clearRing(void){
	ring.clear();
//	ring.show();
}

