#ifndef Gauge_h
#define Gauge_h

#include <Arduino.h>




/* Gauge
   --------------
	-
*/
class Gauge{
	public:	
		//Methods
		Gauge(float);
		float getCurSpeed(void);	
		uint8_t getSpeedIndex(void);
		void updateSpeed(float);		
			
	private:
	//Attributes
	float curSpeed; //Knots
};



#endif

