#include "Sheep.h"


Sheep::Sheep(int x, int y, World* worldPtr, InfoTeller* info)
    : Animal(4, 4, 'S', x, y, worldPtr, info)
{}

Organism* Sheep::Baby(World* worldPtr, InfoTeller* info)
{
    return new Sheep(-4,-8,worldPtr,info);
}
