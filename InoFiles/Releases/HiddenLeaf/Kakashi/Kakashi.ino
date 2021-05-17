

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <ADWatch.h>

/*GPS Nonsesne*/
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  true
/* End GPS Nonsense*/

/* Ring Nonsense */
  #define PIN 6
  #define NUM_LEDS 12
  #define BRIGHTNESS 10
  Adafruit_NeoPixel* ring = new Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
  uint32_t errorColour;
  /* End Ring Nonsense*/

void setup()
{
  /* GPS BS */
  Serial.begin(115200);
  delay(5000);
  //Serial.println("Adafruit GPS library basic test!");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);

  /* Debug */
  //setDebugColour(ring->Color(255,0,0,0));

  /*Ring Setup*/
  errorColour = ring->Color(255,0,0,0);
  ring->begin();
  ring->clear();
  ring->show();
  ring->setBrightness(20);
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
    if(GPS.fix){
       //setTime(GPS.hour,GPS.minute,GPS.seconds,GPS.day,GPS.month,GPS.year);
      //printGPS(GPS);
    }
  }
}

/** Returns an int value from the float
 *  reading given by the dial
 */
int dialSelect(){
  float reading = analogRead(A0);
  return (int) ((int) reading / 100);
}

int setFlag(int index) {
  uint32_t c = ring->Color(255,0,0,0);
  if(NULL == ring){
    return 1;
  } else if(index > 11){
    return 2;
  }

    if(NULL != ring){
        ring->setPixelColor(index,c);
        ring->show();
    }
    return 0;
}

/** Writes testColor to the specified index on the ring
   Returns: 
  0 on success, 
  1 on null ring, 
  2 on invalid index
*/
int writeToRing(int stopIdx){
  uint32_t c = ring->Color(255,0,0,0);
  if(NULL == ring){
    return 1;
  } else if (stopIdx > 11){
    return 2;
  }

  ring->clear();
  ring->show();
    for(int i = 0; i<stopIdx; i++){
        ring->setPixelColor(i,c);
        ring->show();
    }
  return 0;
}
