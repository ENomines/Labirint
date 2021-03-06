#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>

#define MAX_LENGTH 12

int field[9][9] =
{
 {2, 2, 2, 2, 2, 2, 2, 2, 2},
 {2, 0, 2, 0, 0, 0, 2, 4, 2},
 {2, 0, 2, 0, 2, 2, 2, 0, 2},
 {2, 0, 0, 0, 2, 0, 2, 0, 2},
 {2, 0, 2, 0, 2, 0, 2, 0, 2},
 {2, 0, 2, 0, 2, 0, 0, 0, 2},
 {2, 0, 2, 0, 2, 0, 2, 0, 2},
 {2, 3, 2, 0, 0, 0, 2, 0, 2},
 {2, 2, 2, 2, 2, 2, 2, 2, 2}
};

bool CheckForward(int x, int y);
bool CheckBack(int x, int y);
bool CheckLeft(int x, int y);
bool CheckRight(int x, int y);

void CheckMovement(int x, int y);

int GetLength(int x, int y);

void GoHome(int x, int y);

bool bMoveForward = false;
bool bMoveBack = false;
bool bMoveLeft = false;
bool bMoveRight = false;

int minLength = MAX_LENGTH;
int minRating = 2;
int leftCounter = 0, rightCounter = 0;

int main()
{
   int i = 7, j = 1;

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

       if(field[i][j] == 4) break;

   	   CheckMovement(i, j);

   	   if(bMoveForward)
   	   {
          field[i + 1][j] = 1;

   	   	  if(!CheckLeft(i,j) && !CheckRight(i,j) && !CheckBack(i,j) && field[i][j] != 3) field[i + 1][j] = 2;

   	   	  i += 2;
   	   }
   	   else if(bMoveLeft)
   	   {
   	   	   field[i][j + 1] = 1;

   	   	   if(!CheckForward(i,j) && !CheckBack(i,j) && !CheckRight(i,j) && field[i][j] != 3) field[i][j + 1] = 2;

           j += 2;
   	   }
   	   else if(bMoveRight)
   	   {
   	   	   field[i][j - 1] = 1;

   	   	   if(!CheckForward(i,j) && !CheckBack(i,j) && !CheckLeft(i,j) && field[i][j] != 3) field[i][j - 1] = 2;

           j -= 2;
   	   }
   	   else if(bMoveBack)
   	   {
   	   	field[i - 1][j] = 1;

        if(!CheckLeft(i,j) && !CheckRight(i,j) && !CheckForward(i,j) && field[i][j] != 3) field[i - 1][j] = 2;

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

   GoHome(i, j);

   return 0;
}

void CheckMovement(int x, int y)
{
    static int length = 0;
    static int rating = 0;

	if(CheckForward(x, y))
	{
      rating = field[x + 1][y];

      if(rating == minRating)
      {
        length = GetLength(x + 1, y);

        if(length < minLength)
        {
          minLength = length;
          minRating = rating;

          bMoveForward = true;
        }
      } else if(rating < minRating)
      {
        length = GetLength(x + 1, y);

        minLength = length;
        minRating = rating;

        bMoveForward = true;
      }
	}

	if(CheckBack(x, y))
	{
      rating = field[x - 1][y];

      if(rating == minRating)
      {
        length = GetLength(x - 1, y);

        if(length < minLength)
        {
          minLength = length;
          minRating = rating;

          bMoveForward = false;
          bMoveBack = true;
        }
      } else if(rating < minRating)
      {
        length = GetLength(x - 1, y);

      	minLength = length;
      	minRating = rating;

        bMoveForward = false;
        bMoveBack = true;
      }
	}

	if(CheckLeft(x, y))
	{
      rating = field[x][y + 1];

      if(rating == minRating)
      {
        length = GetLength(x, y + 1);

        if(length < minLength)
        {
          minLength = length;
          minRating = rating;

          bMoveForward = false;
          bMoveBack = false;
          bMoveLeft = true;
        }
      } else if(rating < minRating)
      {
        length = GetLength(x, y + 1);

      	minLength = length;
      	minRating = rating;

        bMoveForward = false;
        bMoveBack = false;
        bMoveLeft = true;
      }
	}

	if(CheckRight(x, y))
	{
	  rating = field[x][y - 1];

      if(rating == minRating)
      {
        length = GetLength(x, y - 1);

        if(length < minLength)
        {
          minLength = length;
          minRating = rating;

          bMoveForward = false;
          bMoveBack = false;
          bMoveLeft = false;
          bMoveRight = true;
        }
      } else if(rating < minRating)
      {
        length = GetLength(x, y - 1);

      	minLength = length;
      	minRating = rating;

        bMoveForward = false;
        bMoveBack = false;
        bMoveLeft = false;
        bMoveRight = true;
      }
	}

	minLength = MAX_LENGTH;
	minRating = 2;
}

bool CheckForward(int x, int y)
{
	return field[x + 1][y] != 2;
}

bool CheckBack(int x, int y)
{
	return field[x - 1][y] != 2;
}

bool CheckLeft(int x, int y)
{
	return field[x][y + 1] != 2;
}
bool CheckRight(int x, int y)
{
	return field[x][y - 1] != 2;
}

int GetLength(int x, int y)
{
  static int finishX = 1;
  static int finishY = 7;

  return abs(finishX - x) + abs(finishY - y);
}

void GoHome(int x, int y)
{
	while(true)
	{
      system("clear");

       for(int i = 0; i < 9; i++)
       {
         for(int j = 0; j < 9; j++)
         {
           std::cout << field[i][j] << " ";
         }
         std::cout << std::endl;
       }
      std::cout << std::endl;

      std::cout << x << " " << y << std::endl;

      if(field[x][y] == 3) break;

      if(field[x + 1][y] == 1)
      {
        x += 2;

        field[x - 1][y] = 2;
      }
      else if(field[x - 1][y] == 1)
      {
      	x -= 2;

        field[x + 1][y] = 2;
      }
      else if(field[x][y + 1] == 1)
      {
      	y += 2;

      	field[x][y - 1] = 2;
      }
      else if(field[x][y - 1] == 1)
      {
      	y -= 2;

      	field[x][y + 1] = 2;
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}
