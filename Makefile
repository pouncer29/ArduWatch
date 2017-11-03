#So This is A Make File for the ArduWatch test (at least for now its just
#the test). It's Been awhile so be patient wit me!

CXX = g++
CXXFLAGS = -Wall -Wextra #if wextra is a dick then rm it

.PHONEY: test clean

default: test

all: test

#Targets
test: arrayTools.o ledNode.o playGround.o
	$(CXX) $(CXXFLAGS) -o test arrayTools.o ledNode.o playGround.o
	
#components
arrayTools.o: arrayTools.cc arrayTools.h
	$(CXX) $(CXXFLAGS) -c arrayTools.cc #May need that .h here... not sure.
	
ledNode.o: ledNode.cc ledNode.h arrayTools.h
	$(CXX) $(CXXFLAGS) -c ledNode.cc #Again, those .h may need to be compiled.
	
#If Playground is what we are running the main of, do we need a .o for it?
playGround.o: playGround.cc ledNode.h arrayTools.h 
	$(CXX) $(CXXFLAGS) -c playGround.cc #You know the deal.
	
clean:
	rm *.o
	
	
# TEST_OBJ = arrayTools.o ledNode.o playGround.o
# 
# #Should be the last thing we need to do or close. must make the .o targets first!
# testArduWatch = $(TEST_OBJ)
# 	g++ $(TEST_OBJ)


