
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
	@echo "************************ MADE LIBMOCK ***************************"


libmock.a: Mock_TimeLib.o Mock_NeoPixel.o Mock_Arduino.o Mock_RI.o #misc.o
	@echo "************** Making libmock"
	ar -rv libmock.a Mock_TimeLib.o Mock_NeoPixel.o Mock_Arduino.o Mock_RI.o #misc.o
	@echo "************** libmock made"

#Mocked libs
Mock_TimeLib.o: TimeLib$(MOK).cpp TimeLib$(MOK).h
	$(CC) $(CPPFLAGS) -c -o Mock_TimeLib.o \
	-I. \
	TimeLib$(MOK).cpp
	@echo "Made Mock Time..."

Mock_NeoPixel.o: Adafruit_NeoPixel$(MOK).cpp Adafruit_NeoPixel$(MOK).h
	$(CC) $(CPPFLAGS) -c -o Mock_NeoPixel.o \
	-I. \
	Adafruit_NeoPixel$(MOK).cpp
	@echo "Made Mock NeoPixel..."

Mock_Arduino.o: Arduino$(MOK).cpp Arduino$(MOK).h
	$(CC) $(CPPFLAGS) -c -o Mock_Arduino.o \
	-I. \
	Arduino$(MOK).cpp
	@echo "Made Mock Arduino..."

Mock_RI.o: RingInterface$(MOK).cpp RingInterface$(MOK).h
	$(CC) $(CPPFLAGS) -c -o Mock_RI.o \
	-I. \
	RingInterface$(MOK).cpp
	@echo "Made Mock Ring Interface..."


#All the ones we missed.
misc.o: misc.cpp misc.h
	$(CC) $(CPPFLAGS) -c \
	-I. \
	misc.cpp
	@echo "Made MISC..."


cleano:
	rm *.o
cleana:
	rm *.a

clean: cleano cleana


