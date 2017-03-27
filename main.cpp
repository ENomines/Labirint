#include "CRobot.h"

#define MAX_LENGTH 16

int field[9][9] = 
{
 {1, 1, 1, 1, 1, 1, 1, 1, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 1},
 {1, 1, 1, 1, 1, 1, 1, 1, 1}
};

bool checkForward(int x, int y);
bool checkBack(int x, int y);
bool checkLeft(int x, int y);
bool checkRight(int x, int y);

void checkMovement(int x, int y);

void checkSensors(ev3dev::ultrasonic_sensor leftSensor, ev3dev::ultrasonic_sensor rightSensor, ev3dev::ultrasonic_sensor forwardSensor, int x, int y);

int getLength(int x, int y);

bool bMoveForward = false;
bool bMoveBack = false;
bool bMoveLeft = false;
bool bMoveRight = false;

int minLength = MAX_LENGTH;
int leftCounter = 0, rightCounter = 0;

int main() 
{  
   ev3dev::large_motor _left_motor(ev3dev::OUTPUT_B);
   ev3dev::large_motor _right_motor(ev3dev::OUTPUT_C);

   ev3dev::ultrasonic_sensor leftSensor("in2:i2c1");
   ev3dev::ultrasonic_sensor rightSensor("in3:i2c1");
   ev3dev::ultrasonic_sensor forwardSensor(ev3dev::INPUT_1);

   _left_motor.reset();
   _right_motor.reset();

   CRobot robot;

   int i = 1, j = 1;
  
   field[i][j] = -1;

   try
   {
     while(true)
     {
       checkSensors(leftSensor, rightSensor, forwardSensor, i, j);
   	   checkMovement(i, j);

   	   if(bMoveForward)
   	   {
        if(leftCounter == 1) 
        {
          robot.turnRight(_left_motor,_right_motor);
          leftCounter = 0;
        }

        if(leftCounter == 3)
        {
        	robot.turnLeft(_left_motor,_right_motor);
        	leftCounter = 0;
        }

        if(rightCounter == 1)
        {
        	robot.turnLeft(_left_motor,_right_motor);
        	rightCounter = 0;
        }

        if(rightCounter == 3)
        {
          robot.turnRight(_left_motor,_right_motor);
          rightCounter = 0;
        }

   	   	robot.runForward(_left_motor, _right_motor, 500, 360 * 2);

   	   	i += 2;

   	   	field[i][j] = -1;
   	   } 
   	   else if(bMoveLeft)
   	   {
         robot.turnLeft(_left_motor, _right_motor);

         if(rightCounter == 1) leftCounter = 3;
         if(rightCounter == 2) leftCounter = 2;
         if(rightCounter == 3) leftCounter = 1;

         leftCounter++;
 
         if(leftCounter > 3) leftCounter = 0;
          
         while(checkLeft(i, j))
         {
           robot.runForward(_left_motor, _right_motor, 500, 360 * 2);

           if(leftCounter == 0)
           {
           	i += 2;
           }
           if(leftCounter == 1)
           {
           	 j += 2;
           } 
           else if(leftCounter == 2)
           {
             i -= 2;
           }
           else if(leftCounter == 3)
           {
           	 j -= 2;
           }
           field[i][j] = -1;
           checkSensors(leftSensor,rightSensor,forwardSensor,i,j);
         }
   	   } 
   	   else if(bMoveRight)
   	   {
         robot.turnRight(_left_motor,_right_motor);

         if(leftCounter == 1) rightCounter = 3;
         if(leftCounter == 2) rightCounter = 2;
         if(leftCounter == 3) rightCounter = 1;

         rightCounter++;

         if(rightCounter > 3) rightCounter = 0;
          
        while(checkRight(i, j))
         {
           robot.runForward(_left_motor, _right_motor, 500, 360);

           if(rightCounter == 0)
           {
           	i += 2;
           }
           if(rightCounter == 1)
           {
           	 j -= 2;
           } 
           else if(rightCounter == 2)
           {
             i -= 2;
           }
           else if(rightCounter == 3)
           {
           	 j += 2;
           }
      
           field[i][j] = -1;
           checkSensors(leftSensor,rightSensor,forwardSensor,i,j);
         }

   	   } 
   	   else if(bMoveBack)
   	   {

   	   } else break;

   	   bMoveForward = false;
   	   bMoveBack = false;
   	   bMoveLeft = false;
   	   bMoveRight = false;
   	 }
   } catch(std::exception &e)
   {
   	 std::cout << "ERROR: " << e.what() << std::endl;

     exit(0);
   }

   return 0;
}

void checkMovement(int x, int y)
{
    static int length = 0;

	if(checkForward(x, y))
	{
      length = getLength(x + 1, y);

      if(length < minLength) 
      {
        minLength = length;

        bMoveForward = true;
      }
	}

	if(checkBack(x, y))
	{
      length = getLength(x - 1, y);

      if(length < minLength) 
      {
        minLength = length;

        bMoveForward = false;
        bMoveBack = true;
      }
	}

	if(checkLeft(x, y))
	{
      length = getLength(x, y + 1);

      if(length < minLength) 
      {
        minLength = length;

        bMoveForward = false;
        bMoveBack = false;
        bMoveLeft = true;
      }
	}

	if(checkRight(x, y))
	{
      length = getLength(x, y - 1);

      if(length < minLength) 
      {
        minLength = length;

        bMoveForward = false;
        bMoveBack = false;
        bMoveLeft = false;
        bMoveRight = true;
      }
	}

	minLength = MAX_LENGTH;
}

void checkSensors(ev3dev::ultrasonic_sensor leftSensor, ev3dev::ultrasonic_sensor rightSensor, ev3dev::ultrasonic_sensor forwardSensor, int x, int y)
{
    if(forwardSensor.distance_centimeters() <= 15)
    {
      if(leftCounter == 0) field[x + 1][y] = 1;
      else if(leftCounter == 1) field[x][y + 1] = 1;
      else if(leftCounter == 2) field[x - 1][y] = 1;
      else if(leftCounter == 3) field[x][y - 1] = 1;
    }

    if(leftSensor.distance_centimeters() <= 15)
    {
      if(leftCounter == 0) field[x][y + 1] = 1;
      else if(leftCounter == 1) field[x - 1][y] = 1;
      else if(leftCounter == 2) field[x][y - 1] = 1;
      else if(leftCounter == 3) field[x + 1][y] = 1;
    }

    if(rightSensor.distance_centimeters() <= 15)
    {
      if(leftCounter == 0) field[x][y - 1] = 1;
      else if(leftCounter == 1) field[x + 1][y] = 1;
      else if(leftCounter == 2) field[x][y + 1] = 1;
      else if(leftCounter == 3) field[x - 1][y] = 1;
    }

	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			std::cout << field[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool checkForward(int x, int y)
{
	return field[x + 1][y] != 1;
}

bool checkBack(int x, int y)
{
	return field[x - 1][y] != 1;
}

bool checkLeft(int x, int y)
{
	return field[x][y + 1] != 1;
}

bool checkRight(int x, int y)
{
	return field[x][y - 1] != 1;
}

int getLength(int x, int y)
{
  static int finishX = 8;
  static int finishY = 8;

  return abs(finishX - x) + abs(finishY - y);
}



