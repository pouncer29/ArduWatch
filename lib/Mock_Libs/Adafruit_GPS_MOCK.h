#ifndef ADAFRUIT_GPS_M_H
#define ADAFRUIT_GPS_M_H

#include <cinttypes>
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
  void SetTime(uint8_t,uint8_t,uint8_t);
  void SetSpeed(float);
  void SetAngle(float);
  void SetLongitude(float);
  void SetFix(bool);
  ~Adafruit_GPS();

};


#endif

