

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <ADbug.h>

/*GPS Nonsesne*/
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  true

void setup()
{
  /* GPS BS */
  Serial.begin(115200);
  delay(5000);
  Serial.println("Adafruit GPS library basic test!");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);

  /* Debug */
  setVerbose(false);
}

uint32_t timer = millis();
void loop()                     
{
  char c = GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) 
      return;  
  }
  if (timer > millis())  timer = millis();
  if (millis() - timer > 2000) {
    timer = millis();
    int choice = dialSelect();
    debugOut(choice);
    if(GPS.fix){
      printGPS(GPS);
    }

  }
}

/** Returns an int value from the float
 *  reading given by the dial
 */
int dialSelect(){
  float reading = analogRead(A0);
  //Serial.print("Reading: "); Serial.println(reading);
  return (int) ((int) reading / 100);
}
