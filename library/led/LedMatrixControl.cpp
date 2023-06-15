#include "LedMatrixControl.h"

LedMatrixControl::LedMatrixControl(uint8_t pin, uint16_t numPixels) : pixels(numPixels, pin, NEO_GRB + NEO_KHZ800) {}

void LedMatrixControl::begin() {
  pixels.begin();
  pixels.show();
}

void LedMatrixControl::setColor(uint8_t red, uint8_t green, uint8_t blue) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }
  pixels.show();
}

void LedMatrixControl::setBrightness(uint8_t brightness) {
  pixels.setBrightness(brightness);
  pixels.show();
}

void LedMatrixControl::setPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
  pixels.setPixelColor(pixel, pixels.Color(red, green, blue));
  pixels.show();
}

void LedMatrixControl::show() {
  pixels.show();
}

void LedMatrixControl::setLEDStatus(String status) {
  status = removeHashSymbol(status);
  
  String colorStr;
  uint8_t colorIndex = 0;
  
  for (uint16_t i = 0; i < status.length(); i++) {
    char c = status.charAt(i);
    if (c == ',') {
      setPixelColorFromHexString(colorIndex, colorStr);
      colorStr = "";
      colorIndex++;
    } else {
      colorStr += c;
    }
  }
  
  if (colorStr.length() > 0) {
    setPixelColorFromHexString(colorIndex, colorStr);
  }
  
  pixels.show();
}

void LedMatrixControl::setPixelColorFromHexString(uint16_t pixel, String colorStr) {
  uint32_t color = (uint32_t) strtol(colorStr.c_str(), NULL, 16);
  uint8_t red = (color >> 16) & 0xFF;
  uint8_t green = (color >> 8) & 0xFF;
  uint8_t blue = color & 0xFF;
  
  pixels.setPixelColor(pixel, pixels.Color(red, green, blue));
}

String LedMatrixControl::removeHashSymbol(String str) {
  str.replace("#", "");
  return str;
}
