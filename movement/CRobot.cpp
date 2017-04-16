#include "CRobot.h"

CRobot::CRobot()
{
  leftMotor = ev3dev::large_motor(ev3dev::OUTPUT_A);
  rightMotor = ev3dev::large_motor(ev3dev::OUTPUT_B);

  forwardSensor = ev3dev::ultrasonic_sensor(ev3dev::INPUT_1);
  leftSensor = ev3dev::ultrasonic_sensor("in2:i2c1");
  rightSensor = ev3dev::ultrasonic_sensor("in3:i2c1");

	leftMotor.set_stop_action("brake");
	rightMotor.set_stop_action("brake");

  es = leftSensor.distance_centimeters()-rightSensor.distance_centimeters();
}

void CRobot::turn(ev3dev::large_motor motor, int speed, int position)
{
	motor.set_position_sp(position);
	motor.set_speed_sp(speed).run_to_rel_pos();
}

void CRobot::turnLeft()
{
     turn(leftMotor, 600, 180);
     turn(rightMotor, 600, -180);

     while(leftMotor.state().count("running") && rightMotor.state().count("running"))
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
void CRobot::turnRight()
{
     turn(leftMotor, 600, -210);
     turn(rightMotor, 600, 210);

     while(leftMotor.state().count("running") && rightMotor.state().count("running"))
       	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

 void CRobot::runForward(int speed, int position)
 {
      leftMotor.set_position(-position);
      rightMotor.set_position(-position);

      rightMotor.set_speed_sp(speed).run_to_abs_pos();
			leftMotor.set_speed_sp(speed).run_to_abs_pos();

      static int vmax = 800;
      static float k1 = 0.8;
      static float k2 = 4;
      static float v = 500;
      static float errold = 0;

      static int err,u,mB,mC;

      while(leftMotor.state().count("running") && rightMotor.state().count("running"))
      {
        if (leftMotor.position() == 0 && rightMotor.position() == 0) break;
        err = leftSensor.distance_centimeters() - rightSensor.distance_centimeters() - es;

        u = k1 * err + k2 * (err - errold);
        err = errold;

        mB = v - u;
        mC = v + u;

        if (abs(mB)>vmax) mB = vmax;
        if (abs(mC)>vmax) mC = vmax;

        if(leftSensor.distance_centimeters() < 30)
        {
           rightMotor.set_speed_sp(mC).run_to_abs_pos();
        }
        if(rightSensor.distance_centimeters() < 30)
        {
          leftMotor.set_speed_sp(mB).run_to_abs_pos();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
}
 void CRobot::runBack(int speed, int position)
 {
 	   leftMotor.set_position(position);
     rightMotor.set_position(position);

     leftMotor.set_speed_sp(speed).run_to_abs_pos();
     rightMotor.set_speed_sp(speed).run_to_abs_pos();

     while(leftMotor.state().count("running") && rightMotor.state().count("running"))
       std::this_thread::sleep_for(std::chrono::milliseconds(10));
 }
