//   Name: Ben Lewis
//   Date: Dec 26th, 2017
//   Synopsis: Basically NodeTools and ArrayTools combined.

#include "arduinoTools.h"

//Constructor for the new RGBW nodes
ledNode* newLedNode(){
	ledNode* node = new ledNode();
	// this may be set to 0. not sure which will work better or which will work at all.
	setNodeColour(50,195,195,50,node);	//Default node settings 60 + 195 = 255

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
void setNodeColour(uint8_t r, uint8_t g, uint8_t b, uint8_t w, ledNode* node){
	
	if(node == NULL){
		return;		//How Throw Error?
	}
	node->r = r;
	node->g = g;
	node->b = b;
	node->w = w;
	return;
}


/*
	sets the constant yellow hour hand.
*/
void setHourRGB(ledNode* node){
	setNodeColour(255,255,29,50,node);
	return;
}

/*
	sets constant green minute hand
*/
void setMinRGB(ledNode* node){
	setNodeColour(30,245,95,50,node);
	return;
}

/*
	sets the second to a blue that gets more white, hopefully as the minute progresses
*/
void setSecRGB(ledNode* node,time_t localTime){
	setNodeColour(56,94,234,(100 + second(localTime)), node);
	return;
}


/*
	when two ledNode indices occupy the same space, their color is averaged and displayed.
*/
void setAverageCross(ledNode* a, ledNode* b){
	
	a->r = (a->r + b->r) / 2;
	a->g = (a->g + b->g) / 2;
	a->b = (a->b + b->b) / 2;
	a->w = 50;
	
	return;
}



/*
 * populateNodeArray(ledNode[], tm*)
 * Takes a node array, and a time and populates it with the propper indices flagged.
 */
void populateNodeArray(ledNode* nodeArr, time_t localTime){

	//reset All Nodes to 0... not the 195 thing for now.
	for(int i = 0; i < 12; i++)
		setNodeColour(0,0,0,0,&nodeArr[i]);

	//Grab important indicies
	int hrIndex = getHourIndex(hour(localTime));
	int minIndex = getMinuteIndex(minute(localTime));
	int secIndex = getSecondIndex(second(localTime));
	
	//Set RGB values
	setHourRGB(&nodeArr[hrIndex]);
	setMinRGB(&nodeArr[minIndex]);	
	setSecRGB(&nodeArr[secIndex],localTime);
	
	//Hour Cross minutes
	if(hrIndex==minIndex)
		setAverageCross(&nodeArr[hrIndex],&nodeArr[minIndex]);
	
	//Hours Cross Seconds
	if(hrIndex==secIndex)
		setAverageCross(&nodeArr[hrIndex],&nodeArr[minIndex]);
	
	//Minutes Cross Seconds
	if(minIndex==secIndex)
		setAverageCross(&nodeArr[minIndex], &nodeArr[secIndex]);
		
	/*
		BUG: No average is set. when we initialize them all we are calling set avg with
		 	 two nodes that contain the same values...
	*/

	return;
}

/** Array Tools **/

/* get__Index()
* take in a time and spit out a corresponding array index/clock position.
*/
uint8_t getHourIndex(time_t localTime){

	uint8_t curHour = hour(localTime);

	if(curHour < 0)
		return -1;
	else if(curHour >= 12)
		return curHour - 12;
	else
		return curHour;
}

uint8_t getMinuteIndex(time_t localTime){
	uint8_t curMinute = minute(localTime);
	return curMinute/5;
}

uint8_t getSecondIndex(time_t localTime){
	uint8_t curSecond = second(localTime);
	return curSecond/5;
}


void pullTime(ledNode* oldNTA){
	//Grab a new time
	time_t updatedTime = now();
	
	//Remake the array.
	populateNodeArray(oldNTA, updatedTime);
	return;
	
}















