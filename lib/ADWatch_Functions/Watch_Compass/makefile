#	Names: Bennett Lewis
#	Synopsis: Compass make
#   Date: February 15, 2020

CC = gcc #$(ARDUBIN)/tools/avr/bin/avrdude #-std=gnu++17
CPPFLAGS= -Wall -D CI -g #-n -V

# Get what OS they are on
PLATFORM := $(shell uname)
OS=$(shell uname -s)
ARCH=$(shell uname -m)
USER=$(shell whoami)

#NameHelpers
FUNC = NOTHING

#targets 
.PHONEY: clean

all: watch_compass libCompass clean
	@echo "*************************** COMPASS & TESTS BUILT *********************************"

clean:
	rm *.o

# COMPASS
SRCLIB = ./src
FUNC = Compass

#Compass CI exe
watch_compass: $(FUNC)_Magnet.o $(FUNC)_Needle.o $(FUNC).o $(FUNC)_CI.o  
	$(CC) $(CPPFLAGS)  -o $(TESTDIR)/Watch_Compass_CI.out $(FUNC)_CI.o $(FUNC)_Magnet.o $(FUNC)_Needle.o $(FUNC).o \
	-L $(MOCKLIBS) $(LDFLAGS)


#libCompass
lib$(FUNC): $(FUNC).o $(FUNC)_Magnet.o $(FUNC)_Needle.o
	@echo "************** Making libAD$(FUNC)"
	ar -rv $(MOCKLIBS)/Function_Lib/libAD$(FUNC).a $(FUNC).o $(FUNC)_Magnet.o $(FUNC)_Needle.o
	cp $(FUNC).o $(FUNC)_Magnet.o $(FUNC)_Needle.o $(MOCKLIBS)/Function_Lib	
	@echo "************** libADC$(FUNC) made"

#CI
$(FUNC)_CI.o: $(FUNC)_CI.cpp $(FUNC)_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(FUNC)_CI.cpp 
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

