//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: Arduino watch playground.

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
	
	charArr[0] = 'h'; //Somehow marks the pointer as an array.
	
	//Grab Indices
	int hr = getHourIndex(localTime);
	int min = getMinuteIndex(localTime);
	

	//Assign Values
	for(int i = 0; i < 12; i++){
		if (i==hr)
			charArr[i] = 'h'; 
		if (i==min)
			charArr[i] = 'm'; 
		if ((hr==min) && (min == i))
			charArr[i] = 'b';
		else
			charArr[i] = '-';
		}
		
		return charArr;
	}	





