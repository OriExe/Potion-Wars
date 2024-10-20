#include <string>
#include <iostream>
#include <list>
#pragma once
using std::string;
using std::list;
class ingredient
{
private:
	string name;
public:
	ingredient(string n)
	{
		name = n;
	}
	string getName()
	{
		return name;
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
