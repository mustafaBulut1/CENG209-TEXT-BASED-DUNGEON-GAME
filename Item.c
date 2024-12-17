#include "Item.h"  // Include the Item header file to access Item structure and related functions

// Function to print the details of an item
void printItem(Item *item){
    // Print the name of the item
    printf("%s", item->name);
    
    // Print the damage value of the item
    printf("damage = %d", item->damage);
    
    // Print the health value associated with the item (if applicable)
    printf("health = %d", item->health);
    
    // Print the durability value of the item
    printf("durability = %d", item->durability);
}
