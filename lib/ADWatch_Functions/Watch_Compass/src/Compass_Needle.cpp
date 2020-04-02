/*
	Author: Ben Lewis
	Date: May 10th, 2018
	
	Synopsis: Implementation for Compass_Needle.h
*/

#include <Compass_Needle.h>

/** Compass_Needle()

    @Synopsis: Assigns the special colours needed for the compass function.
              North Yellow, heading blue or someting.

 */
Compass_Needle::Compass_Needle(){
	
	//Define special Colours
	northColour = ring->Color(255,100,0,5);
	needleColour = ring->Color(221,224,208,0);
	blank = ring->Color(0,0,0,0);

}	
