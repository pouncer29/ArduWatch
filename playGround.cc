//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: Arduino watch playground.

#include <iostream>
#include <ctime> //For testing purposes
#include <typeinfo>

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

int getHour(tm* localTime){

	int curHour = localTime->tm_hour;

	if(curHour < 0)
		return -1;
	else if(curHour > 12)
		return curHour - 12;
	else
		return curHour;
	}

int main() {
	cout<<"Begin Watch playground"<<endl;	

	cout<<"Testing instantiation"<<endl;

	ledNode* l = newLedNode();

	setNodeColour(120,12,220,l);
	nodeStats(l);

	cout<<"Looks ok up to here! lets try it with time now!"<<endl<<endl;

	//Testing time
	time_t now = time(0);
	
	tm* timeII = localtime(&now);
	
	char* strTime = ctime(&now);

	cout<<"Our current time is: " <<strTime<<endl;
	cout<<"Hours are: "<<(getHour(timeII))<<endl;
	
	cout<<"type of Hrs is: "<<typeid(timeII->tm_hour).name()<<endl;

	


return EXIT_SUCCESS; 
}
