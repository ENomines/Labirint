#include "CRobot.h"

void CRobot::turn(ev3dev::large_motor motor, int speed, int position)
{
	motor.set_position(position);
	motor.set_speed_sp(speed).run_to_abs_pos();
}

void CRobot::turnLeft(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor)
{
     turn(leftMotor, 900, 170);
     turn(rightMotor, 900, -170);

     while(leftMotor.state().count("running") || rightMotor.state().count("running"))
     {
     	std::this_thread::sleep_for(std::chrono::milliseconds(10));
     }

     turn(leftMotor, 3, 1);
     turn(rightMotor, 1, -1);
}
void CRobot::turnRight(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor)
{
     turn(leftMotor, 900, -170);
     turn(rightMotor, 900, 170);

     while(leftMotor.state().count("running") || rightMotor.state().count("running"))
     {
     	std::this_thread::sleep_for(std::chrono::milliseconds(10));
     }

     turn(leftMotor, 3, -1);
     turn(rightMotor, 1, 1);
}

 void CRobot::runForward(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor, int speed, int position)
 {
      leftMotor.set_position(-position);
      rightMotor.set_position(-position);

     leftMotor.set_speed_sp(speed).run_to_abs_pos();
     rightMotor.set_speed_sp(speed).run_to_abs_pos();

     while(leftMotor.state().count("running") || rightMotor.state().count("running"))
     {
     	std::this_thread::sleep_for(std::chrono::milliseconds(10));
     }
     
     runBack(leftMotor, rightMotor, 10, 1);
 }
 void CRobot::runBack(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor, int speed, int position)
 {
 	 leftMotor.set_position(position);
     rightMotor.set_position(position);

     leftMotor.set_speed_sp(speed).run_to_abs_pos();
     rightMotor.set_speed_sp(speed).run_to_abs_pos();

     while(leftMotor.state().count("running") || rightMotor.state().count("running"))
     {
     	std::this_thread::sleep_for(std::chrono::milliseconds(10));
     }
     
 }