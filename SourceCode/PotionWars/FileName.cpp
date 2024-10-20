#include <iostream>
#include <map>
#include <string>
#include<list>
#include "Potion.h" //Includes class for all potions
#include "conio.h" //Allows keyboard inputs
#define HEIGHT  6
#define WIDTH 8

using std::cout;
using std::string;
using std::list;
using std::endl;

#pragma region Function Definations
void printState(int xPosition, int yPosition);
#pragma endregion
class position
{
protected:
	int x = 6;
	int y = 3;
};

class character : private position
{
private:
	string name;
	int level;
public:
	character(string n)
	{
		name = n;
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
	//Creates new ingrdients
	ingredient* apple = new ingredient("Apple");
	ingredient* pear = new ingredient("Pear");
	ingredient* fire = new ingredient("Fire");

	//Creates a water breathing potionType with ingredients
	potionType* WaterBreathing = new potionType("Water");
	WaterBreathing->addIngredient(apple);
	WaterBreathing->addIngredient(pear);
	WaterBreathing->addIngredient(fire);

	//Creates Player Object
	cout << "Name your player" << endl;
	string playerName;
	std::cin >> playerName;
	character* player = new character(playerName);
	
	do
	{
		printState(player->getPosX(), player->getPosY());
		int Buttonpress;
		Buttonpress = _getch();
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
				cout << '.';
			}
		}
		cout << endl;
	}
}
