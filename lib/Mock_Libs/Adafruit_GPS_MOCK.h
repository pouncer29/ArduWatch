#ifndef ADAFRUIT_GPS_M_H
#define ADAFRUIT_GPS_M_H

#include <cinttypes>
#include <time.h>

class Adafruit_GPS
{
 public:
	bool fix;
	float longitudeDegrees;
	float speed;
	float angle;
	int hour;
	int minute;
	int seconds;
	int day;
	int month;
	int year;

  Adafruit_GPS(void);
  ~Adafruit_GPS();

};

#endif

