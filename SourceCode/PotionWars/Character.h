#include <iostream>
#include <vector>
#include "Position.h"
#include "random.h"
#define HEIGHT  6
#define WIDTH 8

using std::vector;
using std::string;
#pragma once
class character : public position
{
private:
	string name = "";
	int level = 0;
	bool isEnemy; //Returns false if Player
	bool hasMoved; //Returns true if enemy has moved, so it doesn't move again in the same turn
	char icon = '@';
	static std::vector<character>* AliveEnemies;
public:
	character(string n, bool isCharEnemy) //Constructor
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
#pragma region Getters

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

#pragma endregion
#pragma region Setters


	
#pragma endregion
#pragma region Enemy code

	/// <summary>
	/// Makes the enemy move;(
	/// </summary>
	void enemyMovement()
	{
		//Enemy will move to a new position
		if (!hasMoved)
		{
			std::uniform_int_distribution<int> RandomInt(-1, 1);
			int RandomPos = RandomInt(Random::engine);
			std::uniform_int_distribution<int> RandomInt(1, 2); //<-- It'll be in x if 1 or y if 2
			int RandomCoordinate = RandomInt(Random::engine);

			hasMoved = true;
			position* newPos = new position(RandomPos * RandomCoordinate%2, RandomPos * 1%RandomCoordinate);
			cout << newPos << endl;
			//return newPos;
		}
	}
	bool getIsMoved()
	{
		return hasMoved;
	}
	void setIsMoved()
	{

	}
#pragma endregion
};
