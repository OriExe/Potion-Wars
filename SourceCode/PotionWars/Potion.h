#include <string>
#include <iostream>
#include <list>
#pragma once
using std::string;
using std::list;
using std::vector;
class ingredient
{
private:
	string name = "";
	char symbolInGame = 'Z';
	static vector<ingredient> ingredientsInGame;
public:
	ingredient(string n = "placeHolder", char c = 'P')
	{
		if (c != 'P')
		{
			name = n;
			symbolInGame = c;
			ingredientsInGame.push_back(*this);
		}

	}
	string getName()
	{	
		return name;
	}
	char getSymbol()
	{
		return symbolInGame;
	}
	/// <summary>
	/// Outputs a random ingredient
	/// </summary>
	static ingredient outPutRandomIngredient(std::default_random_engine randomNumberGenerator)
	{
		std::uniform_int_distribution<int> Randomint(0, ingredientsInGame.size()-1);
		int RandomIntResult = Randomint(randomNumberGenerator);
		return ingredientsInGame[RandomIntResult];
	}
};


class potionType
{
private:
	string name;
	list<ingredient> ingredientsrequired;
public:
	//Adds new type
	potionType(string n)
	{
		name = n;
	}
	//Adds ingredients
	void addIngredient(ingredient* i)
	{
		ingredientsrequired.push_back(*i); 
	}
};
class Potion
{
private:
	int level;
	potionType* type;
public:
	Potion(potionType* t, int l)
	{
		type = t;
		level = l;
	}
};
