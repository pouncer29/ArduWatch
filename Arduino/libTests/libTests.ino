#include <Adafruit_NeoPixel.h>
#include <faceTrackTime.h>
#include <TimeLib.h>

/*From the RGBW TESTS (not everything)*/
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 12
#define BRIGHTNESS 20

//For Time
#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

//For Ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
Face_Show_Time face = Face_Show_Time(strip);


//For Flow
//ShowTimeButton
const uint8_t startWatchPin = 8;// the number of the pushbutton pin INPUT
boolean on = false;         //current output state
int buttonState = 0;       //the current flow through the button.

bool flourish = true;     //whether or not to do the light show on button press

void setup() {

    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  face.ring.setBrightness(BRIGHTNESS);
  face.ring.begin();
  face.ring.show(); // Initialize all pixels to 'off'
  
  //For Buttons
  pinMode(startWatchPin,INPUT);
  
  //Test Time for testing.
  setTime(1,24,30,12,28,2017);

  


  

  //Testing our Tracker Library Function
 


}

void loop() {

  time_t t =now();
  
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
      t=now();
      if(flourish){
         face.modMinColour(t);           //1. get the flourish colour
         face.colorWipe(face.minColour,100);  //2. do the colour wipe
         face.clearStrip();              //3. reset ring to blank
         face.ring.show();              //4. push the blank ring
         delay(700);                
         flourish = false;          //5. remember not to florish every time we show the time.
      }
      
      face.trackTime(t);
      //face.strip.show();
      //face.clearStrip();   
    }
   else{
    face.clearStrip();               //1. Button must be off, clear the strip
    face.ring.show();                   //2. push the clear
    flourish = true;                //3. remember to flourish when we turn it back on.
   }

    delay(200);                     //Apparently good for 'debounce' whatever that is.
  
}
  



time_t requestSync(){
   Serial.write(TIME_REQUEST);
   return 0;
}



