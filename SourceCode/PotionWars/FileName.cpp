#include <iostream>
#include <map>
#include <string>
#include<list>
#include <random>
#include "Potion.h" //Includes class for all potions
#include "conio.h" //Allows keyboard inputs
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

#pragma endregion
class position
{
protected:
	int x = 6;
	int y = 3;
};
std::default_random_engine engine;
class character : private position
{
private:
	string name;
	int level;
	bool isEnemy; //Returns false if Player
	char icon = '@';
	static std::vector<character>AliveEnemies;
public:
	character(string n, bool isCharPlayer)
	{
		name = n;
		isEnemy = isCharPlayer;
		if (isEnemy)
		{
			icon = '&';
			AliveEnemies.push_back(*this);
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
	int getPosX()
	{
		return x;
	}
	int getPosY()
	{
		return y;
	}
	static int getCountOfEnemy()
	{
		return AliveEnemies.size();
	}

	char getSymbol()
	{
		return icon;
	}
	void setPosX(int n)
	{
		if (x + n >= 0 && x+n < WIDTH)
		{
			x += n;
		}
	}
	void setPosY(int n)
	{
		if (y+n >= 0 && y+n < HEIGHT)
		{
			y += n;
		}
	}


};


int main()
{
	generateRandomNumber();
	//Creates new ingrdients
	//BrainRot Potion
	ingredient* brain = new ingredient("Brain",'B');
	ingredient* appleJuice = new ingredient("AppleJuice",'A');
	//FirePotion
	ingredient* wood = new ingredient("Wood",'W');
	ingredient* magma = new ingredient("Magma",'M');
	
	//PaperBall 
	ingredient* paper = new ingredient("Paper",'P');
	
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
	character* player = new character(playerName, true);
	
	do
	{
		printState(player->getPosX(), player->getPosY());
		int Buttonpress;
		Buttonpress = _getch(); //A built in function to detect the button presses on a keyboard
		Buttonpress = toupper(Buttonpress);

		//Finds what button was pressed
		switch (Buttonpress)
		{
		case 'W':
			player->setPosY(-1);
			break;
		case 'A':
			player->setPosX(-1);
			break;
		case 'S':
			player->setPosY(+1);
			break;
		case 'D':
			player->setPosX(+1);
			break;

		default:
			cout << "Invalid Input" << endl;
			break;
		}
		printf("\033[2J\033[1;1H"); //Clears the terminals (Sort of) Reference:https://stackoverflow.com/a/1348624 
		cout << endl;
	} while (true);// No end point rn
	
	
	return 0;
}

void printState(int xPosition, int yPosition)
{
	
	//Loads game area 
	for (int i = 0; i < HEIGHT;  i++)
	{
		for (int n = 0; n < WIDTH;  n++) 
		{
			if (n == xPosition && i == yPosition) //Places down Player coordinates
			{
				cout << '@';
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
							ingredient* a = new ingredient();
							cout << a->outPutRandomIngredient(engine).getSymbol();
							delete a;
						}
						break;
					case 2:
						{
							character* newEnemy = new character("Enemy", false);
							cout << newEnemy->getSymbol();
						}
						break;

					default:
						cout << "Invalid answer" << endl;
						break;
				}
			}
		}
		cout << endl;
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
	int RandomIntResult = Randomint(engine);

	if (RandomIntResult < 10) // 10% chance
	{
		return 2; //Enemy
	}
	else if (RandomIntResult < 30) //20 Percent chance
	{
		return 1;
	}
	else
	{
		return 0; //70 Percent chance
	}
	
	
}
