#pragma once
#include "Animal.h"
class Fox : public Animal
{
public:
	Fox(int x, int y, World* worldPtr, InfoTeller* info);
	void action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info) override;
	Organism* Baby(World* worldPtr, InfoTeller* info) override;
};

