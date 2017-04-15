#include "CRobot.h"

CRobot::CRobot(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor)
{
	leftMotor.set_stop_action("brake");
	rightMotor.set_stop_action("brake");
}

void CRobot::turn(ev3dev::large_motor motor, int speed, int position)
{
	motor.set_position_sp(position);
	motor.set_speed_sp(speed).run_to_rel_pos();
}

void CRobot::turnLeft(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor)
{
     turn(leftMotor, 600, 180);
     turn(rightMotor, 600, -180);

     while(leftMotor.state().count("running") && rightMotor.state().count("running"))
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
void CRobot::turnRight(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor)
{
     turn(leftMotor, 600, -210);
     turn(rightMotor, 600, 210);

     while(leftMotor.state().count("running") && rightMotor.state().count("running"))
       	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

 void CRobot::runForward(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor, int speed, int position)
 {
      leftMotor.set_position(-position);
      rightMotor.set_position(-position);

      rightMotor.set_speed_sp(speed);
			leftMotor.set_speed_sp(speed);

      while(leftMotor.state().count("running") && rightMotor.state().count("running"))
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
 void CRobot::runBack(ev3dev::large_motor leftMotor, ev3dev::large_motor rightMotor, int speed, int position)
 {
 	   leftMotor.set_position(position);
     rightMotor.set_position(position);

     leftMotor.set_speed_sp(speed).run_to_abs_pos();
     rightMotor.set_speed_sp(speed).run_to_abs_pos();

     while(leftMotor.state().count("running") && rightMotor.state().count("running"))
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
 }
