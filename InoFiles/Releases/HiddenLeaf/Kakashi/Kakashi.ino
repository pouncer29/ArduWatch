#include <Adafruit_GPS.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <GPSTools.h>
#include <Adafruit_GPS.h>
#include <TimeLib.h>
#include <ADWatch.h>
#include <ADbug.h>

/* LED code outpus */
#define PZero 9
#define POne 10
#define PTwo 11
#define PThree 12
/* End LED Code outputs */

/* GPS Nonsense */
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
GPSTools gTools = GPSTools(-6);
#define GPSECHO  true
/* End GPS Nonsense*/

/* Ring Nonsense */
  #define PIN 6
  #define NUM_LEDS 12
  #define BRIGHTNESS 10
  Adafruit_NeoPixel* ring = new Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

  uint32_t errorColour;
 /* End Ring Nonsense*/

 /* Watch Nonsense*/
 ADWatch* watch = new ADWatch(ring);
 uint8_t prevFn;
 enum Feats {Off = 0,Clock,Compass,Speedometer,Flashlight,Strobe,Refresh,FeatCount = 7}; // Remember to update count if features are added
 uint32_t Colours[FeatCount];
 /* End Watch Nonsense*/
 
 void setup()
{
  /* Code out Setup */
  pinMode(PThree,OUTPUT);
  pinMode(PTwo,OUTPUT);
  pinMode(POne,OUTPUT);
  pinMode(PZero,OUTPUT);
  Serial.begin(115200);

  /*Ring Setup*/
  errorColour = ring->Color(255,0,0,0);
  ring->begin();
  ring->clear();
  ring->setBrightness(BRIGHTNESS);

  /*Watch Setup*/
  randomSeed(analogRead(0));
  setTime(12,59,15,12,04,2020);
  Colours[Off] = watch->blank;
  Colours[Clock] = watch->clock_colour;
  Colours[Compass] = watch->compass_colour;
  Colours[Speedometer] = watch->speedo_colour;
  Colours[Flashlight] = watch->light_colour;
  Colours[Strobe] = watch->party_colour;
  Colours[Refresh] = watch->error_colour;

  
  prevFn = 0;

  /*Debug Setup*/
  setDebugColour(errorColour);
  setVerbose(true);
}

void loop()                   
{
  int choice = dialSelect();
  Serial.print("Choice is: ");Serial.println(choice);
  debugOut(choice);
  time_t curTime = now();
    ring->clear();
    ring->show();
  /*Clear ring if different from last fn*/
  if(prevFn != choice){
    ring->clear();
    watch->flourish(Colours[choice],100);
    Serial.print("Choice Switched From ");Serial.print(prevFn);Serial.print(" to "); Serial.println(choice);
  }

  /*If is greater than switch*/
  if(choice == Off){
      ring->clear();
      ring->show();
  } else if(choice == Clock){
      printTime(curTime);
      watch->showTime(curTime);
  } else if(choice == Compass){
      float heading = randFloat(0,360);
      printFloat("heading",heading);
      watch->showHeading(heading);
  } else if(choice == Speedometer){
      float testSpeed = randFloat(0,200);
      printFloat("Speed",testSpeed);
      watch->showSpeed(testSpeed);
  } else if(choice == Flashlight){
	watch->showLight();
  } else if (choice == Strobe){
      while(choice == 5){
	        watch->showStrobe(choice);
          choice = dialSelect();  
        }
  } else {
    writeToRing(ring,8);
    setFlag(ring,2);
	Serial.print("Choice: ");Serial.print(choice);Serial.println(" Not recognized");
  }
  prevFn = choice;
  delay(2000);
      
  }

/** Returns an int value from the float
 *  reading given by the dial
 */
int dialSelect(){
  float reading = analogRead(A0);
  Serial.print("Reading: "); Serial.println(reading);
  return (int) ((int) reading / 100);
}
