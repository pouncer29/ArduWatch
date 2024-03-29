/*
Author: Ben Lewis
Date: Feb 18th, 2020

Synopsis: outline for CI for Speedometer
*/
#ifndef SPEEDOMETER_CI_h
#define SPEEDOMETER_CI_h

#ifdef CI
	#include <Adafruit_NeoPixel_MOCK.h>
	#include <iostream>
	#include <assert.h>
	#include <Speedometer.h>
	#include <Speed_Gauge.h>
	#include <Speed_Dial.h>
#else
	#include <Adafruit_NeoPixel.h>
#endif


/** Speedometer_CI
   -----------
	Made for the CI of the Speedometer class
	
*/
class Speedometer_CI{};

int main();

#endif

