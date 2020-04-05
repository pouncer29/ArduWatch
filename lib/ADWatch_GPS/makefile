#	Names: Bennett Lewis
#	Synopsis: Base_WatchFunction make
#   Date: February 15, 2020

CC = gcc #$(ARDUBIN)/tools/avr/bin/avrdude #-std=gnu++17
CPPFLAGS= -Wall -D CI -g #-n -V

# Get what OS they are on
PLATFORM := $(shell uname)
OS=$(shell uname -s)
ARCH=$(shell uname -m)
USER=$(shell whoami)

#NameHelpers
TOOL = NOTHING

#targets 
.PHONEY: clean

all: GPSTools libGPSTools clean
	@echo "********************* ADWATCH GPS TESTS BUILT ************************"

clean:
	rm *.o

# FLASHLIGHT
SRCLIB = ./src
TOOL = GPSTools

#CI
$(TOOL):  $(TOOL).o $(TOOL)_CI.o
	$(CC) $(CPPFLAGS) -o $(TESTDIR)/$(TOOL)_CI.out $(TOOL)_CI.o $(TOOL).o \
	-L $(MOCKLIBS) $(LDFLAGS)

#lib GPSTools
lib$(TOOL): $(TOOL).o 
	@echo "************** Making lib$(TOOL)"
	ar -rv $(MOCKLIBS)/Function_Lib/lib$(TOOL).a $(TOOL).o
	@echo "************** lib $(TOOL) made"

#CI for the gpsToools 
$(TOOL)_CI.o: $(TOOL)_CI.cpp $(TOOL)_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(TOOL)_CI.cpp 
	@echo "Created CI component for $(TOOL)."

# GPSTools object
$(TOOL).o: $(SRCLIB)/$(TOOL).cpp $(SRCLIB)/$(TOOL).h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(TOOL).cpp 
	@echo "Created $(TOOL)."

