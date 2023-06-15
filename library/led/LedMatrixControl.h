#ifndef LedMatrixControl_h
#define LedMatrixControl_h

#include "Adafruit_NeoPixel.h"

class LedMatrixControl {
  public:
    LedMatrixControl(uint8_t pin, uint16_t numPixels);

    void begin();
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    void setBrightness(uint8_t brightness);
    void setPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
    void show();
    void setLEDStatus(String status);

  private:
    Adafruit_NeoPixel pixels;
    void setPixelColorFromHexString(uint16_t pixel, String colorStr);
    String removeHashSymbol(String str);
};

#endif
