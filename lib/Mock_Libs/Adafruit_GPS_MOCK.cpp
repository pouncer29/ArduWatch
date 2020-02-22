#include "Adafruit_GPS_MOCK.h"

Adafruit_GPS::Adafruit_GPS()
{
	this->fix = true;
	this->angle = 33.3;
	this->longitudeDegrees = 102.2;
	this->hour = 19;
	this->minute= 0;
	this->seconds= 50;
	this->day= 21;
	this->month= 2;
	this->year = 2020;
}
Adafruit_GPS::~Adafruit_GPS(){}



