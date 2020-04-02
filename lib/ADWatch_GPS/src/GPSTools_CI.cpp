/**
	Author: Ben Lewis
	Date: February 21st, 2020
	Synopsis: GPSTools CI Tests
*/

#include "GPSTools.h"
#include <TimeLib_MOCK.h>
#include <iostream>
#include <assert.h>

using namespace std;


//****************************************************************************************
//GPSTools_CI
//****************************************************************************************

/*
  @Synopsis: tests ability to grab time
 */
void gpsTools_GrabTime(){
	cout<<"Testing GPSTools GrabTime..."<<endl;
	//Setup
	Adafruit_GPS* testGPS = new Adafruit_GPS();
	GPSTools* testTools = new GPSTools(testGPS,0);
	uint8_t tstHr = 14;
	uint8_t tstMin = 22;
	uint8_t tstSec = 10;
	testGPS->SetFix(true);
	testGPS->SetTime(tstHr,tstMin,tstSec);	
	
	time_t result;

	//Call with...
		
	//UTC time
	testGPS->SetLongitude(0.0);	
	result = testTools->grabTime();	
	assert(result != 0);
	assert(now() == result);

	//SaskTime
	
	//Grab UTC 0
	testGPS->SetTime(0,0,0);	
	time_t utcNow = testTools->grabTime();
	
	//Setup Sask Time
	testTools = new GPSTools(testGPS,-6);
	testGPS->SetLongitude(-106.6);
	result = testTools->grabTime();	
	setTime(18,0,0);
	time_t saskTime = now();

	//Check We are Sask time with sask latitutde
	assert(result != 0);
	assert(result != utcNow);
	assert(result == saskTime);

	//No Fix
	testTools = new GPSTools(testGPS,-6);
	testGPS->SetFix(false);
	testGPS->SetLongitude(58.8);
	testGPS->SetTime(0,0,0);
	result = testTools->grabTime();

	//Check we did not ask Longitude for a new Timzone adjustment.
	assert(testTools->hasFix() == false);
	assert(result != 0);
	assert(result != utcNow);
	assert(result == saskTime);
	
	cout<<"GPSTools GrabTime -- PASSED"<<endl;
}

/*
  @Synopsis: Tests ability to grab speed (in knots)
 */
void gpsTools_GrabSpeed(){
	cout<<"Testing GPSTools GrabSpeed..."<<endl;

	//Setup
	Adafruit_GPS* testGPS = new Adafruit_GPS();
	GPSTools* testTools = new GPSTools(testGPS,0);
	testGPS->SetFix(false);
	float testSpeed = 10.799;
	testGPS->SetSpeed(testSpeed);

	float eps = 0.05;
	float result = 0.0;
	float expected = 0.0;
	float speed = -5.5;

	//Grab (No Fix)
	speed = testTools->grabSpeed();

	//Check
	result = abs(speed - expected);
	assert (result <= eps );

	//Grab(with fix)
	testGPS->SetFix(true);		

	//Check
	expected = 20.0;
	speed = testTools->grabSpeed();
	result = abs(speed - expected);
	assert(result <= eps);

	cout<<"GPSTools GrabSpeed -- PASSED"<<endl;
}

/*
  @Synopsis: Tests ability to grab heading
 */
void gpsTools_GrabHeading(){
	cout<<"Testing GPSTools GrabHeading..."<<endl;
	
	//Setup
	Adafruit_GPS* testGPS = new Adafruit_GPS();
	GPSTools* testTools = new GPSTools(testGPS,0);
	testGPS->SetFix(false);
	float testHeading = 80.034;
	testGPS->SetAngle(testHeading);

	float eps = 0.05;
	float result = 0.0;
	float expected = 0.0;
	float heading = -5.5;
	
	//Grab (No Fix)
	heading = testTools->grabHeading();
	expected = 0.0;
	result = abs(heading - expected);
	
	//Check
	assert(result <= eps);

	//Grab (With Fix)
	testGPS->SetFix(true);
	expected = testHeading;
	heading = testTools->grabHeading();
	result = abs(heading - expected);
	
	//Check
	assert(result <= eps);

	cout<<"GPSTools GrabHeading -- PASSED"<<endl;
}

/*
  @Synopsis: Tests for GPS Interface
 */
int GPSTools_Tests(){
	cout<<"********************* TESTING GPS ***********************"<<endl;
	gpsTools_GrabTime();
	gpsTools_GrabSpeed();
	gpsTools_GrabHeading();
	return 0;
}

/*
  @Synopsis: Tests for our GPS Tools
 */
int main(){
	cout<<"************* BEGINNING UNIT TESTS FOR GPS **************"<<endl;
	GPSTools_Tests();
	cout<<"******************* GPS TESTS PASSED ********************"<<endl;
	return 0;
}



