#pragma once
#include "Animal.h"
class Wolf : public Animal
{
public:
	Wolf(int x,int y, World* worldPtr, InfoTeller* info);
	Organism* Baby(World* worldPtr, InfoTeller* info) override;
};

