#pragma once
#include "Animal.h"
class Antylope :  public Animal
{
public:
	Antylope(int x, int y, World* worldPtr, InfoTeller* info);
	Organism* Baby(World* worldPtr, InfoTeller* info) override;
	void action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info) override;
};

