/*
Author: Ben Lewis
Date: February 17th, 2020

Synopsis: Compass Tests
*/

#include "Compass_CI.h"
#include "Compass_Needle.h"
#include "Compass_Magnet.h"
#include <Adafruit_NeoPixel_MOCK.h>

#include <assert.h>
#include <iostream>

using namespace std;


//******************************************************************************
//Compass_CI
//******************************************************************************


/**
	@Synopsis: Getter for Heading
*/
void magnet_GetCurHeading(){
	
	cout<<"Testing Magnet Get Heading"<<endl;

	//Setup
	Compass_Magnet* testMag = new Compass_Magnet();
	
	//Run
	float baseHeading = testMag->getCurHeading();

	//Check
	assert(baseHeading == 0.0);

	//Notify
	cout<<"Magnet Get Heading -- PASSED"<<endl;
	
}

/**
	@Synopsis: Setter for Heading
*/
void magnet_UpdateHeading(){
	cout<<"Testing Magnet Update Heading"<<endl;
	
	//Setup
	float testHeading = 29.0;
	Compass_Magnet* testMag = new Compass_Magnet();

	//run it 
	testMag->updateHeading(testHeading);
	float result = testMag->getCurHeading();
		
	//Check
	assert(result != 0.0);
	assert(testHeading == result);

	//Notify	
	cout<<"Magnet Update Heading -- PASSED"<<endl;
}

void magnet_GetHeadingIndex(){
	cout<<"Testing Magnet Get Heading Index Over val is 0"<<endl;
	
	//Setup 
	float testHeading = 361.0;
	Compass_Magnet* testMag = new Compass_Magnet();
	testMag->updateHeading(testHeading);

	//[0,30) -> 0
	cout<<"Testing heading [0deg,30deg) -> 0..."<<endl;
	for(float i = 0; i < 30.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 0);
	}
	
	//[30,60) -> 1
	cout<<"Testing heading [30deg,60deg) -> 1..."<<endl;
	for(float i = 30.0; i < 60.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 1);
	}

	//[60,90) -> 2
	cout<<"Testing heading [60deg,90deg) -> 2..."<<endl;
	for(float i = 60.0; i < 90.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 2);
	}
	
	//[90,120) -> 3
	cout<<"Testing heading [90deg,120deg) -> 3..."<<endl;
	for(float i = 90.0; i < 120.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 3);
	}
	
	//[120,150) -> 4 
	cout<<"Testing heading [150deg,180deg) -> 4..."<<endl;
	for(float i = 120.0; i < 150.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 4);
	}

	//[150,180) -> 5 
	cout<<"Testing heading [150deg,180deg) -> 5..."<<endl;
	for(float i = 150.0; i < 180.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 5);
	}

	//[180,210) -> 6
	cout<<"Testing heading [180deg,210deg) -> 6..."<<endl;
	for(float i = 180.0; i < 210.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 6);
	}

	//[210,240) -> 7
	cout<<"Testing heading [210deg,240deg) -> 7..."<<endl;
	for(float i = 210.0; i < 240.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 7);
	}

	//[240,270) -> 8
	cout<<"Testing heading [240deg,270deg) -> 8..."<<endl;
	for(float i = 240.0; i < 270.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 8);
	}

	//[270,300) -> 9
	cout<<"Testing heading [270deg,300deg) -> 9..."<<endl;
	for(float i = 270.0; i < 300.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 9);
	}
	
	//[300,330) -> 10
	cout<<"Testing heading [300deg,330deg) -> 10 ..."<<endl;
	for(float i = 300.0; i < 330.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 10);
	}

	//[330,360) -> 11
	cout<<"Testing heading [330deg,360deg) -> 11..."<<endl;
	for(float i = 330.0; i < 360.0; i = i + 0.5){
		testMag->updateHeading(i);
		uint8_t result = testMag->getHeadingIndex();
		assert(result == 11);
	}

	cout<<"Magnet Get Heading Index -- PASSED"<<endl;
	
}

/**
	@Synopsis: Tests for the Compass Indexer (Magnet)
*/
int Magnet_Tests(){
	cout<<"********************** TESTING MAGNET **********************"<<endl;
	magnet_GetCurHeading();
	magnet_UpdateHeading();
	magnet_GetHeadingIndex();
	return 0;
}


/**
	@Synopsis: The constructor for the compass needle
*/
void needle_Constructor(){

	cout<<"Testing Needle Constructor Assignes Colours "<<endl;
	//Construct
	Compass_Needle* testNeedle = new Compass_Needle();
	
	//Grab colours
	uint32_t northColour = testNeedle->northColour;
	uint32_t needleColour = testNeedle->needleColour;

	//Assert not 0 and not the same
	assert(northColour != 0);
	assert(needleColour != 0);
	assert(northColour != needleColour);

	cout<<"Needle Constructor Colour Assign -- PASSED"<<endl;
	
}
/**
	@Synopsis: Tests for the Compass Ring Interface (Needle)
*/
int Needle_Tests(){
	cout<<"********************** TESTING NEEDLE **********************"<<endl;
	needle_Constructor();
	return 0;
}

/**
	@Synopsis: Tests for the Compass controller
*/
int Compass_Tests(){
	cout<<"********************** TESTING COMPASS **********************"<<endl;
	assert(false);
}





int main(){
	cout<<"************* BEGINNING UNIT TESTS FOR COMPASS **************"<<endl;
	Magnet_Tests();
	Needle_Tests();
	Compass_Tests();
	return 0;
}

