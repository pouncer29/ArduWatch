#include "Adafruit_GPS_MOCK.h"

Adafruit_GPS::Adafruit_GPS()
{
	this->fix = false;
	this->angle = 0;
	this->longitudeDegrees = 102.2;
	this->hour = 0;
	this->minute= 0;
	this->seconds= 0;
	this->day= 21;
	this->month= 2;
	this->year = 2020;
}

void Adafruit_GPS::SetTime(uint8_t hr, uint8_t min, uint8_t sec){
	this->hour = hr;
	this->minute = min;
	this->seconds = sec;
}

void Adafruit_GPS::SetSpeed(float s){
	this->speed = s; // IN Knots
}

void Adafruit_GPS::SetLongitude(float l){
	this->longitudeDegrees = l;
}

void Adafruit_GPS::SetAngle(float d){
	this->angle = d;
}

void Adafruit_GPS::SetFix(bool f){
	this->fix = f;
}

Adafruit_GPS::~Adafruit_GPS(){}



