#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "Room.h"
#include "Creature.h"

#define MAX_INVENTORY 10  // Define maximum number of items in the player's inventory

// Define the Player structure
typedef struct Player {
    int health;                // Player's health points
    int damage;                // Player's damage output
    Item *inventory[MAX_INVENTORY]; // Array to hold player's inventory items
    int numberOfItems;         // Tracks the number of items in the player's inventory
} Player;

// Function declarations:
void useItem(Player *player , Item *item);   // Function to use an item from the inventory
void attack(Player *player , Room *room);    // Function to attack creatures or objects in the room
void discard(Player *player, const char *itemName, Room *currentRoom); // Function to discard an item
void inventory(Player *player);               // Function to display the player's inventory
void move(Player *player , Room **current_room , const char *direction); // Function to move the player in a direction
void pickup(Player *player, Room *room, const char *itemName);  // Function to pick up an item from the room
void showStatus(Player *player);              // Function to display the player's current status

extern Player player;  // Declare an external variable for the player

#include "Player.c"  // Include the implementation of the functions in Player.c
#endif

