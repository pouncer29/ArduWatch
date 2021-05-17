//
// Created by F.B.W on 2019-07-23.
//

#include "ADbug.h"

int32_t debugColour;
bool verbose = false;

/*Setters*/

/*sets the colour to use for debugging*/
void setDebugColour(uint32_t debugC){
	debugColour = debugC;
}

/* Sets verbosity */
void setVerbose(bool v){
	verbose = v;
}

/***************** RANDOMIZERS ********************/
float randFloat(int lower, int upper){
  	float randFloat = random(lower,upper);
	if(verbose)
		printFloat("Random Float",randFloat);
  	return randFloat;
}
/************** END RANDOMIZERS ******************/

/********* PRINTERS ****************/

/*print gps stats*/
void printGPS(Adafruit_GPS g){
  struct Ser Serial;
  if(g.fix == true){
   // debugOut(15);
    Serial.print("Quality: ");Serial.println(g.fixquality);
    Serial.print("Time: ");
    Serial.print(g.hour, DEC); Serial.print(':');Serial.print(g.minute, DEC); Serial.print(':');Serial.print(g.seconds, DEC); Serial.println('.');
    Serial.print("Longitude: ");Serial.println(g.longitude, 4);
    Serial.print("Longitude Degrees: ");Serial.print(g.longitudeDegrees, 4);Serial.println(g.lon);
    Serial.print("Angle: ");Serial.println(g.angle);
    Serial.print("Speed (kn): "); Serial.println(g.speed);
    Serial.print("Speed (kmph): "); Serial.println((float) (g.speed * 1.852));
    Serial.print("Satellites: "); Serial.println((int) g.satellites);
  } else {
    Serial.println("GPS: NO SIGNAL");
  }
}

/* printTime*/
void printTime(time_t tm){
  struct Ser Serial;
  Serial.print("Time is: ");Serial.print(hour(tm));Serial.print(":");Serial.print(minute(tm));Serial.print(":");Serial.println(second(tm));
}

/*Prints a float with a lable*/
void printFloat(char lable[], float value){
  struct Ser Serial;
  Serial.print(lable);Serial.print(" is: ");Serial.println(value);
}

/****************** END PRINTERS **************************/

/********* OUTPUTS *******************/

/** Writes testColor to the specified index on the ring
 	Returns: 
	0 on success, 
	1 on null ring, 
	2 on invalid index
*/
int writeToRing(Adafruit_NeoPixel* ring, int stopIdx){
	if(NULL == ring){
		return 1;
	} else if (stopIdx > 11){
		return 2;
	}

 	ring->clear();
	ring->show();
    for(int i = 0; i<stopIdx; i++){
      	ring->setPixelColor(i,debugColour);
      	ring->show();
    }
	return 0;
}

/** Sets a flag on the ring 
 	Returns: 
	0 on success, 
	1 on null ring, 
	2 on invalid index
*/
int setFlag(Adafruit_NeoPixel* ring,int index) {
	if(NULL == ring){
		return 1;
	} else if(index > 11){
		return 2;
	}


    if(NULL != ring){
        ring->setPixelColor(index,debugColour);
        ring->show();
    }
    return 0;
}

/** writes a code to the LEDs 
	returns 0 on success,
	1 on ivalid code
*/
int debugOut(int code){
	if(code > 15)
		return 1;
  
	byte v0 = 0;
  	byte v1 = 0;
  	byte v2 = 0;
  	byte v3 = 0;
  	if(code < 16){
    	/* Read fields*/
    	v0 = bitRead(code,0);
    	v1 = bitRead(code,1);
    	v2 = bitRead(code,2);
    	v3 = bitRead(code,3);
		  if(verbose){
  			struct Ser Serial;
    		Serial.print("Code: "); Serial.print(v3); Serial.print(v2); Serial.print(v1); Serial.println(v0);
		 }
  	}


  	/* Write Values*/
  	digitalWrite(PZero,v0);
  	digitalWrite(POne,v1);
  	digitalWrite(PTwo,v2);
  	digitalWrite(PThree,v3);
	return 0;
}
