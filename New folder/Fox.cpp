#include "Fox.h"
#include "World.h"

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

Fox::Fox(int x, int y, World* worldPtr, InfoTeller* info)
	: Animal(3, 7, 'F', x,y, worldPtr,info)
{}

Organism* Fox::Baby(World* worldPtr, InfoTeller* info) {
	return new Fox(-8,-10,worldPtr, info);
}

void Fox::action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info)
{
	int myStrenght = GetStrenght();
	int direction = 0, outcome = 0, horizontal = 0, vertical = 0;
	int leftcell = world.GetOrganismStrength(positionX, positionY - 1);
	int rightcell = world.GetOrganismStrength(positionX, positionY + 1);
	int upcell = world.GetOrganismStrength(positionX-1, positionY);
	int downcell = world.GetOrganismStrength(positionX+1, positionY);
	while (true)
	{
		direction = rand() % 4 + 1;
		if (positionX != 0 && positionX + 1 != sizeX && positionY != 0 && positionY + 1 != sizeY)
		{
			if (direction == DOWN && downcell <= myStrenght)
				break;
			else if (direction == UP && upcell <= myStrenght)
				break;
			else if (direction == LEFT && leftcell <= myStrenght)
				break;
			else if (direction == RIGHT && rightcell <= myStrenght)
				break;
		}
		else if (direction == DOWN && positionX + 1 != sizeX && downcell <= myStrenght)
			break;
		else if (direction == UP && positionX != 0 && upcell <= myStrenght)
			break;
		else if (direction == LEFT && positionY != 0 && leftcell <= myStrenght)
			break;
		else if (direction == RIGHT && positionY + 1 != sizeY && rightcell <= myStrenght)
			break;
	}

	if (direction == LEFT) {
		outcome = collision(positionX, positionY - 1, symbol, world, info);
		horizontal -= 1;
	}
	else if (direction == RIGHT) {
		outcome = collision(positionX, positionY + 1, symbol, world, info);
		horizontal += 1;
	}
	else if (direction == DOWN) {
		outcome = collision(positionX + 1, positionY, symbol, world, info);
		vertical += 1;
	}
	else {
		outcome = collision(positionX - 1, positionY, symbol, world, info);
		vertical -= 1;
	}

	if ((outcome == 3 || outcome == 5) && alive == true)
		SetPosition(positionX + vertical, positionY + horizontal);

}