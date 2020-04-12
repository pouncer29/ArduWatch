#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include<ADWatch.h>

/* LED code outpus */
#define PZero 12
#define POne 11
#define PTwo 10
#define PThree 9
/* End LED Code outputs */

/* Ring Nonsense */
  #define PIN 6
  #define NUM_LEDS 12
  #define BRIGHTNESS 10
  Adafruit_NeoPixel* ring = new Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

  uint32_t testColour;
 /* End Ring Nonsense*/

 /* Watch Nonsense*/
 ADWatch* watch = new ADWatch(ring);
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
  testColour = ring->Color(255,255,0,50);
  ring->begin();
  ring->clear();
  ring->setBrightness(BRIGHTNESS);

  /*Watch Setup*/
  setTime(12,59,15,12,04,2020);
}

void loop()                   
{
  time_t curTime = now();
  printTime(curTime);
	debugOut(hour(curTime));
  watch->showTime(curTime);
 delay(2000);
}

/* printTime*/
void printTime(time_t tm){
  Serial.print("Time: ");Serial.print(hour(tm));Serial.print(":");Serial.print(minute(tm));Serial.print(":");Serial.println(second(tm));
}

/* Writes testColor to the specified index on the ring*/
void writeToRing(int stopIdx){
  ring->clear();
  ring->show();
  if(stopIdx < 13){
    for(int i = 0; i<stopIdx; i++){
      ring->setPixelColor(i,testColour);
      ring->show();
    }
  }
}

/* writes a code to the LEDs*/
void debugOut(int code){
  byte v0 = 0;
  byte v1 = 0;
  byte v2 = 0;
  byte v3 = 0;
  if(code < 16){
    /* Read fields*/
    v0 = bitRead(code,0);
    v1 = bitRead(code,1);
    v2 = bitRead(code,2);
    v3 = bitRead(code,3);
    Serial.print("Code: "); Serial.print(v3); Serial.print(v2); Serial.print(v1); Serial.println(v0);
  }

  /* Write Values*/
  digitalWrite(PZero,v0);
  digitalWrite(POne,v1);
  digitalWrite(PTwo,v2);
  digitalWrite(PThree,v3);
  
  
}

/** Returns an int value from the float
 *  reading given by the dial
 */
int dialSelect(){
  float reading = analogRead(A0);
  Serial.print("Reading: "); Serial.println(reading);
  return reading / 10;
}
