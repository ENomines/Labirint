#include "ev3dev.h"

#include <thread>
#include <chrono>

#include <iostream>

class CRobot
{
  public:
  	void turn(ev3dev::large_motor motor, int speed, int position);
    void turnLeft(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor);
    void turnRight(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor);

    void runForward(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor, int speed, int position);
    void runBack(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor, int speed, int position);
};