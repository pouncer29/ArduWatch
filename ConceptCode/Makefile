#So This is A Make File for the ArduWatch test (at least for now its just
#the test). It's Been awhile so be patient wit me!

CXX = g++
CXXFLAGS = -Wall -Wextra #if wextra is a dick then rm it

#Tools collections
ARRAYTOOLS = ./Tools/ArrayTools/
NODETOOLS = ./Tools/LedNode/

.PHONEY: test flow clean

default: test

all: test flow clean

#Targets
test: arrayTools.o ledNode.o testNodes.o
	$(CXX) $(CXXFLAGS) -o test arrayTools.o ledNode.o testNodes.o

flow: arrayTools.o ledNode.o testFlow.o
	$(CXX) $(CXXFLAGS) -o flowTest arrayTools.o ledNode.o testFlow.o
	
#components
arrayTools.o: $(ARRAYTOOLS)arrayTools.cc $(ARRAYTOOLS)arrayTools.h
	$(CXX) $(CXXFLAGS) -c $(ARRAYTOOLS)arrayTools.cc #Grabbing arrayTools
	
ledNode.o: $(NODETOOLS)ledNode.cc $(NODETOOLS)ledNode.h $(ARRAYTOOLS)arrayTools.h
	$(CXX) $(CXXFLAGS) -c $(NODETOOLS)ledNode.cc #Grabbing ledNode
	
	
testNodes.o: testNodes.cc $(NODETOOLS)ledNode.h $(ARRAYTOOLS)arrayTools.h 
	$(CXX) $(CXXFLAGS) -c testNodes.cc #Creating the PlayGround
	
clean:
	rm *.o #Getting rid of those pesky .o files
	



