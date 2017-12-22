//   Name: Ben Lewis
//   Date: Dec 22nd, 2017
//   Synopsis: test file for ArduWatch

#include <iostream>
#include <ctime> //For testing purposes
#include "./Tools/ArrayTools/arrayTools.h"
#include "./Tools/LedNode/ledNode.h"


using namespace std ; 

//For test purposes!
void printArray(char charArr[]){
	int cap = getArrLen(charArr);
	
	for(int i = 0; i < cap; i++)
		cout<<charArr[i];
	cout<<endl;
	return;
}


/*
 * flourish()
 * All this really does is print the array with different symbols. I was hoping to 
 * simulate the processof the ring flourish but it isn't really that similar.
*/
void flourish(char* charTA){
	cout<<"wow so pretty"<<endl;
	printArray(charTA);
	return;	
}

/*
 * pullTime()
 * - grabs a fresh time and uses it to update char-time-array (CTA)
 * returns: nothing.
*/
void pullTime(char* oldCTA){
	
	time_t now = time(0);
	tm* updatedTime = localtime(&now);
	populateTimeArray(oldCTA, updatedTime);
	
	
	return;
	
}
	



int main() {
	cout<<"Playing wit Control Flow"<<endl;
	
	time_t now = time(0);
	tm* testTime = localtime(&now);
	
	char* timeArrC = genTimeArray(testTime);
	
	cout<<"Current Array"<<endl;
	printArray(timeArrC);
	cout<<endl;
	
	
	while(1){
		
		char choice;
		cout<<" d = displayTime, p = pullTime, b = batteryLife, q=quit"<<endl;
		
		cin>>choice;
		switch(choice){
			case 'd': flourish(timeArrC);break;
			case 'p': pullTime(timeArrC); break;
			case 'b': cout<<"showBatteryLife()"<<endl; break;
			case 'q': return EXIT_SUCCESS;
			}
		}

	return EXIT_FAILURE;
}
