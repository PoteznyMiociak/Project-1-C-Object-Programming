#pragma once
#include "Animal.h"
class Human : public Animal
{
protected:
	int duration = 0;
public:
	Human(World* worldPtr, InfoTeller* info);
	void action(int positionX, int positionY, int sizeX, int sizeY, char symbol, World& world, InfoTeller& info) override;
	Organism* Baby(World* worldPtr, InfoTeller* info) override;
	void ActiveAbility();		
	bool IsOnCooldown();
	void LowerDuration();
	void SetDuration(int time);		//this two guys are only used in loading and saving map
	int GetDuration();
};

