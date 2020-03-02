/*
Author: Ben Lewis
Date: February 16th, 2020

Synopsis: Because Arduino code is tough to make with gcc,and all I want is a verified
build, I've created this class. Perhaps I will add some tests in here too.. eventually
*/

#include "Clock_CI.h"

using namespace std;


//****************************************************************************************
//Clock_CI
//****************************************************************************************

/* CLOCK_GEARS TESTS */

/* TEST HOLDERS */

/** gears_Constructer*/
void gears_Constructor(){
	cout<<"Testing Gears Constructor"<<endl;

	//Setup
	int tstHr = 12;
	int tstMin = 1;
	int tstSec = 36;
	setTime(tstHr,tstMin,tstSec);

	//Construction
	Clock_Gears* testGears = new Clock_Gears();
	time_t result = testGears->getCurTime();

	//Asserts
	assert(testGears != NULL);
	assert(hour(result) == tstHr);
	assert(minute(result) == tstMin);
	assert(second(result) == tstSec);
	
	cout<<"Gears Construction -- PASSED"<<endl;
}


void gears_UpdateTime(){
	cout<<"Testing Gears Update Time"<<endl;
	
	//Setup
	int tstHr = 12;
	int tstMin = 1;
	int tstSec = 36;
	setTime(tstHr,tstMin,tstSec);
	Clock_Gears* testGears = new Clock_Gears();
	time_t tstTime = 15;
	
	//Testing
	testGears->updateTime(tstTime);
	time_t result = testGears -> getCurTime();
	
	assert(result == tstTime);
	cout<<"Gears Update Time -- PASSED"<<endl;
}

/** Tests for Index Retrival*/
void gears_GetIndex(){
	cout<<"Testing Gears Get Index"<<endl;
	Clock_Gears* testGears = new Clock_Gears();

	cout<<"Testing Hour Index Retrival..."<<endl;
	for(uint8_t i =0; i < 24; i++){
		//Setup
		setTime(i,0,0);
		testGears->updateTime(now());
		
		//Testing
		uint8_t result = testGears->getHourIndex();

		//Result should never be greater than 11.
		assert(result <= 11);

		//Assets
		if( i <= 11 ){
			assert(i == result);
		} else {
			//24 hour time
			uint8_t modded = i - 12;
			assert(modded == result);
		}
	}
	
	cout<<"Gears Hour Index Retrival -- PASSED"<<endl;


	cout<<"Testing Minute Index Retrival..."<<endl;
	for(uint8_t i=0; i < 60; i++){
		//Setup
		setTime(0,i,0);
		testGears->updateTime(now());
		
		//Testing
		uint8_t result = testGears->getMinuteIndex();

		//Result should never be greater than 11
		assert(result <= 11);

		// 0
		if( i >= 0 && i < 5){
			assert(result == 0);
		// 5
		} else if ( i >= 5 && i < 10){
			assert(result == 1);
		// 10 
		} else if ( i >= 10 && i < 15){
			assert(result == 2);
		// 15 
		} else if ( i >= 15 && i < 20){
			assert(result == 3);
		// 20
		} else if ( i >= 20 && i < 25){
			assert(result == 4);
		// 25
		} else if ( i >= 25 && i < 30){
			assert(result == 5);
		// 30
		} else if ( i >= 30 && i < 35){
			assert(result == 6);
		// 35
		} else if ( i >= 35 && i < 40){
			assert(result == 7);
		// 40
		} else if ( i >= 40 && i < 45){
			assert(result == 8);
		//45
		} else if ( i >= 45 && i < 50){
			assert(result == 9);
		//50
		} else if ( i >= 50 && i < 55){
			assert(result == 10);
		//55
		} else if ( i >= 55 && i < 60){
			assert(result == 11 );
		//60
		} else if ( i >= 60 ){
			assert(result == 0 );
		}
	}
	
	cout<<"Gears Minute Index Retrival -- PASSED"<<endl;
		

	cout<<"Testing Second Index Retrival..."<<endl;
	for(uint8_t i = 0; i < 60; i++){
		//Setup
		setTime(0,0,i);
		testGears->updateTime(now());
		
		//Testing
		uint8_t result = testGears->getSecondIndex();

		//Result should never be greater than 11
		assert(result <= 11);

		// 0
		if( i >= 0 && i < 5){
			assert(result == 0);
		// 5
		} else if ( i >= 5 && i < 10){
			assert(result == 1);
		// 10 
		} else if ( i >= 10 && i < 15){
			assert(result == 2);
		// 15 
		} else if ( i >= 15 && i < 20){
			assert(result == 3);
		// 20
		} else if ( i >= 20 && i < 25){
			assert(result == 4);
		// 25
		} else if ( i >= 25 && i < 30){
			assert(result == 5);
		// 30
		} else if ( i >= 30 && i < 35){
			assert(result == 6);
		// 35
		} else if ( i >= 35 && i < 40){
			assert(result == 7);
		// 40
		} else if ( i >= 40 && i < 45){
			assert(result == 8);
		//45
		} else if ( i >= 45 && i < 50){
			assert(result == 9);
		//50
		} else if ( i >= 50 && i < 55){
			assert(result == 10);
		//55
		} else if ( i >= 55 && i < 60){
			assert(result == 11 );
		//60
		} else if ( i >= 60 ){
			assert(result == 0 );
		}
	}
	cout<<"Gears Seconds Index Retrival -- PASSED"<<endl;
	return;

}


int Clock_GearsTests(){
	cout<<"****************** TESTING GEARS ****************************"<<endl;
	gears_Constructor();
	gears_GetIndex();

	return 0;
}

uint16_t modIt(uint8_t min){
	return (min%5) * 64;
}

/**
	Tests that the face when it mods a minute colour, it produces the same color for 
	0, and any other divisible by 5.
*/
void face_ModMinColor(){
	cout<<"Testing Min Colour Modification ..."<<endl;
	
	//Construct Face
	Clock_Face* testFace = new Clock_Face();
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();
	int tstHr = 12;
	int tstSec = 36;

	setTime(tstHr,0,tstSec);
	time_t testTime = now();
		
	//5 Minute intervals should all be the same as modded with 0
	testFace->modMinColour(testTime,testRing);
	uint32_t moddedColor = testFace->minColour;
	uint32_t fiveMod_val = moddedColor; // Mod 0 should be the same for every 5 minute interval
	cout<<"5 min Color is: "<<fiveMod_val<<endl;

	for(int i = 5; i < 60; i += 5){
	
		//Setup time
		setTime(tstHr,i,tstSec);
		testTime = now();
		
		// mod min colour
		testFace->modMinColour(testTime,testRing);
		moddedColor = testFace->minColour;

		//Assert is the same as all other 5's
		assert(fiveMod_val == moddedColor);
	}
	
	cout<<"Mod Minute Color Tests Passed -- PASSED"<<endl;
	
}

int Clock_FaceTests(){
	cout<<"****************** TESTING FACE ****************************"<<endl;
	face_ModMinColor();
	return 0;
}


int ClockTests(){
	return 0;
}


int main(){
	cout<<"BEGINNING UNIT TESTS FOR CLOCK"<<endl;

	Clock_GearsTests();
	Clock_FaceTests();
	return 0;
}



