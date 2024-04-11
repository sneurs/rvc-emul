#include "robot.h"

const string ROOM_FILE_NAME = "room.txt";
const Location lc(1, 1);

int main()
{
    Room *dirty_room = new Room(ROOM_FILE_NAME);
    Robot *super_robot = new Robot();
    
    super_robot->set_position(dirty_room, lc);
    dirty_room->show_room();
    
    while (dirty_room->is_dirty())
    {
        super_robot->go_clean();
        dirty_room->show_room();
    }
    
    cout << "Пылесошенье завершено. Количество шагов: " << super_robot->get_steps();
    
    delete dirty_room;
    delete super_robot;
}
