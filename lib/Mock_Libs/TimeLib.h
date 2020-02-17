#include<time.h>
#include<cinttypes>

time_t now();
void setTime(time_t t);
int hour(time_t t);
int minute(time_t);
int second(time_t);
void setTime(int hr, int min, int sec, int day, int month, int yr);
