/* Implementation of Arduino Mock*/
#include "Arduino_MOCK.h"

int delay(unsigned long delay){
	return 0;
}

int delay(int delay){
	return 0;
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

