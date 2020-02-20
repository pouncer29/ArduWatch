
CC = gcc
CPPFLAGS = -Wall
USER = $(shell whoami)

#paths
# BaseWatch = /Users/$(USER)/fGrams/Projects/ArduWatch/lib/ADWatch_Functions/Base_WatchFunction/src
ARDUBIN = /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino
MOK = _MOCK
#targets
.PHONEY: clean cleano cleana

all: libmock.a cleano


libmock.a: Mock_TimeLib.o Mock_NeoPixel.o Mock_Arduino.o Mock_RI.o #misc.o
	ar -rv libmock.a Mock_TimeLib.o Mock_NeoPixel.o Mock_Arduino.o Mock_RI.o #misc.o

#Mocked libs
Mock_TimeLib.o: TimeLib$(MOK).cpp TimeLib$(MOK).h
	$(CC) $(CPPFLAGS) -c -o Mock_TimeLib.o \
	-I. \
	TimeLib$(MOK).cpp

Mock_NeoPixel.o: Adafruit_NeoPixel$(MOK).cpp Adafruit_NeoPixel$(MOK).h
	$(CC) $(CPPFLAGS) -c -o Mock_NeoPixel.o \
	-I. \
	Adafruit_NeoPixel$(MOK).cpp

Mock_Arduino.o: Arduino$(MOK).cpp Arduino$(MOK).h
	$(CC) $(CPPFLAGS) -c -o Mock_Arduino.o \
	-I. \
	Arduino$(MOK).cpp

Mock_RI.o: RingInterface$(MOK).cpp RingInterface$(MOK).h
	$(CC) $(CPPFLAGS) -c -o Mock_RI.o \
	-I. \
	RingInterface$(MOK).cpp

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


