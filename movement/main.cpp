#include "CRobot.h"

int main()
{
  try
  {
    CRobot robot;

    const int position = -360 * 2 + 72;
    const int speed = 500;

    robot.runForward(speed, position);
    robot.runForward(speed, position);
    robot.runForward(speed, position);
    robot.turnRight();
    robot.turnRight();
    robot.runForward(speed, position);
    robot.turnLeft();
    robot.runForward(speed, position);
    robot.turnRight();
    robot.runForward(speed, position);
    robot.runForward(speed, position);
    robot.turnLeft();
    robot.runForward(speed, position);
    robot.turnLeft();
    robot.runForward(speed, position);
    robot.turnRight();
    robot.runForward(speed, position);
    robot.turnLeft();
    robot.runForward(speed, position);
    robot.runForward(speed, position);

  } catch (std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
