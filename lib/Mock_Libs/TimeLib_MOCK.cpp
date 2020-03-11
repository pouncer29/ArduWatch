/* Implementation of Timelib Mock*/
#include "TimeLib_MOCK.h"

struct tm tstTm;

time_t now(){
	time_t t = mktime(&tstTm);
	return t;
}

void setTime(time_t t){
	return;
}

int hour(time_t t){
	return tstTm.tm_hour;
}

int minute(time_t t){
	return tstTm.tm_min;
}

int second(time_t t){
	return tstTm.tm_sec;
}


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


