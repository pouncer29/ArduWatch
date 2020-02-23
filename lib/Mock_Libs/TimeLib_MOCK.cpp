/* Implementation of Timelib Mock*/
#include "TimeLib_MOCK.h"


time_t now(){
	time_t t = 0;
	return t;
}

void setTime(time_t t){
	return;
}

int hour(time_t t){
	return 0;
}

int minute(time_t){
	return 3;
}

int second(time_t){
	return 59;
}

void setTime(int hr, int min, int sec, int day, int month, int yr){
	return;
}


