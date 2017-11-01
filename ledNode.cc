//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: Arduino watch playground.

#include "ledNode.h"
//#include "arrayTools.h"

using namespace std ; 

//LedNodeStruct
// struct ledNode{
// 
// //Colours
// int r, g, b;
// 
// 
// };

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

void setBlueSecond(ledNode* node, int addMe){
	addMe += node->b;
	int g = node->g;
	
		//cout<<"about to make node blue value: "<<addMe<<endl;
	
	setNodeColour(30,g,addMe,node);
	
	return;
}

void setGreenMinute(ledNode* node, int addMe){
	addMe += node->g;
	
	int b = node->b;
	//cout<<"about to make node green value: "<<addMe<<endl;
	
	setNodeColour(30,addMe,b,node);
	
	return;
	}

void setAverageCross(ledNode* hrNode, ledNode*minNode){
	
	minNode->g = (hrNode->g + minNode->g) / 2;
	minNode->b = (hrNode->b + minNode->b) / 2;
	
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
	rgbArr[3] = node->b;
	
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
		setAverageCross(&nodeArr[hrIndex],&nodeArr[minIndex]);
	}
	else{
		setGreenMinute(&nodeArr[hrIndex], time->tm_min);
		setBlueSecond(&nodeArr[minIndex], time->tm_sec);
	}
	
	//if you wanna wolfFence and add a main...
	/*	
	nodeStats(&nodeArr[hrIndex]);
	nodeStats(&nodeArr[minIndex]);
	*/
	return nodeArr;
}
	
