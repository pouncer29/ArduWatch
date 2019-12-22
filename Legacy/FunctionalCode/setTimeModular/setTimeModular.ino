#include <Adafruit_NeoPixel.h>
#include <ADWatch.h>
#include <TimeLib.h>


// Adafruit prerequisites from Circit Playground
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6
#define NUM_LEDS 12
#define BRIGHTNESS 20


//For Time (Possibly for RTC...)
#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message

//Construct watch
time_t t; // Time to track
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800); //Face
ADWatch watch = ADWatch(t,strip);


/***** BUTTONS For Flow *****/

//ShowTimeButton
const uint8_t buttonPinA = 8;// the number of the pushbutton pin INPUT
boolean on = false;         //current output state
byte buttonAState = 0;       //the current flow through the button.
bool flourish = true;     //whether or not to do the light show on button press

//SetTimeButton
const uint8_t buttonPinB = 4;
byte buttonBState = 0;


void setup() {

  //Trinket Special code
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif 
  // End of trinket special code

  //Configure ring
  watch.face->ring.setBrightness(BRIGHTNESS);
  watch.face->ring.begin();
  //watch.face->clearStrip(); Quite possibly redundant.
  watch.face->ring.show(); // Initialize all pixels to 'off'
  
  //Configure buttons
  pinMode(buttonPinA,INPUT);
  pinMode(buttonPinB,INPUT);
  
  //Test Time for testing.
  setTime(1,24,30,12,28,2017);

}

// Run Forest!
void loop() {	
  t =now();
  
 //Start Watch Button checker 
  buttonAState=digitalRead(buttonPinA);
  if(buttonAState == HIGH){
     if(on == true)
       on = false;
     else
       on = true;
  }

  //Start watch button code.
  if(on == true){
      if(flourish){
         watch.face->modMinColour(t);           //1. get the flourish colour
         watch.face->colorWipe(watch.face->minColour,100);  //2. do the colour wipe
         watch.face->clearStrip();              //3. reset ring to blank
         watch.face->ring.show();              //4. push the blank ring
         delay(700);                
         flourish = false;          //5. remember not to florish every time we show the time.
      }

      //Where the magic happens.
     /*******************/
      watch.trackTime(t);
     /*******************/
    }
   else{
    watch.face->clearStrip();               //1. Button must be off, clear the strip
    watch.face->ring.show();                   //2. push the clear
    flourish = true;                //3. remember to flourish when we turn it back on.
   }

    delay(200);                     //Apparently good for 'debounce' whatever that is.

  //Set Time Code
  buttonBState = digitalRead(buttonPinB);
    if((buttonBState == HIGH) && (!on)){
      manualSetTime();
    }
}
  

  //**If you need to send updated info to an RTC this is the place to do it.

 
void manualSetTime(){
  //Show that we have entered the time reset mode
  watch.face->colorWipe(watch.face->rstTimeColour,100);
      
  //values to set
  uint8_t hr = 0;
  uint8_t Min = 0;

  //Loop Controllers & Counters
  uint8_t pressedCount = 0;
  byte pushButtonState = 0;
  byte prevButtonState = 0;

      //Press Once to set Hr, Twice to setMinute)
  while(pressedCount < 2){        
    pushButtonState = digitalRead(buttonPinA);

    //Completley reset time to track change.
    setTime(0,0,0,30,1,1997);
    t = now();
    uint8_t startSet = second(t);  //Keeps the reset Time
    uint8_t endSet = second(t);    //Is Updaed when hands are not moved.

    //Very similar to the above loop to display time.
    if(pushButtonState != prevButtonState){
      if(pushButtonState == HIGH){

        //First Press sets hour.
        if(pressedCount == 0){
          hr = 0;
          byte moveHrButtonState = 0;
          byte prevMoveButtonState = 0;

          //Set Hour Loop
          while(endSet < 5){

            //Cursor not advanced, update time.
            t = now();
            endSet = second(t);
            
            //See if we want to move
            moveHrButtonState = digitalRead(buttonPinA);
            if(moveHrButtonState != prevMoveButtonState){

              //And we've pressed the move button
              if(moveHrButtonState == HIGH){
                //Update hour
                hr++;
                watch.setWatchTime(hr,Min,t); 
                
                //reset Timer
                endSet = startSet;
              }
            }
              
            //remember that we did move.
            prevMoveButtonState = moveHrButtonState;
          }

            //If time is up, Show that hour was set with a wipe
            watch.face->colorWipe(watch.face->hrColour,100);
        }

        //Second Press sets minutes.
        else if (pressedCount == 1){
          Min = 0;
          byte moveMinButtonState = 0;
          byte prevMoveButtonState = 0;
      
          //Set Minute Loop
          while(endSet < 5){

            //Minute hand not changed, update the timer.
            t = now();
            endSet = second(t);

            //See if we want to move
            moveMinButtonState = digitalRead(buttonPinA);

            //if we haven't yet tried to move
            if(moveMinButtonState != prevMoveButtonState){

              //And we've pressed the move button
              if(moveMinButtonState == HIGH){

                //update Minute (but keep that hour we changed)
                Min++;
                watch.setWatchTime(hr,Min,t);

                //reset Timer
                endSet = startSet;
              }
            }  
            //and remember that we did move.
            prevMoveButtonState = moveMinButtonState;
          }

          //Show that minute was successfully updated with a minColour wipe!
          watch.face->colorWipe(watch.face->minColour,100);
        }

  
        //Update our press count.
        pressedCount++;
        delay(50);
      }
    }

    //Remember what our last state was.
    prevButtonState = pushButtonState;
  }
 }



