
CC = gcc
CPPFLAGS = -Wall
USER = $(shell whoami)

#paths
# BaseWatch = /Users/$(USER)/fGrams/Projects/ArduWatch/lib/ADWatch_Functions/Base_WatchFunction/src
ARDUBIN = /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino

#targets
.PHONEY: clean cleano cleana

all: libmock.a cleano


libmock.a: Mock_TimeLib.o Mock_NeoPixel.o Mock_RI.o #misc.o
	ar -rv libmock.a Mock_TimeLib.o Mock_NeoPixel.o Mock_RI.o #misc.o

#Mocked libs
Mock_TimeLib.o: TimeLib.cpp TimeLib.h
	$(CC) $(CPPFLAGS) -c -o Mock_TimeLib.o \
	-I. \
	TimeLib.cpp

Mock_NeoPixel.o: Adafruit_NeoPixel.cpp Adafruit_NeoPixel.h
	$(CC) $(CPPFLAGS) -c -o Mock_NeoPixel.o \
	-I. \
	Adafruit_NeoPixel.cpp

Mock_RI.o: RingInterface.cpp RingInterface.h
	$(CC) $(CPPFLAGS) -c -o Mock_RI.o \
	-I. \
	RingInterface.cpp


#All the ones we missed.
misc.o: misc.cpp misc.h
	$(CC) $(CPPFLAGS) -c \
	-I. \
	misc.cpp


cleano:
	rm *.o
cleana:
	rm *.a

clean: cleano cleana


