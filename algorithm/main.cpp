#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>

#define MAX_LENGTH 12

int field[9][9] = 
{
 {2, 2, 2, 2, 2, 2, 2, 2, 2},
 {2, 0, 0, 0, 0, 0, 0, 0, 2},
 {2, 0, 0, 0, 0, 0, 0, 0, 2},
 {2, 0, 0, 0, 0, 0, 0, 0, 2},
 {2, 0, 2, 0, 0, 0, 0, 0, 2},
 {2, 0, 0, 0, 2, 0, 0, 0, 2},
 {2, 0, 0, 2, 0, 0, 0, 0, 2},
 {2, 0, 2, 0, 0, 0, 0, 0, 2},
 {2, 2, 2, 2, 2, 2, 2, 2, 2}
};

bool checkForward(int x, int y);
bool checkBack(int x, int y);
bool checkLeft(int x, int y);
bool checkRight(int x, int y);

void checkMovement(int x, int y);

int getLength(int x, int y);

bool bMoveForward = false;
bool bMoveBack = false;
bool bMoveLeft = false;
bool bMoveRight = false;

int minLength = MAX_LENGTH;
int leftCounter = 0, rightCounter = 0;

int main() 
{  
   int i = 1, j = 1;
  
   try
   {
     while(true)
     {
       system("clear");

       for(int x = 0; x < 9; x++)
       {
         for(int y = 0; y < 9; y++)
         {
           std::cout << field[x][y] << " ";
         }
         std::cout << std::endl;
       }
       std::cout << std::endl;

       std::cout << i << " " << j << std::endl;  

   	   checkMovement(i, j);

   	   if(i == 7 && j == 7) break;

   	   if(bMoveForward)
   	   {
          field[i + 1][j] = 1;

   	   	  i += 2;
   	   } 
   	   else if(bMoveLeft)
   	   {
   	   	   field[i][j + 1] = 1;
           j += 2; 
   	   } 
   	   else if(bMoveRight)
   	   {
   	   	   field[i][j - 1] = 1;
           j -= 2;
   	   } 
   	   else if(bMoveBack)
   	   {
   	   	field[i - 1][j] = 1;
       
   	   	if(!checkLeft(i,j) && !checkRight(i,j) && !checkForward(i,j)) field[i - 1][j] = 2;

   	    i -= 2;

   	   } else break;

   	   bMoveForward = false;
   	   bMoveBack = false;
   	   bMoveLeft = false;
   	   bMoveRight = false;

       std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

bool checkForward(int x, int y)
{
    if(field[x + 1][y] > field[x - 1][y]) return false; 

	return field[x + 1][y] != 2;
}

bool checkBack(int x, int y)
{
	if(field[x - 1][y] > field[x + 1][y]) return false; 

	return field[x - 1][y] != 2;
}

bool checkLeft(int x, int y)
{
	if(field[x][y + 1] > field[x][y - 1]) return false; 

	return field[x][y + 1] != 2;
}
bool checkRight(int x, int y)
{
	if(field[x][y - 1] > field[x][y + 1]) return false; 

	return field[x][y - 1] != 2;
}

int getLength(int x, int y)
{
  static int finishX = 7;
  static int finishY = 7;

  return abs(finishX - x) + abs(finishY - y);
}



