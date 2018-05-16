#ifndef Magnet_h
#define Magnet_h

#include <Arduino.h>




/* Magnet
   --------------
	- Contains methods to map a degree heading [0,360] to an array offset [0,11]
*/
class Magnet{
	public:	
		//Methods
		Magnet(float);
		uint8_t getCurHeading(void);	
		uint8_t getHeadingIndex(void);
		void updateHeading(float);		
			
	private:
	//Attributes
	float curHeading;
};



#endif

