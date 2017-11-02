//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: Arduino watch playground.

#include <iostream>
#include <ctime> //For testing purposes
#include "arrayTools.h"
#include "ledNode.h"

using namespace std ; 

//For test purposes!
void printArray(char charArr[]){
	int cap = getArrLen(charArr);
	
	for(int i = 0; i < cap; i++)
		cout<<charArr[i];
	cout<<endl;
	return;
}



int main() {
	cout<<"Begin Watch playground"<<endl;	

	cout<<"Testing instantiation"<<endl;

	ledNode* l = newLedNode();
	setNodeColour(120,12,220,l);
	nodeStats(l);

	cout<<"---------------------------------------"<<endl<<endl;
	
	cout<<"Testing Time Indexing and Array Flaggging"<<endl;

	//Testing time
	time_t now = time(0);
	tm* timeII = localtime(&now);
	char* strTime = ctime(&now);

	//Index Testing
	cout<<"Our current time is: " <<strTime<<endl;
	cout<<"Hour Index is: "<<(getHourIndex(timeII))<<endl;
 	cout<<"Minute Index is: "<<getMinuteIndex(timeII)<<endl;
	
	/*
		This is an interesting nugget. Please remember to assign it to a char* before you
		use your Array!*/
		
	//char ledSim[12];
	char* charArr = NULL;
	charArr = genTimeArray(timeII);
	
	cout<<"Length of the array is: "<< getArrLen(charArr)<<endl;

	printArray(charArr);
	
	cout<<"---------------------------------------"<<endl<<endl;
	
	
	
	cout<<"Now lets try it with the ledNodes!"<<endl<<endl;
	
	ledNode* ledArr = genNodeArray(timeII);
	
	//possible new way to check node stats. work on later!
	
	for(int i =0; i < 12; i++){
		int* nodeRGB = nodeStats(&ledArr[i]);
		cout<<" node: "<<i<<" r="<<nodeRGB[0]<<" g="<<nodeRGB[1]<<" b="<<nodeRGB[2]<<endl;
	}
	


return EXIT_SUCCESS; 
}
