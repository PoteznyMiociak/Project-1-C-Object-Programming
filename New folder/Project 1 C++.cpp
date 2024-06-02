#include <iostream>
#include <conio.h>
#include "World.h"
#include <cstdlib>
#include <ctime>
using namespace std;

#define FILENAME "MAP.txt"


int main()
{
    srand(time(nullptr));
    World world(25,25);
    InfoTeller info;
    char option;
    cout << "Press n to start a new game or l to load the old board (and enter)";
    cin >> option;
    if (option == 'n')
        world.CreateWorld(info);
    else
        world.LoadWorld(FILENAME, &info);
    world.DrawMap();
    while(true){
        cout << "Press 'z' to save and exit or just press 'space' to continue" << endl;
        option = _getch();
        if (option == 'z')
        {
            world.SaveWorld(FILENAME);
            break;
        }
        world.SimulateRound(&info);
        world.DrawMap();
        world.PrintInformations(info);
        info.ClearMessages();
        
    }
}
