/*
Author: Ben Lewis
Date: May 10th, 2018

Synopsis: 
*/

#include "ADWatch.h"


/* ADWatch
	- the implementation for ADWatch.h
*/

//ADWatch::ADWatch(Adafruit_GPS g, Adafruit_NeoPixel neoP){} //For when GPS is incorperated

ADWatch::ADWatch(Adafruit_NeoPixel* face){
	strip = face;
	strip->setBrightness(20);
	
	// init functions
	clock = new Clock();
	speedo = new Speedometer();
	compass = new Compass();
	light = new Flashlight();

	//grab colours for flourish/fn() switch
	clock_colour =	clock->face->minColour;
	speedo_colour = speedo->dial->regionBColour;
	compass_colour = compass->needle->needleColour;
	light_colour = light->lightColour;
	blank = light->blank;
	
	return;
}

//Views
//TODO test
/* showTime()
	precond: t is a valid time_t object
	postcond: time is desplayed on the ring

	paramaters: t - the time_t object who's time we will display
	
	synopsis: Takes in a time_t object, passes it to the trackTime function within the
			  Clock module where it is decomposed between Gears and Face modules to produce
			  A visual representation of the time!

	return: nothing
*/
void ADWatch::showTime(time_t t,Adafruit_NeoPixel* ring){
	clock->trackTime(t,ring); 
}

//TODO test
/* showSpeed()
	precond: float s is a float in range[0.0,**200.0] **double check range
	postcond: speed is displayed on the ring indexing fomr 6 up by 20km/h
	
	parameters: s - the speed we will display
	
	synopsis: takes in an initial speed to track (in knots from gps), and displays
			  its value in kmph on the ring.

	return: nothing.
*/
void ADWatch::showSpeed(float s,Adafruit_NeoPixel* ring){
	speedo->setSpeed(s);
	speedo->trackSpeed(s,ring);
}

//TODO test
/* showHeading()
	precond: h is a float in range [0.0,360.0)
	postcond: current heading is displayed using 30-degree intervals.
	
	parameters: h - the float heading we will track 

	synopsis: h is passed to the trackHeading method of the Compass Module where it is 
			  decomposed between the Needle and Magnet modules which, using 12:00, index 0, 
			  to represent North (0-degrees), and a seperate light to show heading based on 
			  every 30 degree change.

	return: nothing
*/
void ADWatch::showHeading(float h){
	compass->trackHeading(h,strip);
}

//TODO test
/* showLight()
	precond: none
	postcond: the light of Gandalf's staff fills the watch with ancient power and causes 
			  illumination.

	paramaters: none
	
	synopsis: turns all the lights to white and On...

	return: nothing
*/
void ADWatch::showLight(){
	//light = new Flashlight(ring);
	//strip->setBrightness(80);
	light->on(strip);
}

//TODO test
/* showStrobe()
	precond: none
	postcond: party gets statrted
	
	paramters: ceasePin - the pin that dictates the starting and stopping of the strobe
	
	synopsis: gets the party started, strobes at a rate of <idk> /s in white (for now)
*/
void ADWatch::showStrobe(uint8_t ceasePin,Adafruit_NeoPixel* ring){
	bool stay = digitalRead(ceasePin);
	delay(45);
	light->strobe(stay,ring);
}
	

//Flow tools
/* setPixels()
	precond: c is a valid colour code
	postcond: all pixels are *SET* to a the given colour.

	parameters: c - the uint32 that represents the colour to be displayed.

	synopsis: All pixels are set to colour c via a for loop.

	return: nothing
*/
void ADWatch::setPixels(uint32_t c,Adafruit_NeoPixel* ring){	
	for(uint8_t i =0; i<12; i++)
		ring->setPixelColor(i,c);		
}

/* flourish()
	precond: colour is valid and wait isn't really long
	postcond: the provided colour is spun around the indicies.

	parameters: colour - the uint32 that will be flourished about the ring
				wait - the uint32 that determines rate of flouish

	synopsis: produces a stream-like effect passing the given colour around the indicies.

	return: nothing
*/
void ADWatch::flourish(uint32_t colour, uint32_t wait,Adafruit_NeoPixel* ring){
		for(uint8_t i=0; i <12;i++){
			ring->setPixelColor(i,colour);
			ring->show();
			delay(wait);
			}
		delay(wait*3);
		ring->clear(); //Could maybe use fn() below! It's just an accessor fn().
		ring->show();
}


