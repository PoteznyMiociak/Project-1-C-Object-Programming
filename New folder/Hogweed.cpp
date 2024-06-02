#include "Hogweed.h"
#include "World.h"
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4


Hogweed::Hogweed(World* worldPtr, InfoTeller* info)
	: Plant(0, 'h', 0, 5, worldPtr, info)
{}

Organism* Hogweed::Baby(World* worldPtr, InfoTeller* info)
{
	return new Hogweed(worldPtr, info);
}


void Hogweed::fight(int posX, int posY, World& world, InfoTeller& info)
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
				continue;
			if (world.CheckIfout(posX + i, posY + j) == false && world.IsOccupied(posX + i, posY + j) != ' ' && world.IsOccupied(posX + i, posY + j) != 'h') {
				Organism* unlucky = world.FindOrganism(posX + i, posY + j);
				char type = unlucky->GetType();
				if (type == 'A'){
					unlucky->SetToDead();
					world.SetCellToFree(posX + i, posY + j, ' ');
					char symbol = unlucky->GetSymbol();
					info.AddToMessages('h', symbol, 'F');
				}
			}
		}
	}

}

void Hogweed::breeding(int posX, int posY, World& world, InfoTeller& info)
{
	char symbol = GetSymbol();
	Organism* baby = Baby(&world, &info);
	baby->SetPosition(posX, posY);
	world.AddToWait(baby);
	info.AddToMessages(symbol, ' ', 'S');
	fight(posX, posY, world, info);
}


void Hogweed::action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info)
{
	fight(positionX, positionY, world, info);
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
			move = true;
		else if (direction == UP && world.IsOccupied(positionX - 1, positionY) == ' ')
			move = true;
		else if (direction == LEFT && world.IsOccupied(positionX, positionY - 1) == ' ')
			move = true;
		else if (direction == RIGHT && world.IsOccupied(positionX, positionY + 1) == ' ')
			move = true;
	}
	else if (direction == DOWN && positionX + 1 != sizeX && world.IsOccupied(positionX + 1, positionY) == ' ')
		move = true;
	else if (direction == UP && positionX != 0 && world.IsOccupied(positionX - 1, positionY) == ' ')
		move = true;
	else if (direction == LEFT && positionY != 0 && world.IsOccupied(positionX, positionY - 1) == ' ')
		move = true;
	else if (direction == RIGHT && positionY + 1 != sizeY && world.IsOccupied(positionX, positionY + 1) == ' ')
		move = true;

	if (move == true) {
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