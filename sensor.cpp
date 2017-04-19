#include "CRobot.h"

int main()
{
  CRobot robot;

  while (true) {
    std::cout << "ForwardSensor: " << robot.forwardSensor.distance_centimeters() << std::endl;
    std::cout << "LeftSensor: " << robot.leftSensor.distance_centimeters() << std::endl;
    std::cout << "RightSensor: " << robot.rightSensor.distance_centimeters() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    system("clear");

  }
}
