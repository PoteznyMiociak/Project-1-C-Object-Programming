#include "World.h"
#include "Organism.h"
#include <string>
#include <iostream>
#include <algorithm>

#include "Organism.h"
#include "Animal.h"
#include "Wolf.h"
#include "Antylope.h"
#include "Human.h"
#include "Fox.h"
#include "Turtle.h"
#include "Sheep.h"

#include "Plant.h"
#include "Grass.h"
#include "Guarana.h"
#include "Sow.h"
#include "Belladona.h"
#include "Hogweed.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread> // Include this for std::this_thread::sleep_for
#include <chrono> // Include this for std::chrono::seconds
using namespace std;

World::World(int N, int M)
{
    rows = N;
    columns = M;
    grid = new char* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new char[columns];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            grid[i][j] = ' ';
        }
    }
}

void World::CreateWorld(InfoTeller& info)
{
    
    Organism* fox1 = new Fox(2, 16, this, &info);
    AddOrganism(fox1);
    Organism* fox2 = new Fox(8, 13, this, &info);
    AddOrganism(fox2);

    Organism* wolf = new Wolf(14, 7, this, &info);
    AddOrganism(wolf);
    Organism* wolf2 = new Wolf(14, 8, this, &info);
    AddOrganism(wolf2);

    Organism* antylope = new Antylope(16,12,this, &info);
    AddOrganism(antylope);
    Organism* antylope2 = new Antylope(10,10,this, &info);
    AddOrganism(antylope2);

    Organism* human = new Human(this, &info);
    AddOrganism(human);

    Organism* sheep = new Sheep(1,2,this, &info);
    AddOrganism(sheep);
    Organism* sheep1 = new Sheep(10,2,this, &info);
    AddOrganism(sheep1);

    Organism* turtle = new Turtle(9,3,this, &info);
    AddOrganism(turtle);
    Organism* turtle1 = new Turtle(17,8,this, &info);
    AddOrganism(turtle1);

    Organism* grass = new Grass(this, &info);
    AddOrganism(grass);

    Organism* sow = new Sow(this, &info);
    AddOrganism(sow);
    
    Organism* hogweed = new Hogweed(this, &info); 
    AddOrganism(hogweed);

    Organism* belladona = new Belladona(this, &info);
    AddOrganism(belladona);

    Organism* guarana = new Guarana(this, &info);
    AddOrganism(guarana);       

}


void World::SaveWorld(const string & filename)
{
    ofstream file(filename, ios::trunc);
    if (file.is_open()) {
        for (const auto& org : organisms) {
            file << org->GetStrenght() << '\n' << org->GetInitiative() << '\n'
                << org->GetSymbol() << '\n' << org->GetPositionX() << '\n'
                << org->GetPositionY() << '\n' << org->GetAge() << endl;
            if (org->GetSymbol() == 'H')
            {
                Human* humanPtr = dynamic_cast<Human*>(org);
                file << humanPtr->GetDuration() << endl;
            }
        }
        cout << "Organisms saved to file: " << filename << endl;
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

void World::AddOrganism(Organism* organism)
{
    int x = organism->GetPositionX();
    int y = organism->GetPositionY();
    if (x >= 0 && x < columns && y >= 0 && y < rows) {
        grid[x][y] = organism->GetSymbol();
        organisms.push_back(organism);

    }
}

void World::LoadWorld(const std::string & filename, InfoTeller * info)
{
    std::ifstream file(filename);
    if (file.is_open()) {
        string a = " ";
        int strenght, initiative, positionX, positionY, age, duration = 0;
        char symbol;
        while (getline(file, a)) {
            strenght = stoi(a);
            getline(file, a);
            initiative = stoi(a);
            getline(file, a);
            symbol = a[0];
            getline(file, a);
            positionX = stoi(a);
            getline(file, a);
            positionY = stoi(a);
            getline(file, a);
            age = stoi(a);

            Organism* add = nullptr;
            if (symbol == 'H')    
            {
                add = new Human(this, info);
                add->SetPosition(positionX, positionY);
                getline(file, a);
                duration = stoi(a);
                Human* humanPtr = dynamic_cast<Human*>(add);
                humanPtr->SetDuration(duration);
            }
            else if(symbol=='W')
                add = new Wolf(positionX,positionY,this, info);
            else if (symbol == 'S')
                add = new Sheep(positionX, positionY, this, info);
            else if (symbol == 'F')
                add = new Fox(positionX, positionY, this, info);
            else if (symbol == 'A')
                add = new Antylope(positionX, positionY, this, info);
            else if (symbol == 'T')
                add = new Turtle(positionX, positionY, this, info);
            else if (symbol == 'b')
                add = new Belladona( this, info);
            else if (symbol == 'u')
                add = new Guarana(this, info);
            else if (symbol == 'g')
                add = new Grass(this, info);
            else if (symbol == 'h')
                add = new Hogweed(this, info);
            else if (symbol == 's')
                add = new Sow(this, info);
            add->SetAge(age);
            add->SetStrenght(strenght);
            grid[positionX][positionY] = symbol;
            organisms.push_back(add);
        }
        std::cout << "Organisms loaded from file: " << filename << std::endl;
    }
}


void World::DrawMap()
{
    cout << "\033[2J\033[H";
    cout << "Klaudia Aleksiejew 197731" << endl;
    for (int i = 0; i < columns; i++)
    {
        if (i < 9)
            cout << "  " << i + 1 << " ";
        else
            cout << " " << i + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout <<"| " << grid[i][j] << " ";
        }
        cout << "|" << endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int World::GetOrganismStrength(int posX, int posY) const {
    int x, y, index = 0;
    for (auto organism : organisms)
    {
        x = organism->GetPositionX();
        y = organism->GetPositionY();
        if (x == posX && y == posY)
        {
           Organism* organism = organisms[index];
           if (organism)
                return organism->GetStrenght();
        }
        index++;
    }
    return 0;
}


void World::AddToWait(Organism* organism)
{
    waitingOrganisms.push(organism);
    int x = organism->GetPositionX(), y = organism->GetPositionY();
    grid[x][y] = organism->GetSymbol();
}

void World::RemoveOrganism()
{
    //count the amount of dead animals
    int licznik_dead = 0;
    bool status;
    for (auto organism : organisms)
    {
        status = organism->CheckIfAlive();
        if (status == false)
            licznik_dead++;
    }
    //go in while loop until none of them are still in vector
    while (licznik_dead != 0)
    {
        for (auto it = organisms.begin(); it != organisms.end();)
        {
            auto organism = *it;
            status = organism->CheckIfAlive();
            if (status == false)
            {
                organisms.erase(it);
                licznik_dead--;
                break;
            }
            ++it;
        }
    }
}

void World::MergeQueue()
{
    int myInitiative = 0, inLoopInitiative = 0, x = 0, y = 0;
    bool alive;
    while (!waitingOrganisms.empty())
    {
        Organism* add = waitingOrganisms.front();
        waitingOrganisms.pop();
        alive = add->CheckIfAlive();
        if (alive == false)
        {
            add = nullptr;
            continue;
        }
        myInitiative = add->GetInitiative();
        x = add->GetPositionX();
        y = add->GetPositionY();
        for (auto it = organisms.begin(); it != organisms.end();)
        {
            auto organism = *it;
            inLoopInitiative = organism->GetInitiative();
            if (myInitiative > inLoopInitiative)
            {
                it = organisms.insert(it, add);
                grid[x][y] = add->GetSymbol();
                add = nullptr;
                break;
            }
            ++it;
        }
        if (add != nullptr){
            organisms.push_back(add);
            grid[x][y] = add->GetSymbol();
            add = nullptr;
        }
    }
}

Organism* World::FindOrganism(int posX, int posY)
{
    Organism* pomocniczy = nullptr;
    queue<Organism*> pomocnicza;
    int x = 0, y = 0;
    for (auto organism : organisms)
    {
        x = organism->GetPositionX();
        y = organism->GetPositionY();
        if (x == posX && y == posY)
            return organism;
    }
    while (!waitingOrganisms.empty())
    {
        Organism* organism = waitingOrganisms.front();
        waitingOrganisms.pop();
        x = organism->GetPositionX();
        y = organism->GetPositionY();
        if (x == posX && y == posY)
            pomocniczy = organism;
        pomocnicza.push(organism);
    }
    waitingOrganisms.swap(pomocnicza);
    return pomocniczy;
}

void World::PrintInformations(InfoTeller Info){
    std::string info = Info.GetMessage();
    if (info.empty() == true)
        return;
    cout << info;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void World::SimulateRound(InfoTeller* info){
    int i = 0, j = 0, licznik = 0;
    char symbol = ' ';
    for (auto it = organisms.begin(); it != organisms.end();) {
        auto organism = *it;
        if (organism->GetMove() == true)
        {
            organism->ChangeMoved(true);
            ++it;
            continue;
        }
        i = organism->GetPositionX();
        j = organism->GetPositionY();
        symbol = organism->GetSymbol();
        
        if (organism->CheckIfAlive() == false)
        {
            ++it;
            continue;
        }
        grid[i][j] = ' ';
        organism->action(i, j, rows, columns, symbol, *this,*info);   
        if(organism->CheckIfAlive() == true)
        {
            organism->IncreaseAge();
            i = organism->GetPositionX();
            j = organism->GetPositionY();
            grid[i][j] = symbol;
        }
        if (it!=organisms.end())        
            it++;

        
    }
    RemoveOrganism();
    MergeQueue();
}

char World::IsOccupied(int posX, int posY)
{
    return grid[posX][posY];
}

bool World::CheckIfout(int posX, int posY)
{
    if (posX < 0 || posX == rows || posY < 0 || posY == columns)
        return true;
    else
        return false;
}

int World::AvaibleDirections(int x, int y)
{
    int i = 0;
    //DOWN cell
    if (CheckIfout(x + 1, y) == true || IsOccupied(x + 1, y) == ' ')
        i++;
    //UP cell
    if (CheckIfout(x - 1, y) == true || IsOccupied(x - 1, y) == ' ')
        i++;
    //RIGHT cell
    if (CheckIfout(x, y + 1) == true || IsOccupied(x, y + 1) == ' ')
        i++;
    //LEFT cell
    if (CheckIfout(x, y - 1) == true || IsOccupied(x, y - 1) == ' ')
        i++;
    return i;
}

void World::SetCellToFree(int x,int y,char s)
{
    grid[x][y] = s;
}
