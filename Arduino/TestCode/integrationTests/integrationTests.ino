#include <Adafruit_NeoPixel.h>
#include <ADWatch.h>
#include <TimeLib.h>

/*From the RGBW TESTS (not everything)*/
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 5
#define NUM_LEDS 12
#define BRIGHTNESS 30

//For Time
#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message
time_t t;

//For Ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel* ring = &strip;



//Using a master watch Class
ADWatch watch = ADWatch(ring);


//For Flow

//ShowTimeButton
const uint8_t startWatchPin = 8;// the number of the pushbutton pin INPUT
boolean on = false;         //current output state
int buttonState = 0;       //the current flow through the button.
bool flourish = true;     //whether or not to do the light show on button press


//Flourish Colours
uint32_t compassColour;
uint32_t speedoColour;
uint32_t clockColour;
uint32_t flashColour;
uint32_t blank;

//test values
 float testSpeed = 45.5;
 float testHeading = 30.0;
 
 uint32_t  err = ring->Color(255,0,0,0);

void setup() {

    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  
  //INIT RING
  ring->setBrightness(BRIGHTNESS);
  ring->begin();    
  ring->clear();
  ring->show(); //Supposedly initilizes all to off  


  
  //For Buttons
  pinMode(startWatchPin,INPUT);
  
  //Test values
  setTime(1,24,30,12,28,2017);

  

  //Init Flourish Colours
    compassColour = watch.compass_colour;
    speedoColour = watch.speedo_colour;
    clockColour = watch.clock_colour;
    flashColour = watch.light_colour;
    blank = watch.blank;

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
         watch.flourish(speedoColour,100,ring);
         delay(800);                
         flourish = false;          //5. remember not to florish every time we show the time
        }
      delay(200);
      watch.setPixels(blank,ring);
      ring->show();
     

      /*************************
      PUT WATCH CODE HERE 
      **************************/
      //setFlag(5);
      watch.showSpeed(180,ring);
      delay(3000);
      watch.showTime(t,ring);
      delay(3000);
      watch.showHeading(60.0);
      delay(3000);
      ring->setBrightness(10);
      //watch.showLight();
      //delay(3000);
      watch.showStrobe(startWatchPin,ring);
      //delay(3000);


     // setFlag(3);
      ring->show();
      //cleanup();
      /**********************************/
      delay(500);
      
    }
   else{
    ring->clear();             //1. Button must be off, clear the strip
    ring->show();
    flourish = true;                //3. remember to flourish when we turn it back on.
   }

   //setFlag(9);

    delay(200);                     //Apparently good for 'debounce' whatever that is

}


void setFlag(int n){
  ring->setPixelColor(n,err);
  ring->show();
}
void removeFlag(int n){
  uint32_t blank = strip.Color(0,0,0,0);
  ring->setPixelColor(n,blank);
  ring->show();
}

float randFloat(){
  float num = random(0,98);
  return num;
}
