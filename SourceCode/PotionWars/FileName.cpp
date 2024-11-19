#include <iostream>
#include <map>
#include <string>
#include<list>
#include <random>
#include <vector>
#include "Potion.h" //Includes class for all potions
#include "conio.h" //Allows keyboard inputs
#include "Unit.h" //Stores information on what is on the boar
#include "Character.h"
#include "Position.h"
#include "Random.h"
#include "thread"
#define HEIGHT  6
#define WIDTH 8

using std::cout;
using std::string;
using std::list;
using std::endl;
using std::vector;

#pragma region Function Definations
void printState(int xPosition, int yPosition);
int generateRandomNumber();
vector<ingredient*> ingredient::ingredientsInGame;
std::default_random_engine Random::engine;
void changeEnemyLocation();
#pragma region Instructions array
string Help[9] =
{
	"Key:",
	"B:Brain",
	"A:Apple Juice",
	"W:Wood",
	"M:Magma",
	"P:Paper",
	"&:Enemy",
	"@:You",
	"Thanks for playing!"
};
#pragma endregion
#pragma endregion

//Vector Defination (Declaration)
vector<character>* character::AliveEnemies;

/// <summary>
/// Stores positions for where things are located across the board
/// </summary>
vector<vector<Unit*>> UnitLocations(HEIGHT,vector<Unit*>(WIDTH,nullptr)); //<-- First is the y array and the second is the X array
bool playerIsDead;

/// <summary>
/// Start of Program
/// </summary>
character* start()
{
	generateRandomNumber();
	//Creates new ingrdients
	//BrainRot Potion
	ingredient* brain = new ingredient("Brain", 'B');
	ingredient* appleJuice = new ingredient("AppleJuice", 'A');
	//FirePotion
	ingredient* wood = new ingredient("Wood", 'W');
	ingredient* magma = new ingredient("Magma", 'M');

	//PaperBall 
	ingredient* paper = new ingredient("Paper", 'P');

	//Creates a brainRot potionType with ingredients
	potionType* brainRot = new potionType("BrainRot");
	brainRot->addIngredient(brain);
	brainRot->addIngredient(appleJuice);
	//Creates a Fire potionType with ingredients
	potionType* fire = new potionType("Fire");
	fire->addIngredient(brain);
	fire->addIngredient(appleJuice);
	//Creates a PaperBall potionType with ingredients
	potionType* paperBall = new potionType("PaperBall");
	fire->addIngredient(paper);

	//Creates Player Object
	cout << "Name your player" << endl;
	string playerName;
	std::cin >> playerName;
	character* player = new character(playerName, false);
	player->setPosX(+6);
	player->setPosY(+3);

	return player;

}
int main()
{
	character* player = start();
	///Main loop
	do
	{
		printState(player->getPosX(), player->getPosY());
		//
		bool inputValid = false;
		while (!inputValid)
		{
			int Buttonpress;
			Buttonpress = _getch(); //A built in function to detect the button presses on a keyboard
			Buttonpress = toupper(Buttonpress);

			//Finds what button was pressed
			switch (Buttonpress)
			{
			case 'W':
			inputValid = player->setPosY(-1);
				break;
			case 'A':
			inputValid = player->setPosX(-1);
				break;
			case 'S':
			inputValid = player->setPosY(+1);
				break;
			case 'D':
			inputValid = player->setPosX(+1);
				break;

			default:
				cout << "Invalid Input" << endl;
				break;
			}

		}
		printf("\033[2J\033[1;1H"); //Clears the terminals (Sort of) Reference:https://stackoverflow.com/a/1348624 
		cout << endl;
	} while (!playerIsDead);// No end point rn
	cout << "You have died";
	
	return 0;
}

void printState(int xPosition, int yPosition)
{
	if (!playerIsDead)
	{
		///Creates thread to change enemy location 
		//std::thread t1(changeEnemyLocation);
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int n = 0; n < WIDTH; n++)
			{
			//	t1.join(); //Not working yet
				if (n == xPosition && i == yPosition) //Places down Player coordinates
				{
					cout << '@';
					//Is the player standing on top of an enemy or ingredient
					if (UnitLocations[i][n] != nullptr)
					{
						playerIsDead = UnitLocations[i][n]->getUnit();

						///As the unit class is deleted this will be null
						UnitLocations[i][n] = nullptr;
					}
				}
				else if (UnitLocations[i][n] != nullptr)
				{
					char symbolInSpace = UnitLocations[i][n]->GetSymbolInLocation();
					if (symbolInSpace != ' ')
					{
						cout << symbolInSpace;
					}
				}
				else
				{
					int ranNum = generateRandomNumber();
					switch (ranNum)
					{
					case 0:
						cout << '.';
						break;
					case 1:
						//Spawns ingredient
					{
						ingredient* newIngredient = ingredient::outPutRandomIngredient(Random::engine);

						Unit* newIngredientUnit = new Unit(newIngredient);
						UnitLocations[i][n] = newIngredientUnit;
						cout << newIngredient->getSymbol();
					}
					break;
					case 2:
					{
						character* newEnemy = new character("Enemy", true);
						Unit* newEnemyUnit = new Unit(newEnemy);
						UnitLocations[i][n] = newEnemyUnit;
						newEnemy->setPosX(+n);
						newEnemy->setPosY(+i);
						cout << newEnemy->getSymbol();
					}
					break;
					default:
						cout << "Invalid answer" << endl;
						break;
					}
				}

			}
			cout << "	" << Help[i] << endl;

		}
		//Loads game area 

		for (int i = HEIGHT; i < sizeof(Help) / 40; i++)
		{
			cout << "		" << Help[i] << endl;
		}
	}
}


/// <summary>
/// Choose a random number between 0 and 2
/// 0:Spot
/// 1:Ingredient
/// 2:Enemy
/// </summary>

int generateRandomNumber()
{
	std::uniform_int_distribution<int> Randomint(0, 100);
	int RandomIntResult = Randomint(Random::engine);

	if (RandomIntResult < 2) // 2% chance
	{
		return 2; //Enemy
	}
	else if (RandomIntResult < 8) //6% chance
	{
		return 1;
	}
	else
	{
		return 0; //92% chance
	}
	
	
}

void changeEnemyLocation()
{
	//Loops through all the enemies
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int n = 0; n < WIDTH; n++)
		{
			if (UnitLocations[i][n] != nullptr)
			{
				char symbolInSpace = UnitLocations[i][n]->GetSymbolInLocation();
				if (symbolInSpace == '&') // <-- If an enemy
				{
					character* enemy = UnitLocations[i][n]->getEnemy();

					if (enemy->getIsMoved())
					{
						///Random Number generation
						std::uniform_int_distribution<int> RandomInt(-1, 1);
						int RandomPos = RandomInt(Random::engine);
						std::uniform_int_distribution<int> RandomInt2(1, 2); //<-- It'll be in x if 1 or y if 2
						int RandomCoordinate = RandomInt2(Random::engine);

						//Calculates a new position to move
						enemy->setIsMoved(true);
						position* newPos = new position(RandomPos * RandomCoordinate % 2, RandomPos * 1 % RandomCoordinate);
						//cout << newPos->getPosX() << newPos->getPosY() << endl;
						//

						//Moves enemy
						enemy->setPosX(newPos->getPosX());
						enemy->setPosY(newPos->getPosY());

						//Deletes value 
						delete newPos;

						//return newPos;
						UnitLocations[enemy->getPosY()][enemy->getPosX()] = UnitLocations[i][n]; //Sets new enemy position
						UnitLocations[i][n] = nullptr; // <-- Removes enemy in that old spot


					}
					else
					{
						enemy->setIsMoved(false);
					}
				}
			}
			

		}

	}
}
