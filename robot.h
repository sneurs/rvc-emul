#ifndef ROBOT_H_
#define ROBOT_H_

#include <string>
#include <list>
#include <unordered_map>
#include <queue>
#include "room.h"

class Location
{
public:
    int row;
	int col;
	Location(int _r, int _c) { row = _r; col = _c; };
	Location() { row = 0; col = 0; };
	bool operator == (const Location& lc) const { return col == lc.col and row == lc.row; };
	bool operator != (const Location& lc) const { return col != lc.col or row != lc.row; };
};

// Для отладки, потом удалить
ostream& operator<<(ostream& stream, const Location& lc);

class Robot
{
	private:
	    Location where;
	    int steps;
	    Room *proom;
		list<Location> to_visit;
		list<Location> visited;
        
        void add_visited();
		Location project_next_move();
		void do_move(Location lc);
		Location sort_uncleaned();
		list<Location> find_route(Location target);
		
	public:
		Robot();
		~Robot();
		
		void set_position(Room *rm, Location loc);
		void go_clean();
		int get_steps();
		Location get_location();
};

#endif