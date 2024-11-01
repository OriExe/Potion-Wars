#include <iostream>
#define HEIGHT  6
#define WIDTH 8

#pragma once
using std::cout;
using std::endl;
class position
{
private:
	int x = 0;
	int y = 0;
public:
	position(int newX = 0, int newY = 0)
	{
		x = newX;
		y = newY;
	}
	int getPosX()
	{
		return x;
	}
	int getPosY()
	{
		return y;
	}
	/// <summary>
	/// Returns false if input is invalid
	/// </summary>
	bool setPosX(int n)
	{
		if (x + n >= 0 && x + n < WIDTH)
		{
			x += n;
			return true;
		}
		else
		{
			return false;
			cout << "Invalid Input reached" << endl;
		}
	}

	/// <summary>
	/// Returns false if input is invalid
	/// </summary>
	bool setPosY(int n)
	{

		if (y + n >= 0 && y + n < HEIGHT)
		{
			y += n;
			return true;
		}
		else
		{
			return false;
			cout << "Invalid Input reached" << endl;
		}
	}
};