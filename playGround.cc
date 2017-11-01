//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: Arduino watch playground.

#include <iostream>
#include <ctime> //For testing purposes
#include "arrayTools.h"

using namespace std ; 

//Structs
struct ledNode{

//Colours
int r, g, b;


};

//For test purposes!
void printArray(char charArr[]){
	int cap = getArrLen(charArr);
	
	for(int i = 0; i < cap; i++)
		cout<<charArr[i];
	cout<<endl;
	return;
}


//ledNode tools
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
	setNodeColour(30,195,195,node);	//Default node settings 60 + 195 = 255

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

	cout<<"Colours were: "<<endl;
	cout<<"Red: "<<node->r<<endl;
	cout<<"Green: "<<node->g<<endl;
	cout<<"Blue: " <<node->b<<endl;
	return;
}

void setBlueSecond(ledNode* node, int addMe){
	addMe += node->b;
	int g = node->g;
	
		cout<<"about to make node blue value: "<<addMe<<endl;
	
	setNodeColour(30,g,addMe,node);
	
	return;
}

void setGreenMinute(ledNode* node, int addMe){
	addMe += node->g;
	
	int b = node->b;
	cout<<"about to make node green value: "<<addMe<<endl;
	
	setNodeColour(30,addMe,b,node);
	
	return;
	}

void setAverageCross(ledNode* hrNode, ledNode*minNode){
	
	minNode->g = (hrNode->g + minNode->g) / 2;
	minNode->b = (hrNode->b + minNode->b) / 2;
	
	return;
	}
	
ledNode* genNodeArray(tm* time){
	
	ledNode* nodeArr = new ledNode[12];
	
	for(int i = 0; i < 12; i++)
		nodeArr[i] = *newLedNode();	

	
	int hrIndex = getHourIndex(time);
	int minIndex = getMinuteIndex(time);
	
	//Assign Values
	
	if(hrIndex==minIndex){
		
		setAverageCross(&nodeArr[hrIndex],&nodeArr[minIndex]);
		//setNodeColour(time->tm_hour,time->tm_min,time->tm_sec,&nodeArr[minIndex]);
	}
	else{
		// setNodeColour(time->tm_hour,time->tm_min,time->tm_sec,&nodeArr[hrIndex]);
// 		setNodeColour(0,128,0,&nodeArr[minIndex]);
		
		setGreenMinute(&nodeArr[hrIndex], time->tm_min);
		setBlueSecond(&nodeArr[minIndex], time->tm_sec);
	}
		
	nodeStats(&nodeArr[hrIndex]);
	nodeStats(&nodeArr[minIndex]);
	return nodeArr;
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
	


return EXIT_SUCCESS; 
}
