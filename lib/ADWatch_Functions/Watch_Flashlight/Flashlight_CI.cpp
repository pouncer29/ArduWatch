/*
Author: Ben Lewis
Date: February 18th, 2020
Synopsis: Unit tests for the flashlight tests.
*/

#include "Flashlight_CI.h"

using namespace std;


//******************************************************************************
//Flashlight_CI
//******************************************************************************

/**
	@Synopsis: Testing Constructor for Flashlight
*/
void flashlight_Constructor(){
	cout<<"Testing Flashlight Constructor ..."<<endl;
	
	//Setup
	Flashlight* testLight = new Flashlight();
	
	//Check colours have been set
	assert(testLight->colours[0] != 0);
	assert(testLight->colours[1] != 0);
	assert(testLight->colours[2] != 0);
	assert(testLight->colours[3] != 0);
	assert(testLight->colours[4] != 0);
	assert(testLight->colours[5] != 0);
	assert(testLight->colours[6] != 0);
	assert(testLight->colours[7] != 0);

	cout<<"Flashlight Constructor -- PASSED"<<endl;
}

/**
	@Synopsis: Testing ColourWipe for Flashlight
*/
void flashlight_ColourWipe(){
	cout<<"Testing Flashlight ColourWipe..."<<endl;
	//Setup
	Flashlight* testLight = new Flashlight();
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();
	uint32_t testColour = 29;
	uint8_t wait = 0;

	//Run
	testLight->colorWipe(testColour,wait,testRing);
	

	//Check
	uint32_t result = 0;
	for(int i = 0; i<12; i++){
		result = GetVal(i,'c');
		assert (result == testColour);	
	}

	cout<<"Flashlight ColourWipe -- PASSED"<<endl;
}

/**
	@Synopsis: Testing on for Flashlight
*/
void flashlight_On(){
	cout<<"Testing Flashlight On..."<<endl;
	//Setup
	Flashlight* testLight = new Flashlight();
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();
	uint32_t lightColour = testLight->colours[0];
	
	//Run
	testLight->on(testRing);
	
	//Check
	uint32_t result = 0;
	for(int i = 0; i<12; i++){
		result = GetVal(i,'c');
		assert(result == lightColour);
	}
	
	cout<<"Flashlight On -- PASSED"<<endl;
}

/**
	@Synopsis: Testing off for Flashlight
*/
void flashlight_Off(){
	cout<<"Testing Flashlight Off..."<<endl;
	//Setup 
	Flashlight* testLight = new Flashlight();
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();
	
	testLight->on(testRing);

	//Run
	testLight->off(testRing);

	//Check 
	uint32_t result = 5;
	for(int i = 0; i<12; i++){
		result = GetVal(i,'c');
		assert(result == 0);
	}

	cout<<"Flashlight Off -- PASSED"<<endl;
}

/**
	@Synopsis: Testing party colour retriver for Flashlight
*/
void flashlight_Party(){
	cout<<"Testing Flashlight Party..."<<endl;

	//Setup
	Flashlight* testLight = new Flashlight();
	
	//Run
	uint32_t result = 0;
	for(int i = 0; i<=50; i++){
		result = testLight->party();
		assert(result != 0);
	}
	cout<<"Flashlight Party -- PASSED"<<endl;
}


/**
@synopsis: Tests for the flashlight component controller
*/
int Flashlight_Tests(){
	cout<<"******************** TESTING FLASHLIGHT *********************"<<endl;
	flashlight_Constructor();
	flashlight_ColourWipe();
	flashlight_On();
	flashlight_Off();
	flashlight_Party();
	return 0;
}


/**
	@Synopsis: Flashlight tests
*/
int main(){
	cout<<"************ BEGINNING UNIT TESTS FOR FLASHLIGHT ************"<<endl;
	Flashlight_Tests();
	cout<<"****************** FLASHLIGHT TESTS PASSED ******************"<<endl;
	return 0;
}



