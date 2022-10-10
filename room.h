#ifndef ROOM_H
#define ROOM_H

#include "items.h"
#define MAX_CHARACTER 5

//given structure of Room
struct Room
{
      char *name;
      struct Room *North;
      struct Room *South;
      struct Room *East;
      struct Room *West;
      struct Item *itemList;
      char *character[MAX_CHARACTER];
};

//declaration of the 3x3 room array with the element defined as the room pointer
extern struct Room *rmArr[3][3];
//declaration of the room instance
extern struct Room realRoom[9];

//initializes and generates room data
void generateRooms();
#endif // ROOM_H
