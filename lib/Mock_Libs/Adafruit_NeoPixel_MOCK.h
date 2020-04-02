#ifndef ADAFRUIT_NEOPIXEL_M_H
#define ADAFRUIT_NEOPIXEL_M_H

#include <cinttypes>

uint32_t GetVal(int,char);

class Adafruit_NeoPixel
{
 public:

  Adafruit_NeoPixel(void);
  ~Adafruit_NeoPixel();

  void              show(void);
  void              setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
  void              setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b,uint8_t w);
  void              setPixelColor(uint16_t n, uint32_t c);
  void              setBrightness(uint8_t);
  void              clear(void);

  static uint32_t   Color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
  }
  static uint32_t   Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    	return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
  }
};

#endif

