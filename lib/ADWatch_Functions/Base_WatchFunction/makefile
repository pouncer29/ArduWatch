#	Names: Bennett Lewis
#	Synopsis: Base_WatchFunction make
#   Date: February 15, 2020

CC = gcc #$(ARDUBIN)/tools/avr/bin/avrdude #-std=gnu++17
CPPFLAGS= -Wall -D CI #-n -V

# Get what OS they are on
PLATFORM := $(shell uname)
OS=$(shell uname -s)
ARCH=$(shell uname -m)
USER=$(shell whoami)

#NameHelpers
FUNC = NOTHING

#targets 
.PHONEY: clean

all: base_watchFunction clean
	@echo "********************* BASE_WAATCHFUNCTION TESTS BUILT ************************"

clean:
	rm *.o

# FLASHLIGHT
ARDULIBS = /Users/$(USER)/Documents/Arduino/libraries
SRCLIB = ./src
FUNC = RingInterface
CI = Base_WatchFunction


base_watchFunction:  $(FUNC).o $(CI)_CI.o
	$(CC) $(CPPFLAGS) -o $(TESTDIR)/Base_WatchFunction_CI $(CI)_CI.o $(FUNC).o \
	-L $(MOCKLIBS) -lmock -lc++

#CI for the base watch function
$(CI)_CI.o: $(SRCLIB)/$(CI)_CI.cpp $(SRCLIB)/$(CI)_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(CI)_CI.cpp 
	@echo "Created CI component for $(CI)."

$(FUNC).o: $(SRCLIB)/$(FUNC).cpp $(SRCLIB)/$(FUNC).h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC).cpp 
	@echo "Created $(FUNC)."

