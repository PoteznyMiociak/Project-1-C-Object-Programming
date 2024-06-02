#pragma once
#include "Animal.h"
class Sheep :public Animal
{
public:
	Sheep(int x, int y, World* worldPtr, InfoTeller* info);
	Organism* Baby(World* worldPtr, InfoTeller* info) override;
};

