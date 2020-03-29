/*
Author: Ben Lewis
Date: February 16th, 2020

Synopsis: Because Arduino code is tough to make with gcc,and all I want is a 
verified build, I've created this class. 
*/

#include "Clock_CI.h"

using namespace std;


//******************************************************************************
//Clock_CI
//******************************************************************************

/* CLOCK_GEARS TESTS */

/* TEST HOLDERS */

/** gears_Constructer*/
void gears_Constructor(){
	cout<<"Testing Gears Constructor..."<<endl;

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


/** 
	@Synopsis: Tests ability to update time
*/
void gears_UpdateTime(){
	cout<<"Testing Gears Update Time..."<<endl;
	
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

/** 
	@Synopsis: Tests for Index Retrival
*/
void gears_GetIndex(){
	cout<<"Testing Gears Get Index..."<<endl;
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

/**
	@Synopsis: Tests for the Index handler for the Clock
*/

int Clock_GearsTests(){
	cout<<"********************** TESTING GEARS ************************"<<endl;
	gears_Constructor();
	gears_GetIndex();

	return 0;
}

/**
	@Synopsis: Testing the ability to modify the minute colour on the Face

	Tests that the face when it mods a minute colour, it produces the same 
	color for 0, and any other divisible by 5.
*/
void face_ModMinColor(){
	cout<<"Testing Min Colour Modification..."<<endl;
	
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
	uint32_t fiveMod_val = moddedColor; //Mod 0 should be same for every 5th min 
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
	
	cout<<"Mod Minute Color Tests -- PASSED"<<endl;
	
}

/**
	@Synopsis: Tests for the Ring Interface of the Clock (Face)
*/
int Clock_FaceTests(){
	cout<<"************************ TESTING FACE ***********************"<<endl;
	face_ModMinColor();
	return 0;
}

/**
	@Synopsis: Testing track time for Clock
	clock_PlaceHands()
	- Checks the cases for place hands
		- disperse
		- overlap
		- Tail removal
*/
void clock_PlaceHands(){	

	//Setup
	cout<<"Testing Clock Place Hands..."<<endl;
	uint8_t hr = 0;
	uint8_t min = 0;
	uint8_t sec = 0;
	int avg = 0;
	int val = 0;

	Adafruit_NeoPixel* ring = new Adafruit_NeoPixel();
	Clock* testClock = new Clock();
	uint32_t hrColour = testClock->face->hrColour;
	uint32_t minColour = testClock->face->minColour;
	uint32_t secColour = testClock->face->secColour;

	//avg(avg(sec,min),hr)
	//Cross 0
	testClock->placeHands(hr,min,sec,ring);
	minColour = testClock->face->minColour;
	avg = ((minColour + secColour)/2 + hrColour)/2;
	val = GetVal(0,'c');
	assert(avg == val);
	cout<<"PlaceHands, overlap all 0 -- PASSED"<<endl;

	//Min/Sec overlap
	hr = 9;
	min = 0 ;
	sec = 0;
	testClock->placeHands(hr,min,sec,ring);
	minColour = testClock->face->minColour;
	avg = (minColour + secColour)/2;
	val = GetVal(0,'c');
	assert(avg == val);
	cout<<"PlaceHands, overlap min/sec 0 -- PASSED"<<endl;

	//Hour/Sec overlap
	hr = 0;
	min = 9 ;
	sec = 0;
	testClock->placeHands(hr,min,sec,ring);
	minColour = testClock->face->minColour;
	avg = (hrColour + secColour)/2;
	val = GetVal(0,'c');
	assert(avg == val);
	cout<<"PlaceHands, overlap hr/sec 0 -- PASSED"<<endl;

	//Hour/Min overlap
	hr = 9;
	min = 9 ;
	sec = 0;
	testClock->placeHands(hr,min,sec,ring);
	minColour = testClock->face->minColour;
	avg = (hrColour + minColour)/2;
	val = GetVal(9,'c');
	assert(avg == val);
	cout<<"PlaceHands, overlap hr/min idx:9 -- PASSED"<<endl;


	//Disperse
	hr = 3;
	min = 6 ;
	sec = 9;
	testClock->placeHands(hr,min,sec,ring);
	minColour = testClock->face->minColour;
	uint32_t ringColour_hr = GetVal(hr,'c');
	uint32_t ringColour_min = GetVal(min,'c');
	uint32_t ringColour_sec= GetVal(sec,'c');

	assert(ringColour_hr == hrColour);
	assert(ringColour_min == minColour);
	assert(ringColour_sec == secColour);
	
	cout<<"PlaceHands, Disperse hrIdx=3, minIdx=6, secIdx=9 -- PASSED"<<endl;

}

/**
	@Synopsis: Testing track time for Clock
*/
void clock_TrackTime(){
	cout<<"Testing Clock TrackTime..."<<endl;

	//Setup ring
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();

	//Setup time
	int tstHr = 0;
	int tstSec = 15;
	int tstMin = 45;
	setTime(tstHr,tstMin,tstSec);
	time_t testTime = now();

	//Construct
	Clock* testClock = new Clock();

	//Grab Colours 
	uint32_t hrColour = testClock->face->hrColour;
	uint32_t minColour = testClock->face->minColour;
	uint32_t secColour = testClock->face->secColour;

	//Call it!	
	testClock->trackTime(testTime,testRing);

	//Grab Resulting Colours
	uint32_t ringColour_hr = GetVal((tstHr % 12),'c');
	uint32_t ringColour_min = GetVal((tstMin % 12),'c');
	uint32_t ringColour_sec= GetVal((tstSec % 12),'c');

	/*
	cout<<"Hour,Min,Sec"<<endl;
	cout<<ringColour_hr<<","<<ringColour_min<<","<<ringColour_sec<<endl;
	cout<<hrColour<<","<<minColour<<","<<secColour<<endl;
	*/


	//Assert they were set
	assert(ringColour_hr == hrColour);
	assert(ringColour_min == minColour);
	assert(ringColour_sec == secColour);
	
	cout<<"TrackTime, Disperse hr=12, min=45, sec=15 -- PASSED"<<endl;
}

/**
	@Synopsis: Testing set time for Clock
*/
void clock_SetWatchTime(){
	cout<<"Testing Clock SetWatchTime..."<<endl;

	//Setup ring
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();

	//Setup time
	uint8_t tstHr = 6;
	uint8_t tstMin = 45;
	time_t testTime = now();

	//Construct
	Clock* testClock = new Clock();

	//Call it!
	testClock->setWatchTime(tstHr,tstMin,testTime,testRing);

	/*
	cout<<"Hour,Min,Sec"<<endl;
	cout<<ringColour_hr<<","<<ringColour_min<<","<<ringColour_sec<<endl;
	cout<<hrColour<<","<<minColour<<","<<secColour<<endl;
	*/

	//Grab Time...
	int hr = hour(now());
	int min = minute(now());
	int sec = second(now());
	
	//Assert time was set	
	assert(hr == tstHr);
	assert(min == tstMin);
	assert(sec == 0);

	cout<<"SetWatchTime, hr=6, min=45, sec=0(by default) -- PASSED"<<endl;

}

/**
	@Synopsis: Testing tail remove for Clock
*/
void clock_RemoveTail(){
	cout<<"Testing Clock RemoveTail..."<<endl;

	//Setup ring
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();

	//Setup time
	int tstHr = 0;
	int tstSec = 1;
	int tstMin = 2;
	uint32_t eraseMe = 999;
	uint32_t value = 0;
	int tstIdx = 0;

	//Construct
	Clock* testClock = new Clock();
	Clock_Face* testFace = new Clock_Face();
	uint32_t blank = testFace->blank;
	uint32_t secColour = testFace->secColour;
	
	//Setup clock
	setTime(tstHr,tstMin,tstSec);
	time_t testTime = now();
	testClock->trackTime(testTime,testRing);


	//TEST - Remove at index 11

	//Set colour
	testRing->setPixelColor(11,eraseMe);

	//Remove 
	tstIdx = tstHr-1;
	testClock->removeTail(tstIdx,tstHr,tstSec,tstMin,testRing);
	value = GetVal(11,'c');
	/*
	int TailIdx = -1 % 12;
	cout<<"Colours: Val: "<<value<<" blank: "<<blank<<"TailIdx: "<<TailIdx<<endl;
	*/
	
	//Assert was erased and is blank
	assert(value != eraseMe);
	assert(value == blank);
	
	cout<<"RemoveTail (11) , hrIdx=0, minIdx=1, secIdx=2 -- PASSED"<<endl;

	// TEST Important Index (do not remove 11)
	tstHr = 0;
	tstMin = 1;
	tstSec = 11;
	tstIdx = tstHr-1;

	setTime(tstHr,tstMin,tstSec);
	testTime = now();

	testRing = new Adafruit_NeoPixel();
	testClock->trackTime(testTime,testRing);
	testRing->setPixelColor(11,secColour);

	/*
	int hrC = GetVal(tstHr,'c');
	int minC = GetVal(tstMin,'c');
	int secC = GetVal(tstSec,'c');
	cout<<"Hour,Min,Sec"<<endl;
	cout<<hrC<<","<<minC<<","<<secc<<endl;
	*/
	
	testClock->removeTail(tstIdx,tstHr,tstMin,tstSec,testRing);
	value = GetVal(tstSec,'c');
	
	//Assert is not te original value, not 0, is SecColour	
	assert(value != eraseMe);
	assert(value != 0);
	assert(value == secColour);
	
	cout<<"RemoveTail (Important 11) , hrIdx=0, minIdx=1, secIdx=11 -- PASSED"<<endl;

	//At 1
	tstHr = 1;
	tstMin = 2;
	tstSec = 2;
	tstIdx = tstHr-1;

	setTime(tstHr,tstMin,tstSec);
	testTime = now();

	testRing = new Adafruit_NeoPixel();
	testClock->trackTime(testTime,testRing);
	testRing->setPixelColor(tstIdx,eraseMe);

	/*
	cout<<"Hour,Min,Sec"<<endl;
	cout<<hrC<<","<<minC<<","<<secC<<endl;
	*/
	
	testClock->removeTail(tstIdx,tstHr,tstMin,tstSec,testRing);
	value = GetVal(tstIdx,'c');

	//Assert is not te original value, not 0, is SecColour	
	assert(value != eraseMe);
	assert(value == blank);
	cout<<"RemoveTail (1) , hrIdx=1, minIdx=0, secIdx=0 -- PASSED"<<endl;
}

/**
@synopsis: Tests for the clock component controller
*/
int Clock_Tests(){
	cout<<"*********************** TESTING CLOCK ***********************"<<endl;
	clock_PlaceHands();
	clock_TrackTime();
	clock_SetWatchTime();
	clock_RemoveTail();
	return 0;
}

/**
	@Synopsis: Clock tests
*/
int main(){
	cout<<"*************** BEGINNING UNIT TESTS FOR CLOCK **************"<<endl;
	Clock_GearsTests();
	Clock_FaceTests();
	Clock_Tests();
	cout<<"********************* CLOCK TESTS PASSED ********************"<<endl;
	return 0;
}



