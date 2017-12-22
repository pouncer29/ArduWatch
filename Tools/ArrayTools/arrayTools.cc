//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: implementation for arrayTools functions.

#include "arrayTools.h"


///////////////
//Array Tools
///////////////
int getArrLen(char charArr[]){
	int i = 0;
	while(charArr[i] != '\0')
		i++;
	return i;
}

int getHourIndex(tm* localTime){

	int curHour = localTime->tm_hour;

	if(curHour < 0)
		return -1;
	else if(curHour >= 12)
		return curHour - 12;
	else
		return curHour;
}

int getMinuteIndex(tm* localTime){
	int curMinute = localTime->tm_min;
	return curMinute/5;
}

char* genTimeArray(tm* localTime){

	char* charArr = new char[12];
	
	for(int i=0;i<12;i++)
		charArr[i] = '-';
		
	
	//Grab Indices
	int hr = getHourIndex(localTime);
	int min = getMinuteIndex(localTime);
	
	if(hr == min){
		charArr[min] = 'b';
		}
	else{
		charArr[hr] = 'h';
		charArr[min] = 'm';
		}
	
		
	return charArr;
}	


/*
 * populateTimeArray()
 *	- to be used as a mans of updating a time array without having to create a new one.
 *	  not really sure how memory works in .ino lang, also don't want to risk running out.
 */
void populateTimeArray(char* charArr, tm* localTime){
	
	for(int i=0;i<12;i++)
		charArr[i] = '-';
		
	
	//Grab Indices
	int hr = getHourIndex(localTime);
	int min = getMinuteIndex(localTime);
	
	if(hr == min){
		charArr[min] = 'b';
		}
	else{
		charArr[hr] = 'h';
		charArr[min] = 'm';
		}
	return;
}



