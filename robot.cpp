#include "robot.h"


ostream& operator<<(ostream& stream, const Location& lc)
{ 
    stream << "value: ";
    stream << lc.row << " - " << lc.col << endl;
    return stream;
};

Robot::Robot()
{
    where.row = 0;
    where.col = 0;
    steps = 0;
    proom = NULL;
}

Robot::~Robot()
{
    // pass
}

int Robot::get_steps()
{
    return steps;
}

void Robot::set_position(Room *rm, Location loc)
{
    proom = rm;
    where = loc;
    
    proom->set_robot(this);
}

Location Robot::get_location()
{
    return where;
}

void Robot::add_visited()
{
    for (list<Location>::iterator it = to_visit.begin(); it != to_visit.end();)
    {
        if (it->row == where.row and it->col == where.col)
            it = to_visit.erase(it);
        else
            ++it;
    }
    visited.push_back(where);
}

list<Location> Robot::find_route(Location target)
{
    Location start(where), cur;
    list<Location> route;
    
    unordered_map<string, Location> visited_loc;
	queue<Location> q;
	bool route_found(false);
	int dx[] = { -1,0,1,0 };
	int dy[] = { 0,1,0,-1 };
	
	
    q.push(start);
	visited_loc[to_string(start.row) + ":" + to_string(start.col)] = start;
	Location tmp;
	string p;
	
    while (!q.empty() && !route_found)
    {
        cur = q.front();
        q.pop();
		for (int i = 0; i < 4; ++i)
		{
			tmp = Location(cur.row + dx[i], cur.col + dy[i]);
			p = to_string(tmp.row) + ":" + to_string(tmp.col);
			
			if ( find(visited.begin(), visited.end(), tmp) != visited.end()
			    and visited_loc.find(p) == visited_loc.end() )
			{
				visited_loc[p] = cur;
				q.push(tmp);
			}
			if (tmp == target)
			{
				visited_loc[p] = cur;
				route_found = true;
				break;
			}
		}
    }
    
    if (route_found)
		do
		{
			route.push_back(target);
			target = visited_loc[to_string(target.row) + ":" + to_string(target.col)];
		}
		while (target.row != start.row or target.col != start.col);
		
	return route;
}

Location Robot::project_next_move()
{
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    list<Location> dirs;
    Location pos;
    
    for (int i(0); i < 4; i++)
    {
        pos = Location(where.row + dy[i], where.col + dx[i]);
        if (proom->get_floor()[where.row + dy[i]][where.col + dx[i]] != '#' 
            and find(to_visit.begin(), to_visit.end(), pos) == to_visit.end() 
            and find(visited.begin(), visited.end(), pos) == visited.end())
            
            dirs.push_back(pos);
    }
    if (dirs.size() > 0)
    {
        to_visit.insert(to_visit.begin(), ++dirs.begin(), dirs.end());
        return *dirs.begin();
    }
    else
        return Location(0,0);
}

Location Robot::sort_uncleaned()
{
    vector<int> dists;
    int i(0);
    
    for (auto v : to_visit)
        dists.push_back(abs(v.row - where.row) + abs(v.col - where.col));
    size_t idx = min_element(dists.begin(), dists.end()) - dists.begin();
    

    auto it = to_visit.begin();
    while (i++ < idx)
        it = next(it);
    return *it;
}

void Robot::go_clean()
{
    list<Location> route; 
    Location where_to_move;
    
    // очищаем ячейку, где находится робот
    proom->get_floor()[where.row][where.col] = ' ';
    
    // добавляем место в список очищенных
    add_visited();
    proom->shits_out();
    
    where_to_move = project_next_move();
    if (where_to_move.row != 0 and where_to_move.col != 0)
    {
        do_move(where_to_move);
        proom->show_room();
    }
    else if (to_visit.size() > 0)
    {
        route = find_route(sort_uncleaned());
        route.reverse();
        for (auto r : route)
        {
            do_move(r);
            proom->show_room();
        }
        route.clear();
    }
}

void Robot::do_move(Location lc)
{
    where.row = lc.row;
    where.col = lc.col;
    steps += 1;
}