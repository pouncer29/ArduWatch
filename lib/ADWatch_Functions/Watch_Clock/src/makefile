#	Names: Bennett Lewis
#	Synopsis: Clock make
#   Date: February 15, 2020

CC = gcc #$(ARDUBIN)/tools/avr/bin/avrdude #-std=gnu++17
CPPFLAGS= -Wall #-n -V

# Get what OS they are on
PLATFORM := $(shell uname)
OS=$(shell uname -s)
ARCH=$(shell uname -m)
USER=$(shell whoami)

# PathHelpers
ARDUBIN = /Applications/Arduino.app/Contents/Java/hardware
MOCKLIBS = /Users/$(USER)/fGrams/Projects/ArduWatch/lib/Mock_Libs
CSTDLIB = /Applications/

#NameHelpers
FUNCPREFIX = Watch_
FUNC = NOTHING
FUNCROOT = ADWATCH_Functions/

all: watch_clock
	@echo "Building Clock..."

# CLOCK
FUNC = Clock
FUNCPATH = $(FUNCROOT)$(FUNCPREFIX)$(FUNC)/"src"
ARDULIBS = /Users/$(USER)/Documents/Arduino/libraries

#reader-writer-test: reader-writer.o reader-writer-monitor.o monitor.o
#	$(CC) $(CFLAGS) -o reader-writer-test monitor.o reader-writer.o \
#	reader-writer-monitor.o -L /student/cmpt332/pthreads/lib/$(OS)$(ARCH) \
#	-L. -llist -lpthreads

watch_clock: $(FUNC)_Gears.o $(FUNC)_Face.o $(FUNC).o $(FUNC)_CI.o  mock_RI.o
	$(CC) $(CPPFLAGS) -o watch_clock_CI $(FUNC)_CI.o $(FUNC)_Gears.o $(FUNC)_Face.o $(FUNC).o \
	-L $(MOCKLIBS) -lmock  -lc++

#reader-writer.o: reader-writer.c
#	$(CC) $(CFLAGS) -c -I. -I /student/cmpt332/pthreads/ reader-writer.c

#-I /Applications/Arduino.app/Contents/Java/hardware/arduino\
	/avr/cores/arduino \

#CI

$(FUNC)_CI.o: $(FUNC)_CI.cpp $(FUNC)_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I. -I $(MOCKLIBS) -I $(ARDULIBS)/Base_WatchFunction/src \
	$(FUNC)_CI.cpp 
	@echo "Created CI component"


#Clock Components
$(FUNC).o: $(FUNC).cpp $(FUNC).h 
	$(CC) $(CPPFLAGS) -c \
	-I. -I $(MOCKLIBS) \
	$(FUNC).cpp 
	@echo "Gathering Clock..."

$(FUNC)_Face.o: $(FUNC)_Face.cpp $(FUNC)_Face.h
	$(CC) $(CPPFLAGS) -c \
	-I. -I $(MOCKLIBS) \
	$(FUNC)_Face.cpp 
	@echo "Got Face!"

$(FUNC)_Gears.o: $(FUNC)_Gears.cpp $(FUNC)_Gears.h
	$(CC) $(CPPFLAGS) -c \
	-I. -I $(MOCKLIBS) \
	$(FUNC)_Gears.cpp 
	@echo "Got Gears!"

mock_RI.o: $(MOCKLIBS)/RingInterface.cpp $(MOCKLIBS)/RingInterface.h
	$(CC) $(CPPFLAGS) -c -o mock_RI.o \
	-I $(MOCKLIBS) \
	$(MOCKLIBS)/RingInterface.cpp



#Make Clean
clean:
	rm *.o
