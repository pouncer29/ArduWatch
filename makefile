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
export PROJDIR := $(shell pwd)
export FUNCDIR := $(PROJDIR)/lib/ADWatch_Functions
export MOCKLIBS := $(PROJDIR)/lib/Mock_Libs
export TESTDIR := $(PROJDIR)/CI/ADWatch_CI_Tests
export FUNCLIB := $(MOCKLIBS)/Function_Lib

ifeq ($(OS),Linux)
	export LDFLAGS = -lmock -lstdc++
else ifeq ($(OS), Darwin)
	export LDFLAGS = -lmock -lc++
endif

all: start libs watchController
	@echo "*********************** CI MAKE COMPLETE ***************************"


.PHONEY: start all libs watchController

start:
	@echo "*********************** BEGINNING WATCH BUILD *****************"
	@echo "User: $(USER) OS: $(OS) PLATFORM: $(PLATFORM) ARCH: $(ARCH)"
	@echo "current dir is $(shell pwd)"
	@echo PROJDIR is $(PROJDIR)


libs: 
	@echo "*********************** CREATING LIBS ******************************"
	@echo "************************ MAKING MOCKLIB ****************************"
	$(MAKE) -C $(MOCKLIBS)
	@echo "************************ TOOLS AND FUNCTIONS MADE ******************"
	$(MAKE) -C $(FUNCDIR)
	$(MAKE) -C $(PROJDIR)/lib/ADWatch_GPS
	$(MAKE) -C $(PROJDIR)/lib/ADWatch_DebugTools
	@echo "************************ MAKING ADWFUNCLIB *************************"
	$(MAKE) -C $(FUNCLIB)
	@echo "************************** ALL LIBS MADE ***************************"

ifeq ($(OS),Darwin)
watchController:
	$(MAKE) -C $(PROJDIR)/lib/ADWatch_lib
else
watchController:
	@echo "**************** SKIPPING ADWATCH BUILD FOR $(OS) ******************"
endif


