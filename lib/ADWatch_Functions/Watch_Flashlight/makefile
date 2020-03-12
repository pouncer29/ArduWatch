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

#NameHelpers
FUNC = NOTHING

#targets 
.PHONEY: clean

all: watch_flashlight libFlashlight clean
	@echo "************************ FLASHLIGHT & TESTS BUILT ******************************"

clean:
	rm *.o

# FLASHLIGHT
ARDULIBS = /Users/$(USER)/Documents/Arduino/libraries
SRCLIB = ./src
FUNC = Flashlight

#Created Tests for Flashlight 
watch_flashlight: $(FUNC).o $(FUNC)_CI.o 
	$(CC) $(CPPFLAGS) -o $(TESTDIR)/Watch_Flashlight_CI.out $(FUNC)_CI.o $(FUNC).o \
	-L $(MOCKLIBS) $(LDFLAGS)

#libFlashlight
lib$(FUNC): $(FUNC).o 
	@echo "************** Making libAD$(FUNC)"
	ar -rv $(MOCKLIBS)/Function_Lib/libAD$(FUNC).a $(FUNC).o
	cp $(FUNC).o $(MOCKLIBS)/Function_Lib	
	@echo "************** libADC$(FUNC) made"

#CI for the flashlight
$(FUNC)_CI.o: $(SRCLIB)/$(FUNC)_CI.cpp $(SRCLIB)/$(FUNC)_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_CI.cpp 
	@echo "Created CI component for $(FUNC)."

$(FUNC).o: $(SRCLIB)/$(FUNC).cpp $(SRCLIB)/$(FUNC).h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC).cpp 
	@echo "Created $(FUNC)."

