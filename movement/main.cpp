#include "CRobot.h"

int main()
{
  try
  {
    CRobot robot;

    robot.runForward(500, 360 * 2 - 70);
    robot.runForward(500, 360 * 2 - 70);
    robot.runForward(500, 360 * 2 - 100);

  } catch (std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
