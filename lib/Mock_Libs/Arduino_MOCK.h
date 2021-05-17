#ifndef ARDUINO_M_H
#define ARDUINO_M_H

#include <cinttypes>

#define LOW 0x0
#define HIGH 0x1 
#define DEC 10
typedef unsigned char byte;

int digitalRead(uint8_t);
int delay(unsigned long);
int delay(int);
int delay(uint32_t);
float random(int,int);
int bitRead(int,int);
void digitalWrite(int,int);

struct Ser{
		/* Print int*/
		void print(int i){
			return;
		}

		void println(int i){
			return;
		}

		/* Print 2 int */
		void println(int i, int j){
			return;
		}

		void print(int i, int j){
			return;
		}

		/*print char*/
		void print(char c){
			return;
		}

		/*Print float*/
		void print(float f){
			return;
		}

		void println(float f){
			return;
		}

		/*Print Char array*/
		void print(char c[]){
			return;
		}

		void println(char c[]){
			return;
		}
};



#endif
