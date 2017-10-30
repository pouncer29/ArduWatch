//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: Arduino watch playground.

#include <iostream>
#include <ctime> //For testing purposes
#include <array>

using namespace std ; 

//Structs
struct ledNode{

//Atributes

//Colours
int r, g, b;

//Time Range - We're going to try this out. If its a bust then oh well.
int minHour;
int maxHour;

int minMinute;
int maxMinute;

};

/*
* setNodeColour(r,g,b,n)
* - sets the colour of node n to the int r g b value paramaters.
* 
* preconditions:
* - n is not NULL
*
* postconditions:
* - the r g b attributes of n are changed
* return: nothing
*/
void setNodeColour(int r, int g, int b, ledNode* node){
	
	if(node == NULL){
		cout<<"node was NULL, exiting"<<endl;
		return;
	}

	node->r = r;
	node->g = g;
	node->b = b;
	return;
}

/*
* newLedNode()
* - the struct equivilent of a constructor
*
* precond: none
* postcond: new node declared and instantiated.
* return: a pointer to the new node.
*/
ledNode* newLedNode(){
	ledNode* node = new ledNode();
	setNodeColour(0,0,0,node);

	return node;
}
	

/*
* nodeStats(n)
* prints the stats of ledNode* n
* precond: n != NULL
* postcond: stats desplayed
* return: nothing 
*/
void nodeStats(ledNode* node){	
	
	if(node == NULL){
		cout<<"node was NULL, exiting"<<endl;
		return;
	}	
	cout<<"Colours were: "<<endl;
	cout<<"Red: "<<node->r<<endl;
	cout<<"Green: "<<node->g<<endl;
	cout<<"Blue: " <<node->b<<endl;
	return;
}

//////////////////////////////////////////////////////////////
//TIME HELPERS
/////////////////////////////////////////////////////////////

time_t getTimeZero(){
	time_t now = time(0);
	return now;
}

tm* getLocalTime(time_t* time){
	tm* localTime = localtime(time);
	return localTime;
}


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

void printArray(char charArr[]){
	int cap = getArrLen(charArr);
	
	for(int i = 0; i < cap; i++)
		cout<<charArr[i];
	cout<<endl;
	return;
}

char* genTimeArray(tm* localTime){

	char* charArr = new char[12];
	
	charArr[0] = 'h'; //Somehow marks the pointer as an array.
	
	//Grab Indices
	int hr = getHourIndex(localTime);
	int min = getMinuteIndex(localTime);
	
	// cout<<"In Generation Function"<<endl;
// 	cout<<" Hour Index is: "<<hr<<endl;
// 	cout<<" Minute Index is: "<<min<<endl;
// 	cout<<"Array is: "<<endl;
// 	//printArray(charArr);
 	cout<<"length is: "<<getArrLen(charArr)<<endl;
// 	
	//Assign Values
	for(int i = 0; i < 12; i++){
		if (i==hr)
			charArr[i] = 'h'; //cout<<"Tried hour!"<<endl;
		if (i==min)
			charArr[i] = 'm'; //cout<<"Tried Minut!"<<endl;
		if ((hr==min) && (min == i))
			charArr[i] = 'b';
		else
			charArr[i] = '-';
		}
		//printArray(charArr);
		return charArr;
	}	





	
int main() {
	cout<<"Begin Watch playground"<<endl;	

	cout<<"Testing instantiation"<<endl;

	ledNode* l = newLedNode();

	setNodeColour(120,12,220,l);
	nodeStats(l);


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
	char* ledArr = genTimeArray(timeII);
	
	cout<<"Length of the array is: "<< getArrLen(ledArr)<<endl;

	printArray(ledArr);


return EXIT_SUCCESS; 
}
