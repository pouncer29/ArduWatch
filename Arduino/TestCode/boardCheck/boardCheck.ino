#define PIN 6



//For Flow

//ShowTimeButton
const uint8_t startWatchPin = 8;// the number of the pushbutton pin INPUT
boolean on = false;         //current output state
int buttonState = 0;       //the current flow through the button.

//SetTimeButton
const uint8_t setTimePin = 4;
int setTimeButtonState = 0;


void setup() {
  
  //For Buttons
  pinMode(startWatchPin,INPUT);
  pinMode(setTimePin,INPUT);
  analogWrite(6,150);
 

}

void loop() {
  
 //Start Watch Button checker 
  buttonState=digitalRead(startWatchPin);
  if(buttonState == HIGH){
     if(on == true)
       on = false;
     else
       on = true;
  }

  //Start watch button code.
  if(on == true){
      digitalWrite(8,HIGH);
    }

    delay(200);                     //Apparently good for 'debounce' whatever that is.


  //Set Time Code
  setTimeButtonState = digitalRead(setTimePin);
    if((setTimeButtonState == HIGH) && (!on)){
      digitalWrite(4,HIGH);   
  }
}
 


