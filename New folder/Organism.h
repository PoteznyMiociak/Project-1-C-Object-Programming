#pragma once
#include "InfoTeller.h"
class World;

class Organism
{
protected:
	World& world;
	InfoTeller& info;
	int strenght;
	int initiative;
	int positionX;
	int positionY;
	bool alive = true;
	bool moved = false;
	int age = 1;
	char type;
	char symbol;
public:
	Organism() = default;
	Organism(int strenght, int initiative, char symb, int posX, int posY, World* worldPtr, char type, InfoTeller* info);

	//get stuff for world
	int GetPositionX();
	int GetPositionY();
	int GetStrenght();
	char GetSymbol();
	int GetInitiative();
	bool GetMove();
	int GetAge();
	char GetType();
	bool CheckIfAlive();

	//set stuff for us
	void SetPosition(int x, int y);
	void SetToDead();
	void SetAge(int age);
	void SetStrenght(int s);
	void ChangeMoved(bool move);
	void IncreaseAge();

	virtual void action(int positionX, int positionY, int sizeX, int sizeY,char symbol, World& world, InfoTeller& info);
	virtual int collision(int posX2, int posY2,char symbol, World& world, InfoTeller& info);
	void findFreeCellAndSetPos(int posX, int posY, World& world, Organism& creature);
	virtual void fight(int posX, int posY, World& world, InfoTeller& info);
	virtual Organism* Baby(World* worldPtr, InfoTeller* info) = 0;
	virtual void breeding(int posX, int posY, World& world, InfoTeller& info);
	virtual ~Organism() {};
};

