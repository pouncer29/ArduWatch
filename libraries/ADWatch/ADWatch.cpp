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
	//speedo = new Speedometer(0,strip);
	light = new Flashlight(strip);
	return;
}

//Views
//TODO test
void ADWatch::showTime(time_t t){
	clock->trackTime(t); 
}

//TODO test
void ADWatch::showSpeed(float s){
	speedo->setSpeed(s);
	speedo->trackSpeed(s);
}

//TODO test
void ADWatch::showHeading(float h){
	compass->trackHeading(h);
}

void ADWatch::showLight(void){
	light->on();
}

void ADWatch::showStrobe(uint8_t stay){
	delay(45);
	light->strobe(stay);
}
	

//Internal Features
//TODO implement
void ADWatch::flashlight(void){
	//Define Colour

	uint32_t white = ring.Color(0,0,0,255);
	//Set Pixels
	flourish(white,100);	
	
	//Show Light!
	ring.show();

	return;
}

void ADWatch::strobe(bool stay){
	//Define Colour
	uint32_t white = ring.Color(0,0,0,255);

	//Strobe
	while(stay){
		//wait
		delay(30);

		//On
		ring.clear();
		ring.show();
		
		//wait		
		delay(100);
		
		//off
		setPixels(white);
		ring.show();
	}
	return;
}

void ADWatch::setPixels(uint32_t c){	
	for(uint8_t i =0; i<12; i++)
		ring.setPixelColor(i,c);		
}

//Flow tools
void ADWatch::flourish(uint32_t colour, uint32_t wait){
		for(uint8_t i=0; i <12;i++){
			ring.setPixelColor(i,colour);
			ring.show();
			delay(wait);
			}
		//ring.clear(); //Could maybe use fn() below! It's just an accessor fn().
		ring.show();
}

void ADWatch::clearRing(void){
	ring.clear();
//	ring.show();
}

