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

#@echo "user is $(USER), OS is $(OS)"

# PathHelpers
PROJDIR = ./lib/ADWatch_Functions

all: watchFunctions
	@echo "********************* CI MAKE COMPLETE ************************"

watchFunctions: 
	$(MAKE) -C $(PROJDIR)
	



