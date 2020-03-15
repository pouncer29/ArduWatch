#include "Adafruit_NeoPixel_MOCK.h"

struct colorNode{
	int r,g,b,w,c;
};

colorNode ring[12];

Adafruit_NeoPixel::Adafruit_NeoPixel(){}
Adafruit_NeoPixel::~Adafruit_NeoPixel(){}
void Adafruit_NeoPixel::show(void){};

void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b){
	ring[n].r = r;
	ring[n].g = g;
	ring[n].b = b;
}
void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b,uint8_t w){
	ring[n].r = r;
	ring[n].g = g;
	ring[n].b = b;
	ring[n].w = w;
}

void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint32_t c){
	ring[n].c = c;
}
void Adafruit_NeoPixel::setBrightness(uint8_t){}
void Adafruit_NeoPixel::clear(void)
{
	/*blank it
	for(int i = 0; i < 12;i++){
		this->setPixelColor(i,0);
		this->setPixelColor(i,0,0,0,0);
	}
	*/
}

int GetVal(int n, char select){
	if (select == 'r'){
		return ring[n].r;
	}else if (select == 'g'){
		return ring[n].g;
	}else if (select == 'b'){
		return ring[n].b;
	}else if (select == 'w'){
		return ring[n].w;
	}else if (select == 'c'){
		return ring[n].c;
	}
	return -1;

}



