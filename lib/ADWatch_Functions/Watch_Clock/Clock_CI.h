/*
Author: Ben Lewis
Date: Feb 16th, 2020

Synopsis: outline for CI for Clock

*/
#ifndef CLOCK_CI_h
#define CLOCK_CI_h

#include "./src/Clock.h"
#include "./src/Clock_Gears.h"
#include "./src/Clock_Face.h"
#include <TimeLib_MOCK.h>
#include <Adafruit_NeoPixel_MOCK.h>

#include <ctime>
#include <iostream>
#include <assert.h>

/** Clock_CI
   -----------
	Made for the CI of the clock class
	
*/
int main();

#endif

