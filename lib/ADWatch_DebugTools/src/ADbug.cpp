//
// Created by F.B.W on 2019-07-23.
//

#include "ADbug.h"

ADBug::ADBug(){
}
ADBug::ADBug(Adafruit_GPS* gps){
    this->gps = gps;
}
ADBug::ADBug(Adafruit_NeoPixel* ring){
    this->ring = ring;
    this->Red = ring->Color(255,0,0,0);
}

ADBug::ADBug(Adafruit_GPS* gps, Adafruit_NeoPixel* ring) {
    this->ring = ring;
    this->gps = gps;
    this->Red = ring->Color(255,0,0,0);
}

void ADBug::setFlag(int index, Adafruit_NeoPixel* aRing ) {
    this->Red = ring->Color(255,0,0,10);
    aRing->setPixelColor(index,Red);
    aRing->show();
}


void ADBug::setFlag(int index) {
    if(nullptr != this->ring){
        this->ring->setPixelColor(index,Red);
        this->ring->show();
    }

    return;

}
