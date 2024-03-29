/*
Author: Ben Lewis
Date: Feb 16th, 2020

Synopsis: outline for CI for Clock

*/
#ifndef CLOCK_CI_h
#define CLOCK_CI_h

#ifdef CI
	#include <Clock.h>
	#include <Clock_Gears.h>
	#include <Clock_Face.h>
	#include <TimeLib_MOCK.h>
	#include <Adafruit_NeoPixel_MOCK.h>
	#include <ctime>
	#include <iostream>
	#include <assert.h>
#endif

/** Clock_CI
   -----------
	Made for the CI of the clock class
	
*/
int main();

#endif

