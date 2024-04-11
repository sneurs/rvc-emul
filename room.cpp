#include "room.h"
#include "robot.h"

Room::Room(string name)
{
    init_from_file(name);
    shits = -1;
}

Room::~Room()
{
    // pass
}

void Room::init_from_file(string name)
{   
    string line;
	ifstream fl(name);
    if (fl.is_open())
        while (getline(fl, line))
            floor.push_back(line);
    fl.close();
}

void Room::set_robot(Robot *_rob)
{
    rob = _rob;
}


// переписать.. shits - не правильно рабоет. 
bool Room::is_dirty()
{
    // в первый раз считаем ввсю грязь
    if (shits == -1)   
        for (auto row : floor)
            for (auto col : row)
                if (col == '.')
                    shits +=1;        
    if (shits > 0)
        return true;
    else
        return false;
}

void Room::shits_out()
{
    shits -=1;
}

void Room::show_room()
{
    system("cls");
    Location lc = rob->get_location();
    char simb = floor[lc.row][lc.col];
    floor[lc.row][lc.col] = '@';
    
    for (auto v : floor)
        cout << v << endl;
        
    floor[lc.row][lc.col] = simb;
    
    this_thread::sleep_for(chrono::milliseconds(SLP));
}

vector<string> &Room::get_floor()
{
    return floor;
}