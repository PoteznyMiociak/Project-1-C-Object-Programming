#include "Wolf.h"


Wolf::Wolf(int x, int y, World* worldPtr, InfoTeller* info)
	: Animal(9, 5, 'W', x,y,worldPtr,info)			
{}

Organism* Wolf::Baby(World * worldPtr, InfoTeller * info)
{
	return new Wolf(-8,-9, worldPtr, info);
}
