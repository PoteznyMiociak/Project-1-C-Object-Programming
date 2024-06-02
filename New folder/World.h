#pragma once
#include "Organism.h"
#include "InfoTeller.h"
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
class World
{
private:
	char** grid;
	int rows, columns;
	std::vector<Organism*> organisms;
	std::queue<Organism*> waitingOrganisms;
public:
	World(int N,int M);
	void CreateWorld(InfoTeller& info);
	void SaveWorld(const std::string& filename);
	void LoadWorld(const std::string& filename, InfoTeller* info);
	char IsOccupied(int posX, int posY);			//checks what animal/plant/free occupies the cell
	bool CheckIfout(int posX, int posY);			//checks if cell which we check is out of board
	int AvaibleDirections(int x, int y);			//for plants to not ways time finding slot that doesnt exist
	void SetCellToFree(int x, int y,char s);		//for Antylope if she goes back
	void AddOrganism(Organism* organism);
	void AddToWait(Organism* organism);				//function not to mess with loop iteration
	void RemoveOrganism();							// - '' - which removes dead organisms
	void MergeQueue();								//function which adds after a turn new organism that were born, sow
	void SimulateRound(InfoTeller* info);
	int GetOrganismStrength(int posX, int posY) const;
	Organism* FindOrganism(int posX, int posY);

	//Stuff to visual world
	void PrintInformations(InfoTeller info);
	void DrawMap();		
};

