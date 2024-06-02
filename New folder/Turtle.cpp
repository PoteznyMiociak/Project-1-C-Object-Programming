#include "Turtle.h"
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

Turtle::Turtle(int x, int y, World* worldPtr, InfoTeller* info)
	: Animal(2, 1, 'T',x,y, worldPtr,info)
{}

Organism* Turtle::Baby(World* worldPtr, InfoTeller* info) {
	return new Turtle(-9,-2,worldPtr, info);
}

void Turtle::action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info)
{
	double stay = static_cast<double>(rand()) / (RAND_MAX + 1.0);
	if (stay > 1 / 4)
		return;
	int direction = 0;
	int outcome = 0;
	int horizontal = 0, vertical = 0;
	while (true)
	{
		direction = rand() % 4 + 1;
		if (positionX != 0 && positionX + 1 != sizeX && positionY != 0 && positionY + 1 != sizeY)
			break;
		else if (direction == DOWN && positionX + 1 != sizeX)
			break;
		else if (direction == UP && positionX != 0)
			break;
		else if (direction == LEFT && positionY != 0)
			break;
		else if (direction == RIGHT && positionY + 1 != sizeY)
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