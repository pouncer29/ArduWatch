#	Names: Bennett Lewis
#	Synopsis: Base_WatchFunction make
#   Date: February 19, 2020

#WATCH FUNCTIONS MAKEFILE

CC = gcc #$(ARDUBIN)/tools/avr/bin/avrdude #-std=gnu++17
CPPFLAGS= -Wall -D CI -g #-n -V

# Get what OS they are on
PLATFORM := $(shell uname)
OS=$(shell uname -s)
ARCH=$(shell uname -m)
USER=$(shell whoami)

all: watch_Functions base_watch run_tests
	@echo "********************* FUNCTION MAKE COMPLETE ************************"

watch_Functions: 
	@echo "********************* MAKING WATCH FUNCTIONS ************************"
	+$(MAKE) -C Watch_Clock
	+$(MAKE) -C Watch_Compass
	+$(MAKE) -C Watch_Speedometer
	+$(MAKE) -C Watch_Flashlight

base_watch:
	+$(MAKE) -C Base_WatchFunction

run_tests:
	@echo "************************Testing Watch****************************"
		$(TESTDIR)/Base_WatchFunction_CI
		$(TESTDIR)/Watch_Clock_CI
		$(TESTDIR)/Watch_Compass_CI
		$(TESTDIR)/Watch_Speedometer_CI
		$(TESTDIR)/Watch_Flashlight_CI
	
	



