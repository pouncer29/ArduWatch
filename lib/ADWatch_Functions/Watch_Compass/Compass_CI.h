/*
Author: Ben Lewis
Date: Feb 16th, 2020

Synopsis: outline for CI for Compass

*/
#ifndef COMPASS_CI_h
#define COMPASS_CI_h

#ifdef CI
	#include <assert.h>
	#include <iostream>
	#include <Adafruit_NeoPixel_MOCK.h>
	#include <Compass.h>
	#include <Compass_Magnet.h>
	#include <Compass_Needle.h>
#else
	#include <Adafruit_NeoPixel.h>
#endif
	

/** Compass_CI
   -----------
	Made for the CI of the clock class
	
*/
class Compass_CI{};

int main();

#endif

