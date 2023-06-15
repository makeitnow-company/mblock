#include <Wire.h>
#include <math.h>
#include "GyroActivity.h"

#define LIS2DW12_ADDR 0x19
#define LIS2DW12_WHO_AM_I 0x0F
#define LIS2DW12_CTRL1 0x20
#define LIS2DW12_OUT_X_L 0x28
#define LIS2DW12_OUT_X_H 0x29
#define LIS2DW12_OUT_Y_L 0x2A
#define LIS2DW12_OUT_Y_H 0x2B
#define LIS2DW12_OUT_Z_L 0x2C
#define LIS2DW12_OUT_Z_H 0x2D



GyroActivity::GyroActivity() {
}

void GyroActivity::begin() {
  Wire.begin();
  
  // Check the LIS2DW12 Who Am I register
  Wire.beginTransmission(LIS2DW12_ADDR);
  Wire.write(LIS2DW12_WHO_AM_I);
  Wire.endTransmission();
  Wire.requestFrom(LIS2DW12_ADDR, 1);
  
  if(Wire.read() == 0x44) {
    Serial.println("LIS2DW12 detected!");
  } else {
    Serial.println("LIS2DW12 not detected. Check your connections.");
    while(1); // halt if no device detected
  }

  // Enable LIS2DW12
  Wire.beginTransmission(LIS2DW12_ADDR);
  Wire.write(LIS2DW12_CTRL1);
  Wire.write(0x57); // Set 100 Hz ODR, High-performance mode
  Wire.endTransmission();
}


void GyroActivity::readGyroData() {
  Wire.beginTransmission(LIS2DW12_ADDR);
  Wire.write(LIS2DW12_OUT_X_L | 0x80); // 0x80 for auto increment
  Wire.endTransmission();

  Wire.requestFrom(LIS2DW12_ADDR, 6);
  x = Wire.read() | (Wire.read() << 8);
  y = Wire.read() | (Wire.read() << 8);
  z = Wire.read() | (Wire.read() << 8);

  // Convert to g's
  Ax = (float)x / 16384.0;
  Ay = (float)y / 16384.0;
  Az = (float)z / 16384.0;
  
  roll = atan2(Ay, Az) * 180.0 / PI;
  pitch = atan2(-Ax, sqrt(Ay * Ay + Az * Az)) * 180.0 / PI;
}

bool GyroActivity::isJumping() {
  // Your jumping detection algorithm here. This is a dummy function.
  readGyroData();
  switch (jumpState) {
    case STAND:
      if (Ax > 0.0) {
        jumpState = JUMPING;
        return true;
      }
      break;
    case JUMPING:
      if (Ax < -1.8) {
        jumpState = JUMPED;
      }
      break;
    case JUMPED:
      if (Ax > -1.1 && Ax < -0.9) { // -1 근처이면 STAND로 감지
        jumpState = STAND;
      }
      break;
  }
  return false;

}

bool GyroActivity::isFalling() {
  // Your falling detection algorithm here. This is a dummy function.
  return false;
}

int GyroActivity::countSteps() {
  // Your step counting algorithm here. This is a dummy function.
  return 0;
}

Direction GyroActivity::getTilt() {
  // Your tilt detection algorithm here. This is a dummy function.
  // Get new gyro data
  readGyroData();

  // Check for left tilt
  if (roll > -170 && roll < -90) {
    return LEFT;
  }
  
  // Check for right tilt
  if (roll < 170 && roll > 90) {
    return RIGHT;
  }

  // Check for forward tilt
  if (pitch < -15 && pitch > -90) {
    return FORWARD;
  }

  // Check for backward tilt
  if (pitch > 15 && pitch < 90) {
    return BACKWARD;
  }

  // If none of the above conditions were met, we are not tilting
  return NONE;
}

bool GyroActivity::isTiltedLeft() {
  return getTilt() == LEFT;
}

bool GyroActivity::isTiltedRight() {
  return getTilt() == RIGHT;
}

bool GyroActivity::isTiltedForward() {
  return getTilt() == FORWARD;
}

bool GyroActivity::isTiltedBackward() {
  return getTilt() == BACKWARD;
}
