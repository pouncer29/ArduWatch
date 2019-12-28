#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <ADWatch.h>
#include <TimeLib.h>
#include <GPSTools.h>
#include <ADbug.h>

/**
 *  WATCH SETUP BEGIN
 */

#define PIN 6
#define NUM_LEDS 12
#define BRIGHTNESS 10

enum Feats {Clock=1,Compass,Speedometer,Flashlight,Strobe,Refresh,Blank,FeatCount = 6}; // Remember to update count if features are added

//For Ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel* ring = &strip;
ADBug debugger = ADBug(ring);



//Using a master watch Class
ADWatch watch = ADWatch(ring);

//For Flow
//ShowTimeButton
const uint8_t startWatchPin = 8;// the number of the pushbutton pin INPUT
boolean on = false;         //current output state
int buttonState = 0;       //the current flow through the button.
bool isRunning = false;     //whether or not to do the light show on button press
bool initialRun = true;

//Flourish Colours
uint32_t compassColour;
uint32_t speedoColour;
uint32_t clockColour;
uint32_t flashColour;
uint32_t partyColour;
uint32_t errorColour;
uint32_t blank;
uint32_t  err = ring->Color(255,0,0,0);

uint32_t Colours[FeatCount +1];
int curFeat;

/** END WATCH SETUP */


// If you're using a GPS module:
// Connect the GPS Power pin to 5V
// Connect the GPS Ground pin to ground
// If using software serial (sketch example default):
//   Connect the GPS TX (transmit) pin to Digital 3
//   Connect the GPS RX (receive) pin to Digital 2
// If using hardware serial (e.g. Arduino Mega):
//   Connect the GPS TX (transmit) pin to Arduino RX1, RX2 or RX3
//   Connect the GPS RX (receive) pin to matching TX1, TX2 or TX3

// If you're using the Adafruit GPS shield, change
// SoftwareSerial mySerial(3, 2); -> SoftwareSerial mySerial(8, 7);
// and make sure the switch is set to SoftSerial

// If using software serial, keep this line enabled
// (you can change the pin numbers to match your wiring):
SoftwareSerial mySerial(3, 2);

Adafruit_GPS GPS(&mySerial);
GPSTools gTools(&GPS,7);
#define GPSECHO  false

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

void setup()
{
  // flow setup
  initialRun = true;
    /** GPS SETUP*/
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
    useInterrupt(true);
    gTools.gps->begin(9600);
    Serial.begin(115200);

  //INIT RING
    ring->setBrightness(BRIGHTNESS);
    ring->begin();
    ring->clear();
    ring->show(); //Supposedly initilizes all to off
    


    
    //For Buttons
    pinMode(startWatchPin,INPUT);
    //Init Flourish Colours & Cycler
    clockColour = watch.clock_colour;
    compassColour = watch.compass_colour;
    speedoColour = watch.speedo_colour;
    flashColour = watch.light_colour;
    partyColour = watch.party_colour;
    errorColour = watch.error_colour;
    blank = watch.blank;

    Colours[Clock] =clockColour;
    Colours[Compass] = compassColour;
    Colours[Speedometer] = speedoColour;
    Colours[Flashlight] = flashColour;
    Colours[Strobe] = partyColour;
    Colours[Refresh] = errorColour;
    Colours[Blank] = blank;
    curFeat = getFeat();
    /**END WATCH SETUP*/
}

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
        char c = GPS.read();
        // if you want to debug, this is a good time to do it!
#ifdef UDR0
if (GPSECHO)
    if (c) UDR0 = c;
    // writing direct to UDR0 is much much faster than Serial.print
    // but only one character can be written at a time.
#endif
}

void useInterrupt(boolean v) {
    if (v) {
        // Timer0 is already used for millis() - we'll just interrupt somewhere
        // in the middle and call the "Compare A" function above
        OCR0A = 0xAF;
        TIMSK0 |= _BV(OCIE0A);
        usingInterrupt = true;
    } else {
        // do not call the interrupt function COMPA anymore
        TIMSK0 &= ~_BV(OCIE0A);
        usingInterrupt = false;
    }
}

void loop()                   
{  
  /* ADAFRUIT GPS STUFF*/
//    if (! usingInterrupt) {
//        char c = GPS.read();
//        if (GPSECHO)
//            if (c) Serial.print(c);
//    }
//    if (GPS.newNMEAreceived()) {
//        if (!GPS.parse(GPS.lastNMEA()))
//            return;
//    }
    /***********************/
  curFeat = getFeat();
    /** WATCH LOOP*/
     Serial.print("GPS has fix: "); Serial.println(GPS.fix == true);
     Serial.print("Reading is: "); Serial.print(analogRead(A0)); Serial.print(" Feat is: "); Serial.println(curFeat);
     on = curFeat >0;

    //Start watch button code.
    if(on == true){
      
      if(initialRun == true){
        setTime(gTools.grabTime());
        initialRun = false;
      }
        if(isRunning == false){
            watch.flourish(Colours[curFeat],100);
            delay(800);
            isRunning = true;          //5. remember not to florish every time we show the time
        }
        delay(200);
        watch.setPixels(blank);
        ring->show();
        Serial.print("CurFeat: ");
        Serial.println(curFeat);

        //Clock
        while(curFeat == Clock){
          watch.showTime(now());
          Serial.println("gTools");
          Serial.print(GPS.hour, DEC); Serial.print(':');
          Serial.print(GPS.minute, DEC); Serial.print(':');
          Serial.print(GPS.seconds, DEC); Serial.println('.');
          time_t test = now();
          Serial.println(test,DEC);
          Serial.println(GPS.longitude, 4);
          Serial.print(GPS.longitudeDegrees, 4);Serial.println(GPS.lon);
          curFeat = getFeat();
        }

        //Compass
        while(curFeat == Compass){
          Serial.print("Has Fix: "); Serial.println(GPS.fix);
          if(gTools.hasFix())
              watch.showHeading(gTools.grabHeading());
          else{
              GPSRead();
              watch.refresh(!GPS.fix);
          }
              
          curFeat = getFeat();
        }

        //Speed
        while(curFeat == Speedometer){
          if(gTools.hasFix())
              watch.showSpeed(gTools.grabSpeed());
          else
              watch.refresh(!gTools.hasFix());
          
          curFeat = getFeat();
        }

        //Flash
        while(curFeat == Flashlight){
          watch.showLight();
          curFeat = getFeat();
        }

        //Party
        while(curFeat == Strobe){
          watch.showStrobe(startWatchPin);
          curFeat = getFeat();
        }

        //Refresh
        while(curFeat == Refresh){
          watch.refresh(!gTools.hasFix());
          curFeat = getFeat();
        }

        ring->show();
        /**********************************/
        delay(500);

    }
    else{
        ring->clear();             //1. Button must be off, clear the strip
        ring->show();
        isRunning = false;                //3. remember to flourish when we turn it back on.
    }


    delay(200);                     //Apparently good for 'debounce' whatever that is
    /*END WATCH LOOP*/
}

/** Gets the Current Feat based on dial position*/
Feats getFeat(){
  int reading = analogRead(A0);
  int featId = watch.getWatchFunction(reading);
  Serial.print("FeatId: ");Serial.println(featId);
  Feats feat = (Feats) featId;
  Serial.print("Feat is: "); Serial.println(feat);
  return feat;
}


void GPSRead(){
      if (! usingInterrupt) {
        char c = GPS.read();
        if (GPSECHO)
            if (c) Serial.print(c);
    }
    if (GPS.newNMEAreceived()) {
        if (!GPS.parse(GPS.lastNMEA()))
            return;
    }
}
