#ifndef GyroActivity_h
#define GyroActivity_h

#include "Arduino.h"

enum Direction {LEFT, RIGHT, FORWARD, BACKWARD, NONE};
enum JumpState { STAND, JUMPING, JUMPED };

class GyroActivity {
  public:
    GyroActivity();
    void begin();
    bool isJumping();
    bool isFalling();
    int countSteps();
    Direction getTilt();
    void readGyroData(); // New method to read gyro data
    bool isTiltedLeft();
    bool isTiltedRight();
    bool isTiltedForward();
    bool isTiltedBackward();
    
  private:
    int16_t x, y, z;
    float Ax, Ay, Az;
    float roll, pitch;
    JumpState jumpState = STAND;
};

#endif