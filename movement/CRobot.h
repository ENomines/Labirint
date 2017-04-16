#include "ev3dev.h"

#include <thread>
#include <chrono>

#include <iostream>

class CRobot
{
  public:
    CRobot();

    void turnLeft();
    void turnRight();

    void runForward(int speed, int position);
    void runBack(int speed, int position);

  	ev3dev::large_motor leftMotor;
    ev3dev::large_motor rightMotor;

    ev3dev::ultrasonic_sensor forwardSensor;
    ev3dev::ultrasonic_sensor leftSensor;
    ev3dev::ultrasonic_sensor rightSensor;

  private:
  	void turn(ev3dev::large_motor motor, int speed, int position);

    int es = 0;

};
