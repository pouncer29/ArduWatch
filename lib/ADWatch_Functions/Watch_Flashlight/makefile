#	Names: Bennett Lewis
#	Synopsis: Flashlight make
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
CSTDLIB = /Applications/

#NameHelpers
FUNC = NOTHING

#targets 
.PHONEY: clean

all: watch_flashlight clean
	@echo "************************ FLASHLIGHT TESTS BUILT ******************************"

clean:
	rm *.o

# FLASHLIGHT
ARDULIBS = /Users/$(USER)/Documents/Arduino/libraries
SRCLIB = ./src
FUNC = Flashlight


watch_flashlight: $(FUNC).o $(FUNC)_CI.o mock_RI.o
	$(CC) $(CPPFLAGS) -o watch_flashlight_CI $(FUNC)_CI.o $(FUNC).o mock_RI.o \
	-L $(MOCKLIBS) -lmock -lc++

#CI for the funcometer
$(FUNC)_CI.o: $(SRCLIB)/$(FUNC)_CI.cpp $(SRCLIB)/$(FUNC)_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_CI.cpp 
	@echo "Created CI component for $(FUNC)."

$(FUNC).o: $(SRCLIB)/$(FUNC).cpp $(SRCLIB)/$(FUNC).h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) -I $(ARDULIBS)/Base_WatchFunction/src \
	$(SRCLIB)/$(FUNC).cpp 
	@echo "Created $(FUNC)."

mock_RI.o: $(MOCKLIBS)/RingInterface.cpp $(MOCKLIBS)/RingInterface.h
	$(CC) $(CPPFLAGS) -c -o mock_RI.o \
	-I $(MOCKLIBS) \
	$(MOCKLIBS)/RingInterface.cpp

