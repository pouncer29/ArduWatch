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
	printArray(charTA);
	return;	
}

/*
 * pullTime()
 * - grabs a fresh time and uses it to update char-time-array (CTA)
 * returns: nothing.
*/
void pullTime(char* oldCTA){
	//Grab a new time
	time_t now = time(0);
	tm* updatedTime = localtime(&now);
	
	//Remake the array.
	populateTimeArray(oldCTA, updatedTime);
	return;
	
}
	



int main() {
	cout<<"Playing wit Control Flow"<<endl;
	
// 	time_t now = time(0);
// 	tm* testTime = localtime(&now);
	
	char* timeArrC = new char[12];
	
	pullTime(timeArrC);
	
	
	
	cout<<"Current Array"<<endl;
	printArray(timeArrC);
	cout<<endl;
	
	/*
	while(1){
		
		char choice;
		cout<<"d = displayTime, p = pullTime, b = batteryLife, q=quit"<<endl;
		
		cin>>choice;
		switch(choice){
			case 'd': flourish(timeArrC);break;
			case 'p': pullTime(timeArrC); break;
			case 'b': cout<<"showBatteryLife()"<<endl; break;
			case 'q': break;break;
			}
		}
	*/
	int i = 0;
	char x;
	//Could use while offButton not pressed in the real deal
	while(cin>>x){
		if(i>3)
			i = 0;

		switch(i){
			case 0 : cout<<"CHOICE 0"<<endl;break; // Track Time
			case 1 : cout<<"CHOICE 1"<<endl;break; // Compass
			case 2 : cout<<"CHOICE 2"<<endl;break; // Spedometer	
			case 3 : cout<<"CHOICE 3"<<endl;break; // Refresh
		}
		i++;
	}

	
	return EXIT_SUCCESS;
}
