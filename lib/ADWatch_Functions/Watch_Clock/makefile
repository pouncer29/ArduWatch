#	Names: Bennett Lewis
#	Synopsis: Clock make
#   Date: February 15, 2020

CC = gcc #$(ARDUBIN)/tools/avr/bin/avrdude #-std=gnu++17
CPPFLAGS= -Wall -D CI #-n -V

# Get what OS they are on
PLATFORM := $(shell uname)
OS=$(shell uname -s)
ARCH=$(shell uname -m)
USER=$(shell whoami)

WATCHENV = $(shell pwd)

ifeq ($(USER),runner)
MOCKLIBS = ../../Mock_Libs
else
MOCKLIBS = /Users/$(USER)/fGrams/Projects/ArduWatch/lib/Mock_Libs
endif

# PathHelpers
TESTDIR = $(PROJDIR)/lib/ADWatch_CI_Tests

#NameHelpers
FUNC = NOTHING

#targets 
.PHONEY: clean

all: showenv watch_clock clean
	@echo "************************ CLOCK TESTS BUILT ******************************"

clean:
	rm *.o

showenv: 
	@echo "*********** CLOCK **** PWD is: $(WATCHENV) projdir is $(PROJDIR) Mockdir is $(MOCKLIBS)"
	

# CLOCK
ARDULIBS = /Users/$(USER)/Documents/Arduino/libraries
SRCLIB = ./src
FUNC = Clock


watch_clock: $(FUNC)_Gears.o $(FUNC)_Face.o $(FUNC).o $(FUNC)_CI.o  
	$(CC) $(CPPFLAGS) -o $(TESTDIR)/Watch_Clock_CI $(FUNC)_CI.o $(FUNC)_Gears.o $(FUNC)_Face.o $(FUNC).o \
	-L $(MOCKLIBS) -lmock -lc++

#CI
$(FUNC)_CI.o: $(SRCLIB)/$(FUNC)_CI.cpp $(SRCLIB)/$(FUNC)_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) -I $(ARDULIBS)/Base_WatchFunction/src \
	$(SRCLIB)/$(FUNC)_CI.cpp 
	@echo "Created CI component"


#Clock Components
$(FUNC).o: $(SRCLIB)/$(FUNC).cpp $(SRCLIB)/$(FUNC).h 
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC).cpp 
	@echo "Gathering Clock..."

$(FUNC)_Face.o: $(SRCLIB)/$(FUNC)_Face.cpp $(SRCLIB)/$(FUNC)_Face.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_Face.cpp 
	@echo "Got Face!"

$(FUNC)_Gears.o: $(SRCLIB)/$(FUNC)_Gears.cpp $(SRCLIB)/$(FUNC)_Gears.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_Gears.cpp 
	@echo "Got Gears!"

#mock_RI.o: $(MOCKLIBS)/RingInterface_MOCK.cpp $(MOCKLIBS)/RingInterface_MOCK.h
#	$(CC) $(CPPFLAGS) -c -o mock_RI.o \
#	-I $(MOCKLIBS) \
#	$(MOCKLIBS)/RingInterface.cpp

