//   Name: Ben Lewis
//   Date: Oct 29th, 2017
//   Synopsis: The Constructors, accessers and modifiers for the declared ledNode struct.

//#include <iostream>
#include <ctime>
#include "../ArrayTools/arrayTools.h"

using namespace std ; 

//LedNodeStruct
struct ledNode{

//Colours
int r, g, b;


};

//constructor
/*
* newLedNode()
* - the struct equivilent of a constructor
*
* precond: none
* postcond: new node declared and instantiated.
* return: a pointer to the new node.
*/
ledNode* newLedNode();

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
void setNodeColour(int,int,int,ledNode*);

void setBlueSecond(ledNode*,int);

void setGreenMinute(ledNode*,int);

void setAverageCross(ledNode*,ledNode*);


//Utilities
/*
* nodeStats(n)
* prints the stats of ledNode* n
* precond: n != NULL
* postcond: stats desplayed
* return: nothing 
*/
int* nodeStats(ledNode*);


void populateNodeArray(ledNode*,tm*);