#	Names: Bennett Lewis
#	Synopsis: Base_WatchFunction make
#   Date: February 19, 2020

#WATCH FUNCTIONS MAKEFILE

CC = gcc #$(ARDUBIN)/tools/avr/bin/avrdude #-std=gnu++17
CPPFLAGS= -Wall -D CI #-n -V

# Get what OS they are on
PLATFORM=$(shell uname)
OS=$(shell uname -s)
ARCH=$(shell uname -m)
USER=$(shell whoami)


# PathHelpers
PROJDIR = $(shell pwd)
FUNCDIR = $(PROJDIR)/lib/ADWatch_Functions
MOCKLIBS = $(PROJDIR)/lib/Mock_Libs
TESTDIR = $(PROJDIR)/lib/ADWatch_CI_TESTS
FUNCLIB = $(MOCKLIBS)/Function_Lib


export 

all: start mocklib watchFunctions funclib
	@echo "********************* CI MAKE COMPLETE ************************"

start:
	export PROJDIR
	export MOCKDIR 
	export TESTDIR
	export FUNCDIR
	export FUNCLIB
	@echo "*********************** BEGINNING WATCH BUILD *****************"
	@echo "User: $(USER) OS: $(OS) PLATFORM: $(PLATFORM) ARCH: $(ARCH)"
	@echo "current dir is $(shell pwd)"
	@echo PROJDIR is $(PROJDIR)


mocklib:
	@echo "************************ MAKING MOCKLIB **************************"
	$(MAKE) -C $(MOCKLIBS)

watchFunctions: 
	$(MAKE) -C $(FUNCDIR)

funclib:
	@echo "************************ MAKING ADWFUNCLIB **************************"
	$(MAKE) -C $(FUNCLIB)
	
.PHONEY: start mocklib funclib watchFunctions all


