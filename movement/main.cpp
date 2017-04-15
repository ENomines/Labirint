#include "CRobot.h"

int main()
{
  ev3dev::large_motor _left_motor(ev3dev::OUTPUT_A);
  ev3dev::large_motor _right_motor(ev3dev::OUTPUT_B);

  CRobot robot(_left_motor,_right_motor);

  robot.runForward(_left_motor, _right_motor, 800, 360 * 2 - 80);
//  robot.runForward(_left_motor, _right_motor, 800, 360 * 2 - 80);
//  robot.runForward(_left_motor, _right_motor, 800, 360 * 2 - 80);

  return 0;
}
