#	Names: Bennett Lewis
#	Synopsis: Clock make
#   Date: February 15, 2020

CC = gcc #$(ARDUBIN)/tools/avr/bin/avrdude #-std=gnu++17
CPPFLAGS= -Wall -D CI -g #-n -V

# Get what OS they are on
PLATFORM := $(shell uname)
OS=$(shell uname -s)
ARCH=$(shell uname -m)
USER=$(shell whoami)

WATCHENV = $(shell pwd)
# PathHelpers

#NameHelpers
FUNC = NOTHING

#targets 
.PHONEY: clean

all: watch_clock libClock clean
	@echo "************************ CLOCK & TESTS BUILT ******************************"

clean:
	rm *.o

# CLOCK
SRCLIB = ./src
FUNC = Clock

#Create CI exe
watch_clock: $(FUNC)_Gears.o $(FUNC)_Face.o $(FUNC).o $(FUNC)_CI.o  
	$(CC) $(CPPFLAGS) -o $(TESTDIR)/Watch_Clock_CI.out $(FUNC)_CI.o $(FUNC)_Gears.o $(FUNC)_Face.o $(FUNC).o \
	-L $(MOCKLIBS) $(LDFLAGS)

#libClock 
lib$(FUNC): $(FUNC).o $(FUNC)_Face.o $(FUNC)_Gears.o
	@echo "************** Making libAD$(FUNC)"
	ar -rv $(MOCKLIBS)/Function_Lib/libAD$(FUNC).a $(FUNC).o $(FUNC)_Face.o $(FUNC)_Gears.o
	cp $(FUNC).o $(FUNC)_Face.o $(FUNC)_Gears.o $(MOCKLIBS)/Function_Lib
	@echo "************** libAD$(FUNC) made"

#CI
$(FUNC)_CI.o: $(FUNC)_CI.cpp $(FUNC)_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) -I $(PROJDIR)/lib/Base_WatchFunction/src \
	$(FUNC)_CI.cpp 
	@echo "Created CI component"

#Clock Components
$(FUNC).o: $(SRCLIB)/$(FUNC).cpp $(SRCLIB)/$(FUNC).h 
	@echo "Gathering Clock..."
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC).cpp 
	@echo "Clock Built......."

$(FUNC)_Face.o: $(SRCLIB)/$(FUNC)_Face.cpp $(SRCLIB)/$(FUNC)_Face.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) -I $(PROJDIR)/lib/Base_WatchFunction/src \
	$(SRCLIB)/$(FUNC)_Face.cpp 
	@echo "Got Face!"

$(FUNC)_Gears.o: $(SRCLIB)/$(FUNC)_Gears.cpp $(SRCLIB)/$(FUNC)_Gears.h
	@echo "MOCKLIBS IS $(MOCKLIBS)"
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_Gears.cpp 
	@echo "Got Gears!"


