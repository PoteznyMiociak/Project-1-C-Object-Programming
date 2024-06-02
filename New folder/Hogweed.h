#pragma once
#include "Plant.h"
class Hogweed : public Plant
{
public:
	Hogweed(World* worldPtr, InfoTeller* info);
	Organism* Baby(World* worldPtr, InfoTeller* info) override;
	virtual void action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info) override;
	void breeding(int posX, int posY, World& world, InfoTeller& info) override;
	void fight(int posX, int posY, World& world, InfoTeller& info) override;
};

