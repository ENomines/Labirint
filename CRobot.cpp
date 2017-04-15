#include "CRobot.h"

CRobot::CRobot()
{
  _left_motor = ev3dev::large_motor(ev3dev::OUTPUT_A);
  _right_motor = ev3dev::large_motor(ev3dev::OUTPUT_B);

  forwardSensor = ev3dev::ultrasonic_sensor(ev3dev::INPUT_1);
  leftSensor = ev3dev::ultrasonic_sensor();
  rightSensor = ev3dev::ultrasonic_sensor;

	_left_motor.set_stop_action("brake");
	_right_motor.set_stop_action("brake");
}

void CRobot::turn(ev3dev::large_motor motor, int speed, int position)
{
	motor.set_position(position);
	motor.set_speed_sp(speed).run_to_abs_pos();
}

void CRobot::turnLeft()
{
     turn(_left_motor, 600, 200);
     turn(_right_motor, 600, -200);

     while(_left_motor.state().count("running") && _right_motor.state().count("running"))
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
void CRobot::turnRight()
{
     turn(_left_motor, 600, -200);
     turn(_right_motor, 600, 200);

     while(_left_motor.state().count("running") && _right_motor.state().count("running"))
       	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

 void CRobot::runForward(int speed, int position)
 {
      _left_motor.set_position(-position);
      _right_motor.set_position(-position);

      _left_motor.set_speed_sp(speed).run_to_abs_pos();
      _right_motor.set_speed_sp(speed).run_to_abs_pos();

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
 void CRobot::runBack(int speed, int position)
 {
 	   _left_motor.set_position(position);
     _right_motor.set_position(position);

     _left_motor.set_speed_sp(speed).run_to_abs_pos();
     _right_motor.set_speed_sp(speed).run_to_abs_pos();

     while(_left_motor.state().count("running") && _right_motor.state().count("running"))
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
 }
