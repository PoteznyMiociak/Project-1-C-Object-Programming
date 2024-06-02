#pragma once
#include "Plant.h"
class Grass : public Plant
{
public:
	Grass(World* worldPtr, InfoTeller* info);
	Organism* Baby(World* worldPtr, InfoTeller* info) override;
};

