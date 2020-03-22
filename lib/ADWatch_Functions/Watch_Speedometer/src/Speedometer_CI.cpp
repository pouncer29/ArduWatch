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



