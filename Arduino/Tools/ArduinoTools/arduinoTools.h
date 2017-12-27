//   Name: Ben Lewis
//   Date: Dec 26th, 2017
//   Synopsis: Basically NodeTools and ArrayTools combined.


//#include <ctime>
//#include <cstdint>
#include <TimeLib.h> // the arduino time Library.


using namespace std ; 

/**FROM NODE TOOLS **/

//LedNodeStruct
struct ledNode{
//Colours
uint8_t r, g, b, w;

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
void setNodeColour(uint8_t,uint8_t,uint8_t,uint8_t,ledNode*);

void setHourRGB(ledNode*);

void setMinRGB(ledNode*);

void setSecRGB(ledNode*,time_t);

void setAverageCross(ledNode*,ledNode*);

void populateNodeArray(ledNode*,time_t);



/**FROM ARRAY TOOLS **/
uint8_t getHourIndex(time_t);

uint8_t getMinuteIndex(time_t);

uint8_t getSecondIndex(time_t);


/**FROM FLOW TEST **/
void pullTime(ledNode*);