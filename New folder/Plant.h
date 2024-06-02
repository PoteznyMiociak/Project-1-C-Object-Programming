#pragma once
#include "Organism.h"
class Plant :public Organism
{
public:
	Plant(int strenght, char symbol, int posX, int posY, World* worldPtr, InfoTeller* info);
	virtual void action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info) override;
	void breeding(int posX, int posY, World& world, InfoTeller& info) override;
};

