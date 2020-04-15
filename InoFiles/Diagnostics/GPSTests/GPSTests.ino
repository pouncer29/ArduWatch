#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <GPSTools.h>
#include <Adafruit_GPS.h>
#include <TimeLib.h>
#include <ADWatch.h>

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
 uint8_t prevFn;
 /* End Watch Nonsense*/

/*GPSNonsense */
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
GPSTools gTools = GPSTools(&GPS,7);
/* End GPS Nonsense*/


#define GPSECHO  true

void setup()
{

 /* Code out Setup */
  pinMode(PThree,OUTPUT);
  pinMode(PTwo,OUTPUT);
  pinMode(POne,OUTPUT);
  pinMode(PZero,OUTPUT);  
  Serial.begin(115200);
  delay(5000);
  Serial.println("TESTING SETUP -- Complete");

  /*GPS Setup*/
   // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  delay(5000);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
  Serial.println("GPS SETUP -- Complete");


  /*Watch Setup*/
  randomSeed(analogRead(0));
  //setTime(12,59,15,12,04,2020);
  prevFn = 0;
  Serial.println("FLOW SETUP -- Complete");
}

void loop()                    
{
  /* GPS loop nonsense */
  char c = GPS.read();
  if ((c) && (GPSECHO))
    Serial.write(c);
  if (GPS.newNMEAreceived()) {

    if (!GPS.parse(GPS.lastNMEA()))
      return;  
  }
  

  Serial.print("GPS has fix: "); Serial.println(GPS.fix == true);
  printGPS(GPS);

  int choice = dialSelect();
  Serial.print("Choice is: ");Serial.println(choice);
  debugOut(choice);

  
  time_t curTime = now();
  ring->clear();
  ring->show();
   
  /*Clear ring if different from last fn*/
  if(prevFn != choice){
    Serial.print("Choice Switched From ");Serial.print(prevFn);Serial.print(" to "); Serial.println(choice);
  }

 /* fn Choice*/
  if(choice == 0){
      ring->clear();
      ring->show();
  } else if (choice == 1){
     printTime(curTime);
     watch->showTime(curTime);
  } else if(choice == 2){
      float heading = randFloat(0,360);
      printFloat("heading",heading);
      watch->showHeading(heading);
  } else if(choice == 3){
     float testSpeed = randFloat(0,200);
      printFloat("Speed",testSpeed);
      watch->showSpeed(testSpeed);
  }
  else{
    writeToRing(8);
  }
  
  prevFn = choice;
  
  delay(2000);
}

/*Random Float*/
float randFloat(int lower, int upper){
  float randFloat = random(lower,upper);
  return randFloat;
}

/*print gps stats*/
void printGPS(Adafruit_GPS g){
  if(g.fix == true){
    debugOut(15);
    Serial.print("Quality: ");Serial.println(g.fixquality);
    Serial.print("Time: ");
    Serial.print(g.hour, DEC); Serial.print(':');Serial.print(g.minute, DEC); Serial.print(':');Serial.print(g.seconds, DEC); Serial.println('.');
    Serial.print("Longitude: ");Serial.println(g.longitude, 4);
    Serial.print("Longitude Degrees: ");Serial.print(g.longitudeDegrees, 4);Serial.println(g.lon);
    Serial.print("Angle: ");Serial.println(g.angle);
    Serial.print("Speed (kn): "); Serial.println(g.speed);
    Serial.print("Speed (kmph): "); Serial.println(g.speed * 1.852);
    Serial.print("Satellites: "); Serial.println((int) g.satellites);
    setTime(gTools.grabTime());
  } else {
    Serial.println("GPS: NO SIGNAL");
  }
}

/* printTime*/
void printTime(time_t tm){
  Serial.print("Time is: ");Serial.print(hour(tm));Serial.print(":");Serial.print(minute(tm));Serial.print(":");Serial.println(second(tm));
}

void printFloat(String lable, float value){
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
  return (int) ((int) reading / 100);
}
