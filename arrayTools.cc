//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: Arduino watch playground.

//#include "arrayTools.h"
#include <ctime>

// time_t getTimeZero(){
// 	time_t now = time(0);
// 	return now;
// }
// 
// tm* getLocalTime(time_t* time){
// 	tm* localTime = localtime(time);
// 	return localTime;
// }


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





