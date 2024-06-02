#pragma once
#include "Plant.h"
class Guarana :public Plant
{
public:
	Guarana(World* worldPtr, InfoTeller* info);
	Organism* Baby(World* worldPtr, InfoTeller* info) override;
};

