#So This is A Make File for the ArduWatch test (at least for now its just
#the test). It's Been awhile so be patient wit me!

CXX = g++
CXXFLAGS = -Wall -Wextra #if wextra is a dick then rm it

.PHONEY: test clean

default: test

all: test

#Targets
test: arrayTools.o ledNode.o testNodes.o
	$(CXX) $(CXXFLAGS) -o test arrayTools.o ledNode.o testNodes.o
	
#components
arrayTools.o: arrayTools.cc arrayTools.h
	$(CXX) $(CXXFLAGS) -c arrayTools.cc #Grabbing arrayTools
	
ledNode.o: ledNode.cc ledNode.h arrayTools.h
	$(CXX) $(CXXFLAGS) -c ledNode.cc #Grabbing ledNode
	
	
testNodes.o: testNodes.cc ledNode.h arrayTools.h 
	$(CXX) $(CXXFLAGS) -c testNodes.cc #Creating the PlayGround
	
clean:
	rm *.o #Getting rid of those pesky .o files
	



