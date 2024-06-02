#include "Plant.h"
#include "World.h"
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4


Plant::Plant(int strenght, char symb, int posX, int posY, World* worldPtr, InfoTeller* info)
	: Organism(strenght, 0, symb, posX,posY, worldPtr,'P',info)
{}

void Plant::breeding(int posX, int posY, World& world, InfoTeller& info)
{
	char symbol = GetSymbol();
	Organism* baby = Baby(&world, &info);
	baby->SetPosition(posX, posY);
	world.AddToWait(baby);
	info.AddToMessages(symbol, ' ', 'S');
}


void Plant::action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World & world, InfoTeller & info)
{
	int avaibleDir = world.AvaibleDirections(positionX, positionY);
	if (avaibleDir == 0)
		return;
	int direction = 0;
	int outcome = 0;
	int horizontal = 0, vertical = 0;
	bool move = false;
	direction = rand() % 4 + 1;
	if (positionX != 0 && positionX + 1 != sizeX && positionY != 0 && positionY + 1 != sizeY)
	{
		if (direction == DOWN && world.IsOccupied(positionX + 1, positionY) == ' ')
			move=true;
		else if (direction == UP && world.IsOccupied(positionX - 1, positionY) == ' ')
			move=true;
		else if (direction == LEFT && world.IsOccupied(positionX, positionY - 1) == ' ')
			move=true;
		else if (direction == RIGHT && world.IsOccupied(positionX, positionY + 1) == ' ')
			move=true;
	}
	else if (direction == DOWN && positionX + 1 != sizeX && world.IsOccupied(positionX + 1, positionY) == ' ')
		move=true;
	else if (direction == UP && positionX != 0 && world.IsOccupied(positionX - 1, positionY) == ' ')
		move=true;
	else if (direction == LEFT && positionY != 0 && world.IsOccupied(positionX, positionY - 1) == ' ')
		move=true;
	else if (direction == RIGHT && positionY + 1 != sizeY && world.IsOccupied(positionX, positionY + 1) == ' ')
		move=true;

	if(move==true){
		if (direction == LEFT)
			horizontal -= 1;
		else if (direction == RIGHT)
			horizontal += 1;
		else if (direction == DOWN)
			vertical += 1;
		else
			vertical -= 1;

		breeding(positionX + vertical, positionY + horizontal, world, info);
	}
	move = false;
}
