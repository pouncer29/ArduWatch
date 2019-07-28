//
// Created by F.B.W on 2019-07-23.
//

#include "ADbug.h"

ADBugger::ADBugger(){
}
ADBugger::ADBugger(Adafruit_GPS* gps){
    this->gps = gps;
}
ADBugger::ADBugger(ADafruit_NeoPixel* ring){
    this->ring = ring;
    this->Red = ring.Color(255,0,0,0);
}

ADBugger::ADBugger(Adafruti_GPS *, Adafruit_NeoPixel *) {
    this->ring = ring;
    this->gps = gps;
    this->Red = ring.Color(255,0,0,0);
}

void ADBugger::setFlag(int index, Adafruit_NeoPixel* aRing ) {
    this->Red = aRing.Color(255,0,0,0);
    aRing->setPixelColor(index,Red);
    aRing->show();
}
