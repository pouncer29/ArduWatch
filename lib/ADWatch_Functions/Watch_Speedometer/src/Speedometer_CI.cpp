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
	@Synopsis: Indexer Tests for the Speedometer (Gauge)
*/
int Gauge_Tests(){
	cout<<"*********************** TESTING GAUGE ***********************"<<endl;
	assert(false);
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



