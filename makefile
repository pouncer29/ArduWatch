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
MOCKLIBS = $(PROJDIR)/lib/Mock_libs
TESTDIR = $(PROJDIR)/lib/ADWatch_CI_TESTS


export 

all: start mocklib watchFunctions
	@echo "********************* CI MAKE COMPLETE ************************"

start:
	export PROJDIR
	export MOCKDIR 
	export TESTDIR
	export FUNCDIR
	@echo "*********************** BEGINNING WATCH BUILD *****************"
	@echo "User: $(USER) OS: $(OS) PLATFORM: $(PLATFORM) ARCH: $(ARCH)"
	@echo "pwd is $(shell pwd) home is: $(shell ls $HOME) or $(shell ls ~)"
	@echo PROJDIR is $(PROJDIR)


mocklib:
	@echo "************************ MAKING MOCKLIB **************************"
	$(MAKE) -C $(MOCKLIBS)

watchFunctions: 
	$(MAKE) -C $(FUNCDIR)
	



