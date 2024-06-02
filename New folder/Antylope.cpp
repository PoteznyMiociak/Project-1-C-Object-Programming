#include "Antylope.h"
#include "World.h"

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

Antylope::Antylope(int x, int y, World* worldPtr, InfoTeller* info)
	: Animal(4, 4, 'A',x,y,worldPtr,info)
{}

Organism* Antylope::Baby(World* worldPtr, InfoTeller* info) {
	return new Antylope(-3,-2,worldPtr, info);
}

void Antylope::action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info)
{
	for (int i=0;i<2;i++)
	{
		if (alive == false)
			break;
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

		if ((outcome == 3 || outcome == 5) && alive == true) {
			SetPosition(positionX + vertical, positionY + horizontal);
			world.SetCellToFree(positionX, positionY, ' ');
			positionX += vertical, positionY += horizontal;
		}
	}

}