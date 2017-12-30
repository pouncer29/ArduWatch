#include <Adafruit_NeoPixel.h>
#include <trackTime.h>
//#include <TimeLib.h>

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

void setup() {

    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  
  //Test Time for testing.
  setTime(3,14,45,12,28,2017);

  

  //Testing our Tracker Library Function
 


}

void loop() {
  time_t testTime = now();
  Time_Tracker face = Time_Tracker(strip);
  // put your main code here, to run repeatedly:
  //Flourish
  //learnOffsets(200);

  //TrackTime
  while(true){
    //time_t t = now();
    face.trackTime(testTime);
  }
  
  
}


time_t requestSync(){
   Serial.write(TIME_REQUEST);
   return 0;
}



