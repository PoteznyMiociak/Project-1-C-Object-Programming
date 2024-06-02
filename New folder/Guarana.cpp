#include "Guarana.h"

Guarana::Guarana(World* worldPtr, InfoTeller* info)
	: Plant(0, 'u', 20, 6, worldPtr, info)
{}

Organism* Guarana::Baby(World* worldPtr, InfoTeller* info)
{
	return new Guarana(worldPtr, info);
}