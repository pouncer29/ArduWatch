//   Name: Ben Lewis
//   Date: Nov 3rd, 2017
//   Synopsis: Arduino watch playground. for real this time tho.

#include <iostream>
//#include <ctime> //For testing purposes
//#include "./Tools/ArrayTools/arrayTools.h"
//#include "./Tools/LedNode/ledNode.h"

using namespace std ; 

//////////////My_Stuff/////////
//Inputs
const int SHOW_TIME_PIN = 4;
const int PULL_TIME_PIN = 6;

//Outputs
const int SHOW_PIN_OUT = 11;
const int PULL_PIN_OUT = 10; 

//States
int showTimeState = 0;
int pullTimeState = 0;
/////////////////////////////////


/////COPY OF THE ARDUINO LAB//

  //Initial Variables
  const int buttonPin = 8; // The pin we are sending stuff too.
  const int lightOut = 11; // The light on our board.
  int toggleState = 0;     // state of the light.


//Running Preconditions
void setup() {
  //Pin Mode is our best friend.
  pinMode(buttonPin,INPUT);
  pinMode(lightOut, OUTPUT);
  
}

//Infinite loop to run our machine forever
void loop() {

  toggleState = digitalRead(buttonPin); //Set state to whichever we are in rn

  //when we press the button, do something.
  if(toggleState == HIGH){          //HIGH is recieving inpt
      digitalWrite(lightOut, HIGH);
  }
  else{
      digitalWrite(lightOut, LOW); //Low must be not receiving input?
  }

}
//////////////////////////////////////////////////////////////////

//What do we want to test for the first round?
/*
	- I guess pressing the button and lighting a light should be the priority rn
		so the code we have above should be made into a circuit again.
		
	- Because we aren't using a pin for each thing anymore, we cant test that. We can
		however test that we can activate a pin based on an array index. How?
			* Create an array of Anything
			* When x minutes or seconds pass, light the light.
			
			What Will we need?
			-------------------
			* A Circuit to test with.
			* A few new button pins? 
*/

void setup(){
	
	//Assign Inputs
	pinMode(SHOW_TIME_PIN,INPUT);
	pinMode(PULL_TIME_PIN,INPUT);
	
	//Assign outputs
	pinMode(SHOW_PIN_OUT, OUTPUT);
	pinMode(PULL_PIN_OUT, OUTPUT);
	}
	

/*
	My Modified Loop
	-----------------
*/
void loop() {

	//Code from testNodes.cc
// 	time_t now = time(0);
// 	tm* timeII = localtime(&now);
// 	char* strTime = ctime(&now);

	//Show Time Button
	showTimeState = digitalRead(SHOW_TIME_PIN);
	if(showTimeState == HIGH)
		digitalWrtie(SHOW_PIN_OUT,HIGH);
	else
		digitalWrtie(SHOW_PIN_OUT,LOW);
		
		
	//Pull time button
	pullTimeState = digitalRead(PULL_TIME_PIN);
	if(pullTimeState == HIGH)
		digitalWrite(PULL_PIN_OUT, HIGH);
	else
		digitalWrite(PULL_PIN_OUT, LOW);
		

/****NOTES*****
	* may need to add brackets because this is only a bit like c++.
	* can we use just one state Variable and re-assign it to other inputPins?
	
*/

}











