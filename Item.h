#ifndef ITEM_H
#define ITEM_H
#include <stdbool.h>



struct Room;  // Forward declaration
struct Creature; // Forward declaration
struct Player; // Forward declaration



// Define the Item structure
typedef struct Item {
    char *name;           // Name of the item (e.g., "Sword", "Health Potion")
    int damage;           // Damage value associated with the item (if applicable, e.g., for weapons)
    int health;           // Health value associated with the item (e.g., for healing items)
    int durability;       // Durability value (e.g., how many uses or hits an item can endure)
    bool isUsing;         // Flag indicating whether the item is currently being used
} Item;

// Function declaration to print the details of an item
void printItem(Item *item);

//#include "Item.c"
#endif
