#include "Animal.h"

Animal::Animal(int strenght, int initiative, char symb, int posX, int posY, World* worldPtr, InfoTeller* info)
	: Organism(strenght,initiative,symb,posX,posY, worldPtr,'A',info)
{}

void Animal::BoostStrenght()
{
	strenght += 3;
}


