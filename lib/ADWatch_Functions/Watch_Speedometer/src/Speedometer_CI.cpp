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
	assert(false);
	//Setup 
	float testSpeed = 0.0;
	Speed_Gauge* testGauge = new Speed_Gauge(testSpeed);
	
	//Remember, the speeodmeter indexer starts at idx 6
	//Check
	// val -> idx
	//testSpeed->
	// [0,19) -> 6
	// [20,40) -> 7
	// [40,60) -> 8
	// [60,80) -> 9
	// [80,100) -> 10
	// [100,120) -> 11
	// [120,140) -> 0
	// [120,160) -> 1
	// [120,180) -> 3
	// [180,200) -> 4
	

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
	@Synopsis: Ring Interface tests for the Speedometer (Dial)
*/
int Dial_Tests(){
	cout<<"*********************** TESTING Dial ************************"<<endl;
	assert(false);
	return 0;
}

/**
	@Synopsis: Tests for the speedometer controller
*/
int Speedometer_Tests(){
	assert(false);
	return 0;
}

int main(){
	cout<<"*********** BEGINNING UNIT TESTS FOR SPEEDOMETER ************"<<endl;
	Gauge_Tests();
	Dial_Tests();
	Speedometer_Tests();
	return 0;
}



