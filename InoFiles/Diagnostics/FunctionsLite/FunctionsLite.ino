#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include <ADWatch.h>

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
 /* End Watch Nonsense*/
 
 void setup()
{
  Serial.begin(115200);

  /*Ring Setup*/
  errorColour = ring->Color(255,0,0,0);
  ring->begin();
  ring->clear();
  ring->setBrightness(BRIGHTNESS);

  /*Watch Setup*/
  randomSeed(analogRead(0));
  setTime(12,59,15,12,04,2020);
  prevFn = 0;
}

void loop()                   
{
  int choice = dialSelect();
  Serial.print("Choice is: ");Serial.println(choice);
  time_t curTime = now();
    ring->clear();
    ring->show();
  /*Clear ring if different from last fn*/
  if(prevFn != choice){
    Serial.print("Choice Switched From ");Serial.print(prevFn);Serial.print(" to "); Serial.println(choice);
    watch->flourish((FnColour) choice, 60);
  }


  /*If is greater than switch*/
  if(choice == BLANK_CLR){
      ring->clear();
      ring->show();
  } else if(choice == CLOCK_CLR){
      watch->showTime(curTime);
  } else if(choice == COMPASS_CLR){
      float heading = 85.0;
      watch->showHeading(heading);
  } else if(choice == SPEED_CLR){
      float testSpeed = 29.9;
      watch->showSpeed(testSpeed);
  } else if(choice == LIGHT_CLR){
	watch->showLight();
  } else if (choice == PARTY_CLR){
      while(choice == PARTY_CLR){
	        watch->showStrobe(choice);
          choice = dialSelect();  
        }
  } else {
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
