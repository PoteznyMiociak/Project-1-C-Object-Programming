#pragma once
#include "Organism.h"
class Animal : public Organism
{
public:
	Animal(int strenght, int initiative, char symb, int posX, int posY, World* worldPtr, InfoTeller* info);
	void BoostStrenght();
};

