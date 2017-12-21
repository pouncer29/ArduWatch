//   Name: Ben Lewis
//   Date: Nov 1st, 2017
//   Synopsis: implementation for ledNode struct operations.

#include "ledNode.h"

using namespace std ; 

//constructor
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

//ledNode setters
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
	preferably "addMe" is the value of seconds.
*/
void setMinRGB(ledNode* node, int addSeconds){
	addSeconds += node->b;
		
	//Could possibly forget about that 195 deal if no longer using seconds to determine b.
	setNodeColour(30,addSeconds,195,node);
	return;
}

/*
	sets the constant yellow hour hand.
*/
void setHourRGB(ledNode* node){
	setNodeColour(247,255,29,node);
	return;
	}

void setAverageCross(ledNode* hrNode, ledNode*minNode){
	
	minNode->g = (hrNode->g + minNode->g) / 2;
	//minNode->b = (hrNode->b + minNode->b) / 2;
	
	return;
	}


//Utilities
/*
* nodeStats(n)
* prints the stats of ledNode* n
* precond: n != NULL
* postcond: stats desplayed
* return: nothing 
*/
int* nodeStats(ledNode* node){	

	int* rgbArr = new int[3];

	rgbArr[0] = node->r;
	rgbArr[1] = node->g;
	rgbArr[2] = node->b;
	
	/*
	cout<<"Colours were: "<<endl;
	cout<<"Red: "<<node->r<<endl;
	cout<<"Green: "<<node->g<<endl;
	cout<<"Blue: " <<node->b<<endl;
	*/
	return rgbArr;
}

ledNode* genNodeArray(tm* time){
	
	ledNode* nodeArr = new ledNode[12];
	
	for(int i = 0; i < 12; i++)
		nodeArr[i] = *newLedNode();	

	
	int hrIndex = getHourIndex(time);
	int minIndex = getMinuteIndex(time);
	
	//Assign Values
	
	if(hrIndex==minIndex){
		//Get interesting values to average.
		setHourRGB(&nodeArr[hrIndex]);
		setMinRGB(&nodeArr[minIndex], time->tm_sec);
	
		//and average them
		setAverageCross(&nodeArr[hrIndex],&nodeArr[minIndex]);
	}
	else{
		// otherwise do a regualr assignment.
		setHourRGB(&nodeArr[hrIndex]);
		setMinRGB(&nodeArr[minIndex], time->tm_sec);
	}
	
	//if you wanna wolfFence and add a main...
	/*	
	nodeStats(&nodeArr[hrIndex]);
	nodeStats(&nodeArr[minIndex]);
	*/
	return nodeArr;
}
	
