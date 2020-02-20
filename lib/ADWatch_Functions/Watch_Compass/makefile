#	Names: Bennett Lewis
#	Synopsis: Compass make
#   Date: February 15, 2020

CC = gcc #$(ARDUBIN)/tools/avr/bin/avrdude #-std=gnu++17
CPPFLAGS= -Wall -D CI #-n -V

# Get what OS they are on
PLATFORM := $(shell uname)
OS=$(shell uname -s)
ARCH=$(shell uname -m)
USER=$(shell whoami)

# PathHelpers
MOCKLIBS = /Users/$(USER)/fGrams/Projects/ArduWatch/lib/Mock_Libs
PROJDIR = /Users/$(USER)/fGrams/Projects/ArduWatch/
TESTDIR = $(PROJDIR)/lib/ADWatch_CI_Tests

#NameHelpers
FUNC = NOTHING

#targets 
.PHONEY: clean

all: watch_compass clean
	@echo "*************************** COMPASS TESTS BUILT *********************************"

clean:
	rm *.o

# COMPASS
ARDULIBS = /Users/$(USER)/Documents/Arduino/libraries
SRCLIB = ./src
FUNC = Compass


watch_compass: $(FUNC)_Magnet.o $(FUNC)_Needle.o $(FUNC).o $(FUNC)_CI.o  
	$(CC) $(CPPFLAGS)  -o $(TESTDIR)/watch_Compass_CI $(FUNC)_CI.o $(FUNC)_Magnet.o $(FUNC)_Needle.o $(FUNC).o \
	-L $(MOCKLIBS) -lmock -lc++

#CI
$(FUNC)_CI.o: $(SRCLIB)/$(FUNC)_CI.cpp $(SRCLIB)/$(FUNC)_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) -I $(ARDULIBS)/Base_WatchFunction/src \
	$(SRCLIB)/$(FUNC)_CI.cpp 
	@echo "Created CI component for Compass."

#Compass Components
$(FUNC).o: $(SRCLIB)/$(FUNC).cpp $(SRCLIB)/$(FUNC).h 
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC).cpp 
	@echo "Gathering Compass..."

$(FUNC)_Needle.o: $(SRCLIB)/$(FUNC)_Needle.cpp $(SRCLIB)/$(FUNC)_Needle.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_Needle.cpp 
	@echo "Got Needle "

$(FUNC)_Magnet.o: $(SRCLIB)/$(FUNC)_Magnet.cpp $(SRCLIB)/$(FUNC)_Magnet.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_Magnet.cpp 
	@echo "Got Magnet"

