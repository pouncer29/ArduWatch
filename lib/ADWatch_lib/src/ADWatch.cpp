/*
Author: Ben Lewis
Date: May 10th, 2018

Synopsis: 
*/

#include <ADWatch.h>


/** ADWatch()
 @Synopsis: The controller for the watch functions.
*/
ADWatch::ADWatch(Adafruit_NeoPixel* strip){
	// Ring
	ring = strip;
	//ring->setBrightness(20);

	// init features
	clock = new Clock();
	speedo = new Speedometer();
	compass = new Compass();
	//light = new Flashlight();
	functionCount = 6; //Including "refresh"

	//grab colours for flourish/fn() switch

	clock_colour =	clock->face->minColour;
	speedo_colour = speedo->dial->regionBColour;
	compass_colour = compass->needle->northColour;
	//light_colour = light->lightColour;
	//party_colour = light->violet;
	//blank = light->blank;
	//error_colour = light->red; 

}



/**FUNCTIONS*/
//Views
//TODO test
/** showTime()
	@precond: t is a valid time_t object
	@postcond: time is displayed on the ring

	@param: t - the time_t object who's time we will display
	
	@Synopsis: Takes in a time_t object, passes it to the trackTime function within the
			  Watch_Clock module where it is decomposed between Gears and Face modules to produce
			  A visual representation of the time!

*/
void ADWatch::showTime(time_t t){
	clock->trackTime(t,ring);
}

//TODO test
/** showSpeed()
	@precond: float s is a float in range[0.0,**200.0] **double check range
	@postcond: speed is displayed on the ring indexing fomr 6 up by 20km/h
	
	@param: s - the speed we will display
	
	@Synopsis: takes in an initial speed to track (in knots from gps), and displays
			  its value in kmph on the ring.

*/
void ADWatch::showSpeed(float speed){
	speedo->trackSpeed(speed,ring);
}

//TODO test
/** showHeading()
	@precond: h is a float in range [0.0,360.0)
	@postcond: current heading is displayed using 30-degree intervals.
	
	@param: h - the float heading we will track

	@Synopsis: h is passed to the trackHeading method of the Compass Module where it is
			  decomposed between the Needle and Magnet modules which, using 12:00, index 0, 
			  to represent North (0-degrees), and a seperate light to show heading based on 
			  every 30 degree change.

*/
void ADWatch::showHeading(float heading){
	compass->trackHeading(heading,ring);
}

//TODO test
/** showLight()
	@precond: none
	@postcond: the light of Gandalf's staff fills the watch with ancient power causing
			  illumination.

	@synopsis: turns all the lights to white and On...

*/
void ADWatch::showLight(){
	//ring->setBrightness(80);
	ring->setPixelColor(6,light_colour);
	light->on(ring);
}

//TODO test
/** showStrobe()
	@precond: none
	@postcond: party gets statrted
	
	@param: ceasePin - the pin that dictates the starting and stopping of the strobe
	
	@Synopsis: gets the party started, strobes at a rate of <idk> /s in white (for now)
*/
void ADWatch::showStrobe(uint8_t ceasePin){
	delay(45);
	light->strobe(ceasePin,ring);
}
	

//Flow tools
/** setPixels()
	@precond: c is a valid colour code
	@postcond: all pixels are *SET* to a the given colour.

	@param: c - the uint32 that represents the colour to be displayed.

	@synopsis: All pixels are set to colour c via a for loop.

*/
void ADWatch::setPixels(uint32_t c){	
	for(uint8_t i =0; i<12; i++)
		ring->setPixelColor(i,c);		
}

/** flourish()
	@precond: colour is valid and wait isn't really long
	@postcond: the provided colour is spun around the indicies.

	@param: colour - the uint32 that will be flourished about the ring
	@param: wait - the uint32 that determines rate of flouish

	@synopsis: produces a stream-like effect passing the given colour around the indicies.

*/
void ADWatch::flourish(uint32_t colour, uint32_t wait){
		for(uint8_t i=0; i <12;i++){
			ring->setPixelColor(i,colour);
			ring->show();
			delay(wait);
			}
		delay(wait*3);
		ring->clear(); //Could maybe use fn() below! It's just an accessor fn().
		ring->show();
}

/** refresh()
 *
 * @param: cond the terminating contition for the refresh
 * @Synopsis: Refreshes the watch, and displays loading-esq colours as it does.
 */
void ADWatch::refresh(bool cond){

	
}

/** showError()
 * @param: errColour - the colour to show when things go wrong
 * @Synopsis: the method to call, when things go wrong. Like the Cobra bubbles of methods.
 */
void ADWatch::showError(uint32_t errColour){
	setPixels(errColour);
	ring->show();
}

/**
 *
 * @param reading - the potentiometer reading to map to the enum
 * @return an integer that maps to the
 */
uint8_t ADWatch::getWatchFunction(int reading){
	uint8_t functionId = reading / 100;
	if(functionId > 10)
		return 10;
	else if(functionId > 5)
		return (functionId-functionCount);
	else
		return functionId;

}

