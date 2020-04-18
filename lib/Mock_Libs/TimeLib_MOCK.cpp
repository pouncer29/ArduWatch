/* Implementation of Timelib Mock*/
#include "TimeLib_MOCK.h"

struct tm tstTm;

/**
 @synopsis: grabs the current time
*/
time_t now(){
	time_t t = mktime(&tstTm);
	return t;
}

/**
 @synopsis: does nothing right now.
*/
void setTime(time_t t){
	return;
}

/**
 @synopsis: grabs the hour for a time
*/
int hour(time_t t){
	return tstTm.tm_hour;
}

/**
 @synopsis: grabs the minute for a time
*/
int minute(time_t t){
	return tstTm.tm_min;
}

/**
 @synopsis: grabs the second for a time
*/
int second(time_t t){
	return tstTm.tm_sec;
}

/**
 @synopsis: grabs the day for a time
*/
int day(time_t t){
	return tstTm.tm_mday;
}

/**
 @synopsis: grabs the month for a time
*/
int month(time_t t){
	return tstTm.tm_mon;
}

/**
 @synopsis: grabs the year for a time
*/
int year(time_t t){
	return tstTm.tm_year;
}

/**
 @synopsis: Sets the time to the given date/time
*/
void setTime(int hr, int min, int sec, int day, int month, int yr){
	tstTm.tm_hour = hr;
	tstTm.tm_min = min;
	tstTm.tm_sec = sec;
	tstTm.tm_mday = day;
	tstTm.tm_mon = month;
	tstTm.tm_year = yr;
	
}

// Used to set up the environment for the tests.
void setTime(int hr, int min, int sec){
	tstTm.tm_hour = hr;
	tstTm.tm_min = min;
	tstTm.tm_sec = sec;
}


