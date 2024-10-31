#include <iostream>
#include <vector>
#include "Position.h"
#define HEIGHT  6
#define WIDTH 8

using std::vector;
using std::string;
#pragma once
class character : protected position
{
private:
	string name = "";
	int level = 0;
	bool isEnemy; //Returns false if Player
	char icon = '@';
	static std::vector<character>* AliveEnemies;
public:
	character(string n, bool isCharEnemy)
	{
		name = n;
		isEnemy = isCharEnemy;
		if (isEnemy)
		{
			if (AliveEnemies == nullptr)
			{
				AliveEnemies = new vector<character>;
			}
			icon = '&';
			AliveEnemies->push_back(*this);
		}
		else if (!isEnemy)
		{
			icon = '@';
		}
	}
	string getName()
	{
		return name;
	}

	static int getCountOfEnemy()
	{
		return AliveEnemies->size();
	}

	char getSymbol()
	{
		return icon;
	}
	int getPosX()
	{
		return x;
	}
	int getPosY()
	{
		return y;
	}
	void setPosX(int n)
	{
		if (x + n >= 0 && x + n < WIDTH)
		{
			x += n;
		}
	}
	void setPosY(int n)
	{
		if (y + n >= 0 && y + n < HEIGHT)
		{
			y += n;
		}
	}

};
