#	Names: Bennett Lewis
#	Synopsis: Speedo make
#   Date: February 15, 2020

CC = gcc #$(ARDUBIN)/tools/avr/bin/avrdude #-std=gnu++17
CPPFLAGS= -Wall -D CI #-n -V

# Get what OS they are on
PLATFORM := $(shell uname)
OS=$(shell uname -s)
ARCH=$(shell uname -m)
USER=$(shell whoami)

# PathHelpers
ARDUBIN = /Applications/Arduino.app/Contents/Java/hardware
MOCKLIBS = /Users/$(USER)/fGrams/Projects/ArduWatch/lib/Mock_Libs
CSTDLIB = /Applications/

#NameHelpers
FUNC = NOTHING

#targets 
.PHONEY: clean

all: watch_speedometer clean
	@echo "************************ SPEEDOMETER TESTS BUILT ******************************"

clean:
	rm *.o

# SPEEDO
ARDULIBS = /Users/$(USER)/Documents/Arduino/libraries
SRCLIB = ./src
FUNC = Speed


watch_speedometer: $(FUNC)_Gauge.o $(FUNC)_Dial.o $(FUNC)ometer.o $(FUNC)ometer_CI.o  mock_RI.o
	$(CC) $(CPPFLAGS) -o watch_speedometer_CI $(FUNC)ometer_CI.o \
	$(FUNC)ometer.o $(FUNC)_Gauge.o $(FUNC)_Dial.o \
	-L $(MOCKLIBS) -lmock -lc++

#CI for the funcometer
$(FUNC)ometer_CI.o: $(SRCLIB)/$(FUNC)ometer_CI.cpp $(SRCLIB)/$(FUNC)ometer_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) -I $(ARDULIBS)/Base_WatchFunction/src \
	$(SRCLIB)/$(FUNC)ometer_CI.cpp 
	@echo "Created CI component for $(FUNC)ometer (groovy)."

#Speedometer Components
$(FUNC)ometer.o: $(SRCLIB)/$(FUNC)ometer.cpp $(SRCLIB)/$(FUNC)ometer.h 
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)ometer.cpp 
	@echo "Gathering $(FUNC)ometer..."

$(FUNC)_Dial.o: $(SRCLIB)/$(FUNC)_Dial.cpp $(SRCLIB)/$(FUNC)_Dial.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_Dial.cpp 
	@echo "Got Dial..."

$(FUNC)_Gauge.o: $(SRCLIB)/$(FUNC)_Gauge.cpp $(SRCLIB)/$(FUNC)_Gauge.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_Gauge.cpp 
	@echo "Got Gauge..."

mock_RI.o: $(MOCKLIBS)/RingInterface.cpp $(MOCKLIBS)/RingInterface.h
	$(CC) $(CPPFLAGS) -c -o mock_RI.o \
	-I $(MOCKLIBS) \
	$(MOCKLIBS)/RingInterface.cpp

