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
FUNC = NOTHING

#targets 
.PHONEY: clean

all: base_watchFunction clean #libbaseWF -- for later maybe 
	@echo "********************* BASE_WAATCHFUNCTION TESTS BUILT ************************"

clean:
	rm *.o

# BASE WATCH FUNCTION
SRCLIB = ./src
FUNC = RingInterface
CI = Base_WatchFunction

#CI for Base WF
base_watchFunction:  $(FUNC).o $(CI)_CI.o
	$(CC) $(CPPFLAGS) -o $(TESTDIR)/Base_WatchFunction_CI.out $(CI)_CI.o $(FUNC).o \
	-L $(MOCKLIBS) $(LDFLAGS)

#lib baseWF
libbaseWF: $(FUNC).o 
	@echo "************** Making libbaseWatchFunction"
	ar -rv $(MOCKLIBS)/Function_Lib/libbaseWF.a $(FUNC).o
	cp $(FUNC).o $(MOCKLIBS)/Function_Lib
	@echo "************** libbaseWatchFunction made"

#CI for the base watch function
$(CI)_CI.o: $(CI)_CI.cpp $(CI)_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(CI)_CI.cpp 
	@echo "Created CI component for $(CI)."

$(FUNC).o: $(SRCLIB)/$(FUNC).cpp $(SRCLIB)/$(FUNC).h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC).cpp 
	@echo "Created $(FUNC)."

