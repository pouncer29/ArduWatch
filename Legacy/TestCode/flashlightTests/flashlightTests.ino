#include <Adafruit_NeoPixel.h>
#include <ADWatch.h>
#include <Adafruit_GPS.h>
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
time_t t;

//For Ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);



//Using a master watch Class
ADWatch watch = ADWatch(t,strip);




//For Flow

//ShowTimeButton
const uint8_t startWatchPin = 8;// the number of the pushbutton pin INPUT
boolean on = false;         //current output state
int buttonState = 0;       //the current flow through the button.
bool flourish = true;     //whether or not to do the light show on button press

//SetTimeButton
const uint8_t setTimePin = 4;
int setTimeButtonState = 0;

//Flourish Colours
uint32_t compassColour;
uint32_t speedoColour;
uint32_t flashColour;


void setup() {

    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
//  #if defined (__AVR_ATtiny85__)
//    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
//  #endif
  // End of trinket special code
  
  //INIT RING
  strip.begin();    
  strip.clear();
  strip.show(); //Supposedly initilizes all to off  


  
  //For Buttons
  pinMode(startWatchPin,INPUT);
  pinMode(setTimePin,INPUT);
  
  //Test Time for testing.
  setTime(1,24,30,12,28,2017);
  

  //Init Flourish Colours
  //compassColour = watch.compass->needle->needleColour;
//  speedoColour = watch.speedo->dial->regionAColour;
//    flashColour = watch.ring.Color(0,0,0,255);


}

void loop() {
  //setFlag(0);
  t =now();
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
      if(flourish){
         //setFlag(1);
         watch.flourish(strip.Color(25,10,150,0),100);
         delay(500);                
         flourish = false;          //5. remember not to florish every time we show the time
        }
      delay(200);
      /*************************
      PUT WATCH CODE HERE falsl:e
      **************************/
       watch.showTime(t);
      //watch.showSpeed(randFloat());
      //watch.ring.setPixelColor(watch.light->lightColour,0);
      //setFlag(0);
      watch.ring.show(); 
     
      /**********************************/
      delay(700);
      
    }
   else{
    strip.clear();             //1. Button must be off, clear the strip
    strip.show();
    flourish = true;                //3. remember to flourish when we turn it back on.
   }

    delay(200);                     //Apparently good for 'debounce' whatever that is

}
 


void setFlag(int n){
  uint32_t  err = strip.Color(255,0,0,0);
  strip.setPixelColor(n,err);
  strip.show();
}
void removeFlag(int n){
  uint32_t blank = strip.Color(0,0,0,0);
  strip.setPixelColor(n,blank);
  strip.show();
}

float randFloat(){
  float num = random(0,98);
  Serial.print(num);
  return num;
}





