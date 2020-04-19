//
// Created by F.B.W on 2019-07-23.
//

#ifndef ADBUG_H
#define ADBUG_H

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GPS.h>
#include <TimeLib.h>
#include <Arduino.h>

/***** REQUIRED PINS **********/
#define PZero 9
#define POne 10
#define PTwo 11
#define PThree 12

/**************** ADBUG TOOLS ********************
ADBUG tools works under the following assumptions:

* A Serial Connection has been established to enable prints.
* Pins [9,12] have been set to outputs for 4 lights such that P0 (9) is the Leas significant bit.

*/

//Attributes

//Methods
//Setters
void setDebugColour(uint32_t);
void setVerbose(bool);

//Randomizers
float randFloat(int,int);

//Printers
void printGPS(Adafruit_GPS);
void printTime(time_t);
void printFloat(char[],float);

//Outputs
int writeToRing(Adafruit_NeoPixel*,int);
int setFlag(Adafruit_NeoPixel*,int);
int debugOut(int);

#endif 
