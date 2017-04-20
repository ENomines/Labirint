#include "CRobot.h"

CRobot::CRobot()
{
  leftMotor = ev3dev::large_motor(ev3dev::OUTPUT_A);
  rightMotor = ev3dev::large_motor(ev3dev::OUTPUT_B);

  forwardSensor = ev3dev::ultrasonic_sensor(ev3dev::INPUT_1);
  leftSensor = ev3dev::ultrasonic_sensor("in2:i2c1");
  rightSensor = ev3dev::ultrasonic_sensor("in3:i2c1");

  leftMotor.reset();
  rightMotor.reset();

  leftMotor.set_stop_action("hold");
  rightMotor.set_stop_action("hold");
}

void CRobot::turn(ev3dev::large_motor motor, int speed, int position)
{
	motor.set_position(position);
	motor.set_speed_sp(speed).run_to_abs_pos();
}

void CRobot::turnLeft()
{
     turn(leftMotor, 600, 208);
     turn(rightMotor, 600, -208);

     while(leftMotor.state().count("running") || rightMotor.state().count("running"))
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
void CRobot::turnRight()
{
     turn(leftMotor, 600, -208);
     turn(rightMotor, 600, 208);

     while(leftMotor.state().count("running") || rightMotor.state().count("running"))
       	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

 void CRobot::runForward(int speed, int position)
 {
   leftMotor.set_position(position);
   rightMotor.set_position(position);

   leftMotor.set_speed_sp(speed);
   rightMotor.set_speed_sp(speed);

   leftMotor.run_to_abs_pos();
   rightMotor.run_to_abs_pos();

   activation = false;

   oldErrorLeft = 0, oldErrorRight = 0;

   while (leftMotor.state().count("running") || rightMotor.state().count("running"))
   {
     std::this_thread::sleep_for(std::chrono::milliseconds(10));

     if (leftMotor.speed() >= speed || rightMotor.speed() >= speed) activation = true;

     if (leftMotor.position() >= 0 || rightMotor.position() >= 0)
     {
         break;
     }

     if (activation)
     {
       error = speed - leftMotor.speed();
       deltaSpeed = error / kP + (error - oldErrorLeft) / kD;
       oldErrorLeft = error;

       leftMotor.set_speed_sp(leftMotor.speed() + deltaSpeed).run_to_abs_pos();

       error = speed - rightMotor.speed();
       deltaSpeed = error / kP + (error - oldErrorRight) / kD;
       oldErrorRight = error;

       rightMotor.set_speed_sp(rightMotor.speed() + deltaSpeed).run_to_abs_pos();
     }
   }
}
 void CRobot::runBack(int speed, int position)
 {
 	   leftMotor.set_position(position);
     rightMotor.set_position(position);

     leftMotor.set_speed_sp(speed).run_to_abs_pos();
     rightMotor.set_speed_sp(speed).run_to_abs_pos();

     while(leftMotor.state().count("running") || rightMotor.state().count("running"))
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
 }

 CRobot::~CRobot()
 {
   leftMotor.reset();
   rightMotor.reset();
 }
