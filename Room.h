#ifndef ROOM_H
#define ROOM_H
// Include necessary header files for Item, Creature, and Player structures
#include "Item.h"
#include "Creature.h"
#include "Player.h"

// Define the maximum number of items a room can hold
#define MAX_INVENTORY 10

typedef struct Room {
    char *description;                  // Description of the room
    Item *item[MAX_INVENTORY];          // Array of pointers to items in the room
    int numberOfItems;                  // Current number of items in the room
    Creature *creature;                 // Pointer to a creature in the room
    struct Room *up;                    // Pointer to the room above
    struct Room *down;                  // Pointer to the room below
    struct Room *right;                 // Pointer to the room to the right
    struct Room *left;                  // Pointer to the room to the left
} Room;

// Function prototypes for Room operations
Room *createRoom(const char *description,Item *item, Creature *creature);
void set_connection(Room *room , Room *connected_room, const char *direction);
void free_room(Room *room);
void look (Room *room);

// Include the Room.c implementation file
#include "Room.c"
#endif 

