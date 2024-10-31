#include <iostream>
#include "Character.h"
#include "Potion.h"

#pragma once

class Unit
{
private:
	ingredient* ingredientPosition = nullptr;
	character* enemyPosition = nullptr;
public:
	Unit(ingredient* I = nullptr)
	{
		ingredientPosition = I;
	}

	Unit(character* E = nullptr)
	{
		enemyPosition = E;
	}
	char GetSymbolInLocation()
	{
		if (ingredientPosition != nullptr)
		{
			return ingredientPosition->getSymbol();
		}
		else if (enemyPosition != nullptr)
		{
			return enemyPosition->getSymbol();
			//Tells the enemy to move position through a function
			//Actually I need to do this differently
			
		}
		else
		{
			return ' ';
		}
	}

	/// <summary>
	/// Will return true if player dies
	/// </summary>
	/// <returns>Return true to confirm death of player</returns>
	bool getUnit()
	{
		///Adds the an extra ingredient to the player's inventory 
		if (ingredientPosition != nullptr)
		{
			ingredientPosition->setCount(1);
			return false;
		}
		else if (enemyPosition != nullptr)
		{
			//return true;
		}
		//And then also delete this unit and replace it with nullptr in the array. 
		delete this;

	}
};

