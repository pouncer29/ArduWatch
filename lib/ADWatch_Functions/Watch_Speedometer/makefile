#	Names: Bennett Lewis
#	Synopsis: Speedo make
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

all: watch_speedometer libSpeed clean
	@echo "************************ SPEEDOMETER & TESTS BUILT ******************************"

clean:
	rm *.o

# SPEEDO
SRCLIB = ./src
FUNC = Speed

# Speedometer CI exe
watch_speedometer: $(FUNC)_Gauge.o $(FUNC)_Dial.o $(FUNC)ometer.o $(FUNC)ometer_CI.o
	$(CC) $(CPPFLAGS) -o $(TESTDIR)/Watch_Speedometer_CI.out $(FUNC)ometer_CI.o \
	$(FUNC)ometer.o $(FUNC)_Gauge.o $(FUNC)_Dial.o \
	-L $(MOCKLIBS) $(LDFLAGS)

#libSpeedometer
lib$(FUNC): $(FUNC)ometer.o $(FUNC)_Dial.o $(FUNC)_Gauge.o
	@echo "************** Making libAD$(FUNC)ometer"
	ar -rv $(MOCKLIBS)/Function_Lib/libAD$(FUNC)ometer.a $(FUNC)ometer.o \
	$(FUNC)_Dial.o $(FUNC)_Gauge.o
	cp $(FUNC)ometer.o $(FUNC)_Dial.o $(FUNC)_Gauge.o $(MOCKLIBS)/Function_Lib
	@echo "************** libADC$(FUNC)ometer made"


#CI for the funcometer
$(FUNC)ometer_CI.o: $(FUNC)ometer_CI.cpp $(FUNC)ometer_CI.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(FUNC)ometer_CI.cpp 
	@echo "Created CI component for $(FUNC)ometer (groovy)."

#Speedometer Components
$(FUNC)ometer.o: $(SRCLIB)/$(FUNC)ometer.cpp $(SRCLIB)/$(FUNC)ometer.h 
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)ometer.cpp 
	@echo "Gathering $(FUNC)ometer..."

$(FUNC)_Dial.o: $(SRCLIB)/$(FUNC)_Dial.cpp $(SRCLIB)/$(FUNC)_Dial.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_Dial.cpp 
	@echo "Got Dial..."

$(FUNC)_Gauge.o: $(SRCLIB)/$(FUNC)_Gauge.cpp $(SRCLIB)/$(FUNC)_Gauge.h
	$(CC) $(CPPFLAGS) -c \
	-I $(SRCLIB) -I $(MOCKLIBS) \
	$(SRCLIB)/$(FUNC)_Gauge.cpp 
	@echo "Got Gauge..."
