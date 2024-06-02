#pragma once
#include "Plant.h"
class Sow : public Plant
{
public:
	Sow(World* worldPtr, InfoTeller* info);
	Organism* Baby(World* worldPtr, InfoTeller* info) override;
	void action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info) override;
};

