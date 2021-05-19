/*
Bennett Lewis - May 19, 2021
Summer2021-Release
*/

/* INCLUDES */

// For GPS
#include <Adafruit_GPS.h>
#include <GPSTools.h>
#include <SoftwareSerial.h>

//For Ring
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include <ADWatch.h>

/* END INCLUDES*/

/* MACROS */

//GPS 
#define GPSECHO false

//Ring
#define PIN 6
#define NUM_LEDS 12
#define BRIGHTNESS 10
/* END MACROS */

/* GLOBALS */

//GPS
SoftwareSerial mySerial(3,2);
Adafruit_GPS GPS(&mySerial);
GPSTools gTools = GPSTools(-6);

uint32_t timer = millis();


//Ring
Adafruit_NeoPixel* ring = new Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

//Watch
ADWatch* watch = new ADWatch(ring);
uint8_t prevFn;
// 
/* END GLOBALS */

/* SETUP */

void setup(){
	// GENERAL / DEBUG
	Serial.begin(115200);

	//GPS
	delay(5000);
	Serial.println("Adafruit GPS library basic test!");
	GPS.begin(9600);
	GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
	GPS.sendCommand(PGCMD_ANTENNA);
	delay(1000);
	mySerial.println(PMTK_Q_RELEASE);

	//Ring
  ring->begin();
  ring->clear();
  ring->setBrightness(BRIGHTNESS);
//
//  	//Watch Setup
  	prevFn = 0;
}

/* END SETUP */

/* LOOP */
void loop(){
  GPS.read();
	//GPS GRAB
	if (GPS.newNMEAreceived()) {
		if (!GPS.parse(GPS.lastNMEA()))
			return; 
	}

	/* GPS Poll */
	if (timer > millis())  timer = millis();
	if (millis() - timer > 2000) {
		timer = millis();
		if(GPS.fix == true){
			setTime(GPS.hour,GPS.minute,GPS.seconds,GPS.day,GPS.month,GPS.year);
			//int success = gTools.grabTime(now(),GPS.longitudeDegrees);
      Serial.println("WE HAVE A FIX!");
		}else{
      Serial.println("NO FIX!");
		}
	}	
	/* End GPS Poll */

	// Function Grab
	int choice = dialSelect();
	time_t curTime = now();
	ring->clear();
	ring->show();
	/*Clear ring if different from last fn*/
	if(prevFn != choice){
		watch->flourish((FnColour) choice, 60);
	}

	/* FUNCTION SELECT */
	/* END FUNCTION SELECT */
	prevFn = choice;
	delay(2000);
}
/* END LOOP*/

/* value from the float
 *  reading given by the dial
 */
int dialSelect(){
	float reading = analogRead(A0);
	//Serial.print("Reading: "); Serial.println(reading);
	return (int) ((int) reading / 100);
}
/* HELPER FUNCTIONS */

/* END HELPER FUNCTIONS */
