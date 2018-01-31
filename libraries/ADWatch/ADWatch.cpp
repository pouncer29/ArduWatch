

#include "ADWatch.h"


ADWatch::ADWatch(time_t t, Adafruit_NeoPixel neoP){
	
	/**WILL COMPILE**/
	face = Face(neoP);
	gears = Gears(t);
}

void ADWatch::trackTime(time_t t){

  	gears.updateTime(t);

	uint8_t hrIdx  = gears.getHourIndex();
	uint8_t minIdx = gears.getMinuteIndex();
	uint8_t secIdx = gears.getSecondIndex();

	//Track minutes with minHand.
	face.modMinColour(t); 

	//Assign colours accordingly

	//Base case: No Overlap regualr 
	face.ring.setPixelColor(hrIdx,hrColour);
	face.ring.setPixelColor(minIdx,minColour);
	face.ring.setPixelColor(secIdx,secColour);

	// Otherwise: If Hands Cross, Their indicies will be the same so I average their set colours.
	//This particuairly nasty block is only so nasty because I take the average of an average. will work on shortening 
	if (secIdx == minIdx && minIdx == hrIdx)
		face.ring.setPixelColor(minIdx,face.getAverageCross((face.getAverageCross(face.secColour,face.minColour)),face.hrColour));
	else if(secIdx == minIdx)
		face.ring.setPixelColor(minIdx,face.getAverageCross(face.secColour,face.minColour));
	else if(secIdx == hrIdx)
		face.ring.setPixelColor(hrIdx,face.getAverageCross(face.secColour,face.hrColour));
	else if(hrIdx == minIdx)
		face.ring.setPixelColor(hrIdx, face.getAverageCross(face.hrColour,face.minColour));

  //Display 
  face.ring.show();
}
	