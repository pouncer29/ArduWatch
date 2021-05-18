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
#include <SoftwareSerial.h>
#include <GPSTools.h>


/* GPS Nonsense */
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
GPSTools gTools = GPSTools(-6);
#define GPSECHO  true
/* End GPS Nonsense*/
uint8_t prevFn;

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

   /*Watch Setup*/
  randomSeed(analogRead(0));
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
    printGPS(&GPS);
    if(GPS.fix == true){
      setTime(GPS.hour,GPS.minute,GPS.seconds,GPS.day,GPS.month,GPS.year);
      int success = gTools.grabTime(now(),GPS.longitudeDegrees);
      
  /* End GPS Poll */

  	}
  }
}


/*************** SUPPLEMENTAL FUNCTIONS *************************/

/*print gps stats*/
void printGPS(Adafruit_GPS* g){
  if(g->fix == true){
   // debugOut(15);
    Serial.print("Quality: ");Serial.println(g->fixquality);
    Serial.print("Time: ");
    Serial.print(g->hour, DEC); Serial.print(':');Serial.print(g->minute, DEC); Serial.print(':');Serial.print(g->seconds, DEC); Serial.println('.');
    Serial.print("Longitude: ");Serial.println(g->longitude, 4);
    Serial.print("Longitude Degrees: ");Serial.print(g->longitudeDegrees, 4);Serial.println(g->lon);
    Serial.print("Angle: ");Serial.println(g->angle);
    Serial.print("Speed (kn): "); Serial.println(g->speed);
    Serial.print("Speed (kmph): "); Serial.println(g->speed * 1.852);
    Serial.print("Satellites: "); Serial.println((int) g->satellites);
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
