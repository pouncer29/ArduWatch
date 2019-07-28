//
// Created by F.B.W on 2019-07-23.
//

#ifndef ARDUWATCH_ADBUG_H
#define ARDUWATCH_ADBUG_H

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GPS.h>

public class ADBugger{

    //Attributes
    public:
    Adafruit_NeoPixel* ring;
    Adafruit_GPS* gps;

    int32_t Red;

    //Methods
    ADBugger();
    ADBugger(Adafruit_NeoPixel*);
    ADBugger(Adafruit_GPS*);
    ADBugger(Adafruti_GPS*,Adafruit_NeoPixel*);

    void setFlag(int,Adafruit_NeoPixel*);
};
#endif //ARDUWATCH_ADBUG_H
