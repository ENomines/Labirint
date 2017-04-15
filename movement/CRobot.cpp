#include "CRobot.h"

CRobot::CRobot()
{
  leftMotor = ev3dev::large_motor(ev3dev::OUTPUT_A);
  rightMotor = ev3dev::large_motor(ev3dev::OUTPUT_B);

  forwardSensor = ev3dev::ultrasonic_sensor(ev3dev::INPUT_1);
  leftSensor = ev3dev::ultrasonic_sensor(ev3dev::INPUT_2);
  rightSensor = ev3dev::ultrasonic_sensor(ev3dev::INPUT_3);

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

      static int deltaSpeed = 0;

      while(_left_motor.state().count("running") && _right_motor.state().count("running"))
      {
        if(leftSensor.distance_centimeters() < 30)
        {
           deltaSpeed = leftSensor.distance_centimeters() - 15;
          _left_motor.set_speed_sp(speed + deltaSpeed).run_to_abs_pos();
        }

        if(rightSensor.distance_centimeters() < 30)
        {
           deltaSpeed = rightSensor.distance_centimeters() - 15;
          _right_motor.set_speed_sp(speed + deltaSpeed).run_to_abs_pos();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
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
