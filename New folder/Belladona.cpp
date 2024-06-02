#include "Belladona.h"

Belladona::Belladona(World* worldPtr, InfoTeller* info)
	: Plant(99, 'b', 12, 17, worldPtr, info)
{}

Organism* Belladona::Baby(World* worldPtr, InfoTeller* info)
{
	return new Belladona(worldPtr, info);
}

