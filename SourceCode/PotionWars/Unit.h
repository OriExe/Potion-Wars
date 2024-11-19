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
	/// <summary>
	/// Returns the unit that is stored in that space
	/// </summary>
	/// <returns>The symbol of the object in that space or a blank space</returns>
	char GetSymbolInLocation()
	{
		//If Ingrdient
		if (ingredientPosition != nullptr)
		{
			return ingredientPosition->getSymbol(); // <- Sends Ingredient
		}
		//If Enemy
		else if (enemyPosition != nullptr)
		{
			//if (!enemyPosition->getIsMoved()) //< - Checks if enemy has moved 
			//{
			//	enemyPosition->enemyMovement();
			//	return '.';
			//}
			
			return enemyPosition->getSymbol(); // <- Sends enemy
			
		}
		else
		{
			return ' ';
		}
	}

	/// <summary>
	/// Calls when the player is standing over an enemy or ingredient and decides the action that'll be taken
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
	/// <summary>
	/// Should only run is enemy is this unit
	/// </summary>
	character* getEnemy()
	{
		if (enemyPosition != nullptr)
		{
			return enemyPosition;
		}
	}
};

