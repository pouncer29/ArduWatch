/* Implementation of Arduino Mock*/
#include "Arduino_MOCK.h"
#include <iostream>
using namespace std;

int bitRead(int i, int p){
	return i & p;
}

void digitalWrite(int i, int j){
	return;
}

int delay(unsigned long delay){
	return 0;
}

int delay(int delay){
	return 0;
}

float random(int up, int low){
	return 0.0;
}

int delay(uint32_t  delay){
	return 0;
}

int digitalRead(uint8_t pin){
	if (pin % 2 == 0) {
		return LOW;
	}
	else{
		return HIGH;
	}
}

	

