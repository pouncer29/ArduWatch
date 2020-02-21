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
PROJDIR = ./lib/ADWatch_Functions


all: start watchFunctions
	@echo "********************* CI MAKE COMPLETE ************************"

start:
	@echo "*********************** BEGINNING WATCH BUILD *****************"
	@echo "User: $(USER) OS: $(OS) PLATFORM: $(PLATFORM) ARCH: $(ARCH)"
	@echo "pwd is $(shell pwd) home is: $(shell ls $HOME) or $(shell ls ~)"

watchFunctions: 
	$(MAKE) -C $(PROJDIR)
	


