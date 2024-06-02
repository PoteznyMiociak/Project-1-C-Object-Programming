#pragma once
#include "Plant.h"
class Belladona : public Plant
{
public:
	Belladona(World* worldPtr, InfoTeller* info);
	Organism* Baby(World* worldPtr, InfoTeller* info) override;
};

