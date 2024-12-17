#ifndef CREATURE_H
#define CREATURE_H


#include "Item.h"
#include "Room.h"
#include "Player.h"


// Define the Creature structure
typedef struct Creature {
    char *name;     // Name of the creature (e.g., "Goblin", "Dragon")
    int health;     // Health points of the creature
    int damage;     // Damage output of the creature
} Creature;        // End of Creature structure definition


#include "Creature.c"
#endif

