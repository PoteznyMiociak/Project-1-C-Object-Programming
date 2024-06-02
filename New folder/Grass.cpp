#include "Grass.h"

Grass::Grass(World* worldPtr, InfoTeller* info)
	: Plant(0, 'g',0,0, worldPtr, info)
{}

Organism* Grass::Baby(World * worldPtr, InfoTeller * info)
{
	return new Grass(worldPtr,info);
}
