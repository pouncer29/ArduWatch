#ifndef TIMELIB_M_H
#define TIMELIB_M_H

#include<ctime>
#include<cinttypes>

time_t now();
void setTime(time_t t);
int hour(time_t t);
int minute(time_t);
int second(time_t);
void setTime(int , int , int , int , int , int );
void setTime(int , int , int );

#endif
