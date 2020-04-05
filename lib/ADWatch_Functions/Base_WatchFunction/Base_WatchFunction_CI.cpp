/*
Author: Ben Lewis
Date: February 19th, 2020

Synopsis: Because Arduino code is tough to make with gcc,and all I want is a verified
build, I've created this class. Perhaps I will add some tests in here too.. eventually
*/

#include "Base_WatchFunction_CI.h"
using namespace std;

//****************************************************************************************
//Base_WatchFunction
//****************************************************************************************


/**
   @Synopsis checks that Colour wipe sets colours
 */
void ringInterface_ColourWipe(){
	cout<<"Testing RingInterface Colour Wipe..."<<endl;
	//Setup
	RingInterface* testRI = new RingInterface();
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();
	uint32_t testColour = 44;

	//Call
	testRI->colorWipe(testColour,0,testRing);
	
	//Check
	uint32_t result = 0;
	for(int i = 0; i < 12; i++){
		result = GetVal(i,'c');
		assert(result == testColour);	
	}
	
	cout<<"RingInterface ColourWipe -- PASSED"<<endl;
}

/**
   @Synopsis checks that the 2 colours are averaged
 */
void ringInteface_GetAverageCross(){
	cout<<"Testing RingInterface Get Average Cross..."<<endl;

	//Setup
	RingInterface* testRI = new RingInterface();
	uint32_t colourA = 45;
	uint32_t colourB = 12;
	uint32_t avg = (colourA + colourB) / 2;
	
	//Call
	uint32_t result = testRI->getAverageCross(colourA,colourB);
	
	//Check
	assert(result == avg);
	
	cout<<"RingInterface GetAverageCross -- PASSED"<<endl;
}


/**
   @Synopsis: Tests for the Ring Interface
 */
int RingInterface_Tests(){
	cout<<"***************** TESTING RING INTERFACE ****************"<<endl;
	ringInterface_ColourWipe();
	ringInteface_GetAverageCross();
	return 0;
}
/**
   @Synopsis: Test for the BaseWatchFunctions 
 */
int main(){
	cout<<"***** BEGINNING UNIT TESTS FOR BASE WATCH FUNCTION ******"<<endl;
	RingInterface_Tests();	
	cout<<"************ BASE WATCH FUNCTION TESTS PASSED ***********"<<endl;
	return 0;
}



