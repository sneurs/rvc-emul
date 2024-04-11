#ifndef ROOM_H_
#define ROOM_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

const int SLP = 100;

class Robot;

class Room
{
	private:
		vector<string> floor;
		int shits;
		Robot *rob;
		
	private:	
		void init_from_file(string name);
		
	public:
		Room(string name);
		~Room();
		
		void set_robot(Robot *_rob);
		void shits_out();
		vector<string> &get_floor();
		void show_room();
		bool is_dirty();
};

#endif