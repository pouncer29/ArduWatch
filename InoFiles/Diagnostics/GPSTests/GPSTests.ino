// Test code for Adafruit GPS modules using MTK3329/MTK3339 driver
//
// This code shows how to listen to the GPS module in an interrupt
// which allows the program to have more 'freedom' - just parse
// when a new NMEA sentence is available! Then access data when
// desired.
//
// Tested and works great with the Adafruit Ultimate GPS module
// using MTK33x9 chipset
//    ------> http://www.adafruit.com/products/746
// Pick one up today at the Adafruit electronics shop
// and help support open source hardware & software! -ada

#include <Adafruit_GPS.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <GPSTools.h>
#include <Adafruit_GPS.h>
#include <TimeLib.h>
#include <ADWatch.h>

/* GPS Nonsense */
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
GPSTools gTools = GPSTools(-6);
#define GPSECHO  true
/* End GPS Nonsense*/

/* LED OUTPUT CODES */
#define PZero 9
#define POne 10
#define PTwo 11
#define PThree 12
/* END LED OUTPUT CODES*/

/* Ring Nonsense */
  #define PIN 6
  #define NUM_LEDS 12
  #define BRIGHTNESS 10
  Adafruit_NeoPixel* ring = new Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
  uint32_t testColour;
  /* End Ring Nonsense*/

  /* Watch Nonsense*/
 ADWatch* watch = new ADWatch(ring);
 uint16_t prevFn;
 /* End Watch Nonsense*/

void setup()
{
  /* GPS Setup*/
  Serial.begin(115200);
  delay(5000);
  Serial.println("Adafruit GPS library basic test!");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);

  /* Code out Setup */
  pinMode(PThree,OUTPUT);
  pinMode(PTwo,OUTPUT);
  pinMode(POne,OUTPUT);
  pinMode(PZero,OUTPUT);  
  Serial.println("TESTING SETUP -- Complete");

  /*Ring Setup*/
  ring->begin();
  ring->clear();
  ring->show();
  ring->setBrightness(20);
  Serial.println("RING SETUP -- Complete");

   /*Watch Setup*/
  randomSeed(analogRead(0));
  //setTime(12,59,15,12,04,2020);
  prevFn = 0;
  Serial.println("FLOW SETUP -- Complete");
  
}

uint32_t timer = millis();
void loop()                     // run over and over again
{
  char c = GPS.read();
  //if ((c) && (GPSECHO))
    //Serial.write(c);
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return; 
  }
/* GPS Poll */
  if (timer > millis())  timer = millis();
  if (millis() - timer > 2000) {
    timer = millis();
    //printGPS(GPS);
    if(GPS.fix == true){
      setTime(GPS.hour,GPS.minute,GPS.seconds,GPS.day,GPS.month,GPS.year);
      //setTime(12,15,30,18,04,2020);
      //printTime(now());
      int success = gTools.grabTime(now(),GPS.longitudeDegrees);
      //debugOut(success);
      
  /* End GPS Poll */
      /*Selector */
  int choice = dialSelect();
  //Serial.print("Choice is: ");Serial.println(choice);
  debugOut(choice);
  /* End Selector*/
    /* Flow Setup */
  /*Clear ring if different from last fn*/
  if(prevFn != choice){
      ring->clear();
        //ring->show();
    //Serial.print("Choice Switched From ");Serial.print(prevFn);Serial.print(" to "); Serial.println(choice);
   }
    /* fn Choice*/
  if(choice == 0){
      ring->clear();
      ring->show();
  } else if (choice == 1){
     //ring->clear();
     time_t curTime = now();
     printTime(curTime);
     watch->showTime(curTime);
     //ring->show();
  } else if(choice == 2){
      //ring->clear();
      //float heading = randFloat(0,360);
      float heading = gTools.grabHeading(GPS.angle);
      //float heading = GPS.angle;
      //float heading = 15.0;
      printFloat("GPS_Heading",heading);
      watch->showHeading(heading);
      //ring->show();
  } else if(choice == 3){
      //ring->clear();
      //float speed = randFloat(0,200);
       float speed = gTools.grabSpeed(GPS.speed);
       //float speed = GPS.speed * 1.825;
       printFloat("GPS_Speed", speed);
       watch->showSpeed(speed);
      //ring->show();
  }
  else{
    writeToRing(8);
  }

  prevFn = choice;
  }
  /* End Flow Setup */
  }
  }


/*************** SUPPLEMENTAL FUNCTIONS *************************/
/*Random Float*/
float randFloat(int lower, int upper){
  float randFloat = random(lower,upper);
  return randFloat;
}

/*print gps stats*/
void printGPS(Adafruit_GPS g){
  if(g.fix == true){
   // debugOut(15);
    Serial.print("Quality: ");Serial.println(g.fixquality);
    Serial.print("Time: ");
    Serial.print(g.hour, DEC); Serial.print(':');Serial.print(g.minute, DEC); Serial.print(':');Serial.print(g.seconds, DEC); Serial.println('.');
    Serial.print("Longitude: ");Serial.println(g.longitude, 4);
    Serial.print("Longitude Degrees: ");Serial.print(g.longitudeDegrees, 4);Serial.println(g.lon);
    Serial.print("Angle: ");Serial.println(g.angle);
    Serial.print("Speed (kn): "); Serial.println(g.speed);
    Serial.print("Speed (kmph): "); Serial.println(g.speed * 1.852);
    Serial.print("Satellites: "); Serial.println((int) g.satellites);
    //setTime(gTools.grabTime(&g));
  } else {
    Serial.println("GPS: NO SIGNAL");
  }
}

/* printTime*/
void printTime(time_t tm){
  Serial.print("Time is: ");Serial.print(hour(tm));Serial.print(":");Serial.print(minute(tm));Serial.print(":");Serial.println(second(tm));
}

void printFloat(char lable[], float value){
  Serial.print(lable);Serial.print(" is: ");Serial.println(value);
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
    //Serial.print("Code: "); Serial.print(v3); Serial.print(v2); Serial.print(v1); Serial.println(v0);
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
 // Serial.print("Reading: "); Serial.println(reading);
  return (int) ((int) reading / 100);
}
