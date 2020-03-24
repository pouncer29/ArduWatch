/*
Author: Ben Lewis
Date: February 18th, 2020

Synopsis: The tests for the speedometer
*/

#include "Speedometer_CI.h"
#include "Speed_Gauge.h"
#include "Speed_Dial.h"
#include <assert.h>
#include <iostream>

using namespace std;

//******************************************************************************
//Speedometer_CI
//******************************************************************************

/**
	@Synopsis: tests getter for cur speed
*/
void gauge_GetCurSpeed(){
	cout<<"Testing Gauge Get Speed"<<endl; 

	//Setup 
	float testSpeed = 25.4;
	Speed_Gauge* testGauge = new Speed_Gauge(testSpeed);
	
	//Check Construct
	assert(testGauge != NULL);

	float result = testGauge->getCurSpeed();

	//Check
	assert(result == testSpeed);

	cout<<"Gauge Get Speed -- PASSED"<<endl;

}

/**
	@Synopsis: tests update function for speed
*/
void gauge_UpdateSpeed(){
	cout<<"Testing Gauge Update Speed"<<endl; 

	//setup
	float testSpeed = 50.6;
	float newSpeed = 99.5;
	Speed_Gauge* testGauge = new Speed_Gauge(testSpeed);

	//Run
	testGauge->updateSpeed(newSpeed);
	
	//Grab
	float result = testGauge->getCurSpeed();

	//Check	
	assert(result != testSpeed);
	assert(result == newSpeed);

	cout<<"Gauge Update Speed -- PASSED"<<endl;
}


/**
	@Synopsis: tests indexer for cur speed
*/
void gauge_GetSpeedIndex(){
	cout<<"Testing Gauge Get Speed Index"<<endl; 
	//Setup 
	float testSpeed = 0.0;
	Speed_Gauge* testGauge = new Speed_Gauge(testSpeed);
	uint8_t result = 55;
	
	//Remember, the speeodmeter indexer starts at idx 6
	//Check
	// val -> idx

	// [0,19) -> 6
	cout<<"Testing heading [0km,20km) -> 6..."<<endl;
	for(float i = 0.0; i < 20.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 6);
	}
	
	// [20,40) -> 7
	cout<<"Testing heading [20km,40km) -> 7..."<<endl;
	for(float i = 20.0; i < 40.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 7);
	}

	// [40,60) -> 8
	cout<<"Testing heading [40km,60km) -> 8..."<<endl;
	for(float i = 40.0; i < 60.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 8);
	}
	// [60,80) -> 9
	cout<<"Testing heading [60km,80km) -> 9..."<<endl;
	for(float i = 60.0; i < 80.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 9);
	}


	// [80,100) -> 10
	cout<<"Testing heading [80km,100km) -> 10..."<<endl;
	for(float i = 80.0; i < 100.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 10);
	}

	// [100,120) -> 11
	cout<<"Testing heading [100km,120km) -> 11..."<<endl;
	for(float i = 100.0; i < 120.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 11);
	}

	// [120,140) -> 0
	cout<<"Testing heading [120km,140km) -> 0..."<<endl;
	for(float i = 120.0; i < 140.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 0);
	}

	// [140,160) -> 1
	cout<<"Testing heading [140km,160km) -> 1..."<<endl;
	for(float i = 140.0; i < 160.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 1);
	}

	// [160,180) -> 2
	cout<<"Testing heading [160km,180km) -> 2..."<<endl;
	for(float i = 160.0; i < 180.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 2);
	}

	// [180,200) -> 3
	cout<<"Testing heading [180km,200km) -> 3..."<<endl;
	for(float i = 180.0; i < 200.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 3);
	}

	// [200,220) -> 4
	cout<<"Testing heading [180km,200km) -> 4..."<<endl;
	for(float i = 200.0; i < 220.0; i+=0.5){
		//Set Speed
		testGauge->updateSpeed(i);
		
		//Get Index
		result = testGauge->getSpeedIndex();
		
		//Check
		assert(result == 4);
	}


	cout<<"Gauge Get Speed Index -- PASSED"<<endl;
}

/**
	@Synopsis: Indexer Tests for the Speedometer (Gauge)
*/
int Gauge_Tests(){
	cout<<"*********************** TESTING GAUGE ***********************"<<endl;
	gauge_GetCurSpeed();
	gauge_UpdateSpeed();
	gauge_GetSpeedIndex();
	return 0;
}

/**
	@Synopsis: Testing colour setup for the RingInterface
*/
void dial_Constructor(){
	cout<<"Testing Dial Constructor"<<endl;

	//Setup 
	Speed_Dial* testDial = new Speed_Dial();

	//Grab
	uint32_t regionA = testDial->regionAColour;
	uint32_t regionB = testDial->regionBColour;
	uint32_t regionC = testDial->regionCColour;
	
	//Not 0
	assert(regionA != 0);
	assert(regionB != 0);
	assert(regionC != 0);

	//Not the same
	assert(regionA != regionB && regionA != regionC);
	assert(regionB != regionC);
	
	
	cout<<"Dial Constructor -- PASSED"<<endl;
}

/**
	@Synopsis: Ring Interface tests for the Speedometer (Dial)
*/
int Dial_Tests(){
	cout<<"*********************** TESTING Dial ************************"<<endl;
	dial_Constructor();
	return 0;
}

/**
	@Synopsis Tests that the speedometer sets region A color properly.
*/
void speedo_SetRegionA(){
	cout<<"Testing Speedometer Set Region A"<<endl;
	//Setup
	Speedometer* testSpeedo = new Speedometer();
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();
	uint32_t regionAColour = testSpeedo->dial->regionAColour;

	//Grab
	uint32_t result = 0;

	//6
	testSpeedo->setRegionA(6,testRing);
	result = GetVal(6,'c');
	
	//Check
	assert(result == regionAColour);
	assert(GetVal(7,'c') == 0);
	assert(GetVal(8,'c') == 0);

	//8
	testSpeedo->setRegionA(8,testRing);
	result = GetVal(8,'c');

	//Check
	assert(result == regionAColour);
	assert(GetVal(7,'c') == regionAColour);
	assert(GetVal(6,'c') == regionAColour);
		
	cout<<"Speedometer Set Region A -- PASSED"<<endl;
}

/**
	@Synopsis Tests that the speedometer sets region B color properly.
*/
void speedo_SetRegionB(){
	cout<<"Testing Speedometer Set Region B"<<endl;
	//Setup
	Speedometer* testSpeedo = new Speedometer();
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();
	uint32_t regionBColour = testSpeedo->dial->regionBColour;

	//Grab
	uint32_t result = 0;

	//6
	testSpeedo->setRegionB(10,testRing);
	result = GetVal(9,'c');
	
	//Check
	assert(result == regionBColour);
	assert(GetVal(10,'c') == 0);
	assert(GetVal(11,'c') == 0);

	//11
	testSpeedo->setRegionB(12,testRing);
	result = GetVal(11,'c');

	//Check
	assert(result == regionBColour);
	assert(GetVal(9,'c') == regionBColour);
	assert(GetVal(10,'c') == regionBColour);
		
	cout<<"Speedometer Set Region B -- PASSED"<<endl;
}

/**
	@Synopsis Tests that the speedometer sets region C color properly.
*/
void speedo_SetRegionC(){
	cout<<"Testing Speedometer Set Region C"<<endl;
	//Setup
	Speedometer* testSpeedo = new Speedometer();
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();
	uint32_t regionCColour = testSpeedo->dial->regionCColour;

	//Grab
	uint32_t result = 0;

	//6
	testSpeedo->setRegionC(0,testRing);
	result = GetVal(0,'c');
	
	//Check
	assert(result == regionCColour);
	assert(GetVal(1,'c') == 0);
	assert(GetVal(2,'c') == 0);
	assert(GetVal(3,'c') == 0);
	assert(GetVal(4,'c') == 0);

	//8
	testSpeedo->setRegionC(4,testRing);
	result = GetVal(4,'c');

	//Check
	assert(result == regionCColour);
	assert(GetVal(0,'c') == regionCColour);
	assert(GetVal(1,'c') == regionCColour);
	assert(GetVal(2,'c') == regionCColour);
	assert(GetVal(3,'c') == regionCColour);
		
	cout<<"Speedometer Set Region C -- PASSED"<<endl;
}

/**
	@Synopsis: Checks that all regions are set properly
*/
void speedo_SetDial(){
	cout<<"Testing Speedometer Set Dial"<<endl;
	//Setup
	Speedometer* testSpeedo = new Speedometer();
	Adafruit_NeoPixel* testRing = new Adafruit_NeoPixel();
	uint32_t regionAColour = testSpeedo->dial->regionAColour;
	uint32_t regionBColour = testSpeedo->dial->regionBColour;
	uint32_t regionCColour = testSpeedo->dial->regionCColour;

	//Run
	//[6,9)
	testSpeedo->setDial(8,testRing);
	cout<<"Testing one Region set..."<<endl;
	//Region A set
	assert(GetVal(6,'c') == regionAColour);
	assert(GetVal(7,'c') == regionAColour);
	assert(GetVal(8,'c') == regionAColour);
	cout<<"Region A set..."<<endl;

	//[9,12)
	testSpeedo->setDial(11,testRing);
	cout<<"Testing two Region set..."<<endl;
	// Region A set
	assert(GetVal(6,'c') == regionAColour);
	assert(GetVal(7,'c') == regionAColour);
	assert(GetVal(8,'c') == regionAColour);
	cout<<"Region A set..."<<endl;
	// & Region B set
	assert(GetVal(9,'c') == regionBColour);
	assert(GetVal(10,'c') == regionBColour);
	cout<<"Region B set..."<<endl;

	//[0,4)
	cout<<"Testing full Region set..."<<endl;
	testSpeedo->setDial(0,testRing);
	// Region A set
	assert(GetVal(6,'c') == regionAColour);
	assert(GetVal(7,'c') == regionAColour);
	assert(GetVal(8,'c') == regionAColour);
	cout<<"Region A set..."<<endl;
	// & Region B set
	assert(GetVal(9,'c') == regionBColour);
	assert(GetVal(10,'c') == regionBColour);
	assert(GetVal(11,'c') == regionBColour);
	cout<<"Region B set..."<<endl;
	// & Region C set
	assert(GetVal(0,'c') == regionCColour);
	assert(GetVal(1,'c') == regionCColour);
	assert(GetVal(2,'c') == regionCColour);
	assert(GetVal(3,'c') == regionCColour);
	cout<<"Region C set..."<<endl;
	
	cout<<"Speedometer SetDial -- PASSED"<<endl;
}

/**
	@Synopsis: Checks speed setter
*/
void speedo_SetSpeed(){
	cout<<"Testing Speedometer Set Speed "<<endl;
	assert(false);
	cout<<"Speedometer SetSpeed -- PASSED"<<endl;
}

/**
	@Synopsis: Checks that speed is set and dial is good.
*/
void speedo_TrackSpeed(){
	cout<<"Testing Speedometer Track Speed"<<endl;
	assert(false);
	cout<<"Speedometer TrackSpeed -- PASSED"<<endl;
}

/**
	@Synopsis: Tests for the speedometer controller
*/
int Speedometer_Tests(){
	cout<<"******************** TESTING SPEEDOMETER ********************"<<endl;
	speedo_SetRegionA();
	speedo_SetRegionB();
	speedo_SetRegionC();
	speedo_SetDial();
	speedo_SetSpeed();
	speedo_TrackSpeed();
	return 0;
}

int main(){
	cout<<"*********** BEGINNING UNIT TESTS FOR SPEEDOMETER ************"<<endl;
	Gauge_Tests();
	Dial_Tests();
	Speedometer_Tests();
	return 0;
}



