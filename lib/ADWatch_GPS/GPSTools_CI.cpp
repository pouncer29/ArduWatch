/**
	Author: Ben Lewis
	Date: February 21st, 2020
	Synopsis: GPSTools CI Tests
*/

#include "GPSTools_CI.h"
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
	Adafruit_GPS testGPS = Adafruit_GPS();
	GPSTools* testTools = new GPSTools(0);
	uint16_t tstHr = 14;
	uint16_t tstMin = 22;
	uint16_t tstSec = 10;
	uint16_t tstDay = 10;
	uint16_t tstMonth = 12;
	uint16_t tstYear = 2020;
	testGPS.SetFix(true);

	setTime(tstHr,tstMin,tstSec,tstDay,tstMonth,tstYear);
	time_t expected = now();
	time_t result;
	uint8_t success = 15;

	//Call with...
		
	//UTC time
	testGPS.SetLongitude(0.0);	
	success = testTools->grabTime(now(),0.0);
	result = now();
	//cout<<"GPS: "<<testGPS.hour<<":"<<testGPS.minute<<":"<<testGPS.seconds<<endl;
	//cout<<"NOW: "<<hour(now())<<":"<<minute(now())<<":"<<second(now())<<endl;
	assert(success == 0);
	assert(result != 0);
	assert(expected == result);

	//SaskTime
	
	//Grab UTC 0
	setTime(0,0,0,tstDay,tstMonth,tstYear);
	testGPS.SetTime(0,0,0);	
	testTools->grabTime(now(),0.0);
	time_t utcNow = now();
	
	//Setup Sask Time
	testTools = new GPSTools(-6);
	success = testTools->grabTime(now(),106.6);	
	result = now();
	setTime(18,0,0,tstDay,tstMonth,tstYear);
	time_t saskTime = now();

	//Check We are Sask time with sask latitutde
	assert(success == 0);
	assert(result != utcNow);
	assert(result == saskTime);

	//Data errors (Seems like the time library protects itelf from faulty times.
	/*
	setTime(25,65,6);
	testTools = new GPSTools(0);
	result = testTools->grabTime(now(),58.8);
	cout<<"result: "<<result<<endl;
	cout<<"NOW: "<<hour(now())<<":"<<minute(now())<<":"<<second(now())<<endl;

	assert(success != 0);
	*/
	
	cout<<"GPSTools GrabTime -- PASSED"<<endl;
}

/*
  @Synopsis: Tests ability to grab speed (in knots)
 */
void gpsTools_GrabSpeed(){
	cout<<"Testing GPSTools GrabSpeed..."<<endl;

	//Setup
	Adafruit_GPS testGPS = Adafruit_GPS();
	GPSTools* testTools = new GPSTools(0);
	testGPS.SetFix(false);
	float testSpeed = 10.799;
	testGPS.SetSpeed(testSpeed);

	float eps = 0.05;
	float result = 0.0;
	float expected = 0.0;
	float speed = -5.5;

	//Grab(with fix)
	testGPS.SetFix(true);		

	//Check
	expected = 20.0;
	speed = testTools->grabSpeed(testGPS.speed);
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
	Adafruit_GPS testGPS = Adafruit_GPS();
	GPSTools* testTools = new GPSTools(0);
	testGPS.SetFix(false);
	float testHeading = 80.034;
	testGPS.SetAngle(testHeading);

	float eps = 0.05;
	float result = 0.0;
	float expected = 0.0;
	float heading = -5.5;
	
	//Grab (With Fix)
	testGPS.SetFix(true);
	expected = testHeading;
	heading = testTools->grabHeading(testGPS.angle);
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



