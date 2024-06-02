#include "Human.h"
#include <conio.h>
#include <iostream>

#define ALIVE true
#define DEAD false

Human::Human(World* worldPtr, InfoTeller* info)
	: Animal(5, 4, 'H', 2,6, worldPtr, info)
{}


void Human::ActiveAbility()
{
	duration =15;
	strenght += 10;
}


void Human::LowerDuration()
{
	if (duration >0)
	{
		duration--;
	}
	if (duration > 6)
		strenght--;
}

void Human::SetDuration(int time)
{
	duration = time;
}

int Human::GetDuration()
{
	return duration;
}

bool Human::IsOnCooldown()
{
	if (duration == 0)
		return false;
	else
		return true;
}


void Human::action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info)
{
	int outcome;
	char dir = ' ';
	int horizontal = 0, vertical = 0;
	std::cout << "Press w,a,s,d to walk or f to use superAbility" << std::endl;
	while (true)
	{
		dir = _getch();
		if (dir == 'f')
		{
			if (IsOnCooldown() == false) {
				ActiveAbility();
				info.AddToMessages('H', ' ', 's');
			}
			else
				std::cout << "You can't use ability now. It is active or on cooldown";
			continue;
			
		}
		if (dir != 's' && dir != 'w' && dir != 'a' && dir != 'd')
			continue;
		if (positionX != 0 && positionX + 1 != sizeX && positionY != 0 && positionY + 1 != sizeY)
			break;
		else if (dir == 's' && positionX + 1 != sizeX)
			break;
		else if (dir == 'w' && positionX != 0)
			break;
		else if (dir == 'a' && positionY != 0)
			break;
		else if (dir == 'd' && positionY + 1 != sizeY)
			break;
		
	}
	if (dir == 'a') {
		outcome = collision(positionX , positionY-1, symbol, world, info);
		horizontal -= 1;
	}
	else if (dir == 'd') {
		outcome = collision(positionX, positionY+1, symbol, world,info);
		horizontal += 1;
	}
	else if (dir == 's') {
		outcome = collision(positionX+1, positionY, symbol, world,info);
		vertical += 1;
	}
	else {
		outcome = collision(positionX-1, positionY, symbol, world,info);
		vertical -= 1;
	}

	if ((outcome == 3 || outcome == 5) && alive==true)
		SetPosition(positionX + vertical, positionY + horizontal);
	if (IsOnCooldown() == true)
		LowerDuration();
	else
		info.AddToMessages(' ', ' ', 'c');
}

Organism* Human::Baby(World* worldPtr, InfoTeller* info)
{
	return nullptr;
}
