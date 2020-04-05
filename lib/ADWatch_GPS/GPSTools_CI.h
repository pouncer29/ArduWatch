/**
	Author: Ben Lewis
	Date: February 21st, 2020
	Synopsis: GPSTools CI Tests
*/
#ifndef GPSTOOLS_CI_H
#define GPSTOOLS_CI_H

#ifdef CI
	#include <GPSTools.h>
	#include <TimeLib_MOCK.h>
	#include <iostream>
	#include <cmath>
	#include <assert.h>
#endif

 
int main();

#endif
