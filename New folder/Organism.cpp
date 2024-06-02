#include "Organism.h"
#include "Animal.h"
#include "World.h"
using namespace std;

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

#define SAMESPECIE 0
#define ANIMAL 1
#define PLANT 2
#define FREESPACE 3


Organism::Organism(int strenght, int initiative,char symb, int x, int y,World* world, char type, InfoTeller* info)
	: strenght(strenght), initiative(initiative), symbol(symb), world(*world), positionX(x), positionY(y), type(type), info(*info)
{}

char Organism::GetSymbol(){
	return symbol;
}

int Organism::GetPositionX(){
	return positionX;
}

int Organism::GetPositionY(){
	return positionY;
}

int Organism::GetAge(){
	return age;
}

int Organism::GetInitiative() {
	return initiative;
}

bool Organism::GetMove()
{
	if (moved == true)
		return true;
	else
		return false;
}

char Organism::GetType() {
	return type;
}

int Organism::GetStrenght() {
	return strenght;
}

void Organism::IncreaseAge()
{
	age++;
}

void Organism::SetToDead() {
	alive = false;
}

void Organism::SetAge(int age)
{
	age = age;
}

void Organism::SetStrenght(int s)
{
	strenght = s;
}

void Organism::ChangeMoved(bool move)
{
	if (move == true)
		moved = false;
	else
		moved = true;
}

bool Organism::CheckIfAlive()
{
	if (alive == true)
		return true;
	else
		return false;
}

void Organism::findFreeCellAndSetPos(int posX, int posY, World& world, Organism& creature)
{

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
				continue;
			if (world.CheckIfout(posX+i,posY+j)==false&& world.IsOccupied(posX + i, posY + 1) == ' '){
				creature.SetPosition(posX + i, posY + j);
				return;
			}
		}
	}
}

void Organism::fight(int posX, int posY, World& world,InfoTeller& info){
	
	//opponent data
	Organism* deffender1 = world.FindOrganism(posX, posY);
	int opponentStrenght = deffender1->GetStrenght();
	char def_symbol = deffender1->GetSymbol();

	//my data
	int strenght = GetStrenght();
	int myX = GetPositionX(), myY = GetPositionY();
	char symbol = GetSymbol();

	if (def_symbol == 'T' && strenght < 5)
		return;
	else if (def_symbol == 'A') {
		double randomValue = static_cast<double>(rand()) / (RAND_MAX + 1.0);
		if (randomValue > 0.5){
			info.AddToMessages('A', ' ', 'E');
			findFreeCellAndSetPos(posX, posY, world, *deffender1);
			return;
		}
	}
	if (def_symbol == 'u'){		//for guarana
		Animal* animalPtr = dynamic_cast<Animal*>(this);
		animalPtr->BoostStrenght();
	}
	char type = deffender1->GetType();
	if (strenght > opponentStrenght || strenght == opponentStrenght)
	{
		deffender1->SetToDead();
		if (type == 'A')
			info.AddToMessages(symbol, def_symbol, 'F');
		else
			info.AddToMessages(symbol, def_symbol, 'e');
	}
	else
	{
		info.AddToMessages(def_symbol, symbol, 'F');
		SetToDead();
	}
}

void Organism::breeding(int posX, int posY, World& world, InfoTeller& info)
{
	char symbol = GetSymbol();
	Organism* baby = Baby(&world, &info);
	findFreeCellAndSetPos(posX, posY, world, *baby);
	Organism* parent = world.FindOrganism(posX, posY);
	parent->ChangeMoved(false);
	world.AddToWait(baby);
	info.AddToMessages(symbol, ' ', 'B');
}


int Organism::collision(int posX, int posY, char symbol, World& world, InfoTeller& info)
{
	char deffender = world.IsOccupied(posX, posY);
	if (deffender == ' ')
		return FREESPACE;
	else if (symbol == deffender)		
	{
		breeding(posX, posY, world, info);
		return SAMESPECIE;
	}
	else
		fight(posX, posY, world,info);
	return 5;
}


void Organism::SetPosition(int x, int y) {
	positionX = x;
	positionY = y;
}

void Organism::action(int positionX, int positionY, int sizeX, int sizeY,char symbol, World& world, InfoTeller& info)
{
	int direction = 0;
	int outcome = 0;
	int horizontal = 0, vertical = 0;
	while(true)
	{
		direction = rand() % 4 + 1;
		if (positionX != 0 && positionX + 1 != sizeX && positionY != 0 && positionY + 1 != sizeY)
			break;
		else if (direction == DOWN && positionX + 1 != sizeX)
			break;
		else if (direction == UP && positionX != 0)
			break;
		else if (direction == LEFT && positionY != 0)
			break;
		else if (direction == RIGHT && positionY + 1 != sizeY)
			break;
	}

	if (direction == LEFT){
		outcome = collision(positionX, positionY - 1, symbol, world, info);
		horizontal -= 1;
	}
	else if( direction == RIGHT){
		outcome = collision(positionX, positionY + 1, symbol, world, info);
		horizontal += 1;
	}
	else if (direction == DOWN){
		outcome = collision(positionX + 1, positionY, symbol, world,info);
		vertical += 1;
	}
	else{
		outcome = collision(positionX - 1, positionY, symbol, world,info);
		vertical -= 1;
	}

	if ((outcome == FREESPACE || outcome==5) && alive==true)
		SetPosition(positionX + vertical, positionY + horizontal);

}