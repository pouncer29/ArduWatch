//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: Arduino watch playground.

#include <iostream>
#include <ctime> //For testing purposes


//////////////////////////////////////////////////////////////
//TIME HELPERS
/////////////////////////////////////////////////////////////

// time_t getTimeZero();
// 
// tm* getLocalTime(time_t* time);


///////////////
//Array Tools
///////////////
int getArrLen(char[]);

int getHourIndex(tm*);

int getMinuteIndex(tm*);

char* genTimeArray(tm*);


