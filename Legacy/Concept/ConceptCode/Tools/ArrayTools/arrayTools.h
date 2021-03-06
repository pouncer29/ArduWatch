//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: Functions to display TEST array functions.
//			   These will likely only be handy for my char arr examples.

#include <iostream>
#include <ctime> //For testing purposes

///////////////
//Array Tools
///////////////
int getArrLen(char[]);

int getHourIndex(tm*);

int getMinuteIndex(tm*);

/*
 * populateTimeArray()
 *	- to be used as a mans of updating a time array without having to create a new one.
 *	  not really sure how memory works in .ino lang, also don't want to risk running out.
 */
void populateTimeArray(char* charArr, tm* localTime);




