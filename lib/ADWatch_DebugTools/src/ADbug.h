//
// Created by F.B.W on 2019-07-23.
//

#ifndef ARDUWATCH_ADBUG_H
#define ARDUWATCH_ADBUG_H

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GPS.h>

class ADBug{

    //Attributes
    public:
    Adafruit_NeoPixel* ring;
    Adafruit_GPS* gps;

    int32_t Red;

    //Methods
    ADBug();
    ADBug(Adafruit_NeoPixel*);
    ADBug(Adafruit_GPS*);
    ADBug(Adafruit_GPS*,Adafruit_NeoPixel*);

    void setFlag(int,Adafruit_NeoPixel*);
    void setFlag(int);
};
#endif //ARDUWATCH_ADBUG_H
