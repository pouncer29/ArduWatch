#ifndef Compass_Magnet_h
#define Compass_Magnet_h

#include <Arduino.h>




/* Magnet
   --------------
	- Contains methods to map a degree heading [0,360] to an array offset [0,11]
*/
class Magnet{
	public:	
		//Methods
		Magnet(float);
		float getCurHeading(void);	
		uint8_t getHeadingIndex(void);
		void updateHeading(float);		
			
	private:
	//Attributes
	float curHeading;
};



#endif

