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
#targets 
.PHONEY: clean

all: watch_ADWatch clean
	@echo "********************* ADWatch & TESTS BUILT ************************"

clean:
	rm *.o

FUNC = ADWatch

# ADWATCH
SRCLIB = ./src

#ADWatch CI exe
watch_ADWatch: $(FUNC).o $(FUNC)_CI.o
	$(CC) $(CPPFLAGS) -o $(TESTDIR)/$(FUNC)_CI_TEST $(FUNC).o $(FUNC)_CI.o \
	-L$(MOCKLIBS) -lmock -L$(FUNCLIB) -ladwfunc -lc++

#CI for the base watch function
$(FUNC)_CI.o: $(SRCLIB)/$(FUNC)_CI.cpp $(SRCLIB)/$(FUNC)_CI.h
	@echo "********* STARTED $(FUNC)_CI BUILD ***************"
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) -I $(FUNCDIR)/Watch_Clock/src \
	-I $(FUNCDIR)/Watch_Compass/src -I $(FUNCDIR)/Watch_Speedometer/src \
	-I $(FUNCDIR)/Watch_Flashlight/src -I $(PROJDIR)/lib/ADWatch_GPS/src \
	$(SRCLIB)/$(FUNC)_CI.cpp 
	@echo "Created CI component for $(FUNC)."

$(FUNC).o: $(SRCLIB)/$(FUNC).cpp $(SRCLIB)/$(FUNC).h
	@echo "********* STARTED $(FUNC) BUILD ***************"
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) -I $(FUNCDIR)/Watch_Clock/src \
	-I $(FUNCDIR)/Watch_Compass/src -I $(FUNCDIR)/Watch_Speedometer/src \
	-I $(FUNCDIR)/Watch_Flashlight/src -I $(PROJDIR)/lib/ADWatch_GPS/src \
	$(SRCLIB)/$(FUNC).cpp 
	@echo "***************** Created $(FUNC)."



