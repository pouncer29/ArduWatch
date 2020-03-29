/*
Author: Ben Lewis
Date: February 19th, 2020

Synopsis: Because Arduino code is tough to make with gcc,and all I want is a verified
build, I've created this class. Perhaps I will add some tests in here too.. eventually
*/

#include "Base_WatchFunction_CI.h"
#include <iostream>

using namespace std;

//****************************************************************************************
//Base_WatchFunction
//****************************************************************************************

void ringInterface_ColourWipe(){
	cout<<"Testing RingInterface <METHOD>..."<<endl;
	//Setup
	//Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();
	assert(false);
	cout<<"RingInterface <METHOD> -- PASSED"<<endl;
}

/**
   @Synopsis checks that the 2 colours are averaged
 */
void ringInteface_GetAverageCross(){
	cout<<"Testing RingInterface <METHOD>..."<<endl;
	assert(false);
	cout<<"RingInterface <METHOD> -- PASSED"<<endl;
}


/**
   @Synopsis: Tests for the Ring Interface
 */
int RingInterface_Tests(){
	cout<<"***************** TESTING RING INTERFACE ****************"<<endl;
	ringInterface_ColourWipe();
	ringInteface_GetAverageCross();
	assert(false);
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



