#include "Player.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void move(Player *player, Room **currentRoom, const char *direction) {
    Room *nextRoom = NULL;
    Room *previousRoom = *currentRoom;  // Save the current room to return if necessary

    // Determine the next room based on direction
    if (strcmp(direction, "up") == 0) {
        nextRoom = (*currentRoom)->up;
    } else if (strcmp(direction, "down") == 0) {
        nextRoom = (*currentRoom)->down;
    } else if (strcmp(direction, "left") == 0) {
        nextRoom = (*currentRoom)->left;
    } else if (strcmp(direction, "right") == 0) {
        nextRoom = (*currentRoom)->right;
    }

    // If there's a creature and it's still alive, return to the current room
    if ((*currentRoom)->creature != NULL && (*currentRoom)->creature->health > 0) {
        printf("There is a creature in this room and it is still alive! You must defeat it before moving on.\n");
        *currentRoom = previousRoom;  // Return to the previous room (same room)
        printf("You are forced to stay in this room until you defeat the creature.\n");
    } else {
        // If no creature or the creature is dead, allow the player to move
        if (nextRoom) {
            printf("You move %s.\n", direction);
            *currentRoom = nextRoom;
            look(*currentRoom);  // Look around in the new room
        } else {
            printf("You can't go that way.\n");
        }
    }
}

// Function to display the player's inventory
void inventory(Player *player) {
    if (player->numberOfItems == 0) {
        printf("Your inventory is empty.\n");
    } else {
        printf("Your inventory: ");
        for (int i = 0; i < player->numberOfItems; i++) {
            printf("%s%s", player->inventory[i]->name, (i == player->numberOfItems - 1) ? "\n" : ", ");
        }
    }
}

// Function to pick up an item from the room
void pickup(Player *player, Room *room, const char *itemName) {
    if (room->creature && room->creature->health > 0) {
        printf("You cannot pick up items while a creature is present or alive.\n");
        return; // Prevent picking up items if a creature is present
    }
    if (room->numberOfItems > 0) { // Check if the room has any items
        for (int i = 0; i < room->numberOfItems; i++) {
            if (strcmp(room->item[i]->name, itemName) == 0) {
                if (player->numberOfItems < MAX_INVENTORY) { // Check if the player's inventory has space
                    player->inventory[player->numberOfItems++] = room->item[i];
                    printf("You picked up the %s.\n", room->item[i]->name);

                    // Shift remaining items in the room to fill the gap
                    for (int j = i + 1; j < room->numberOfItems; j++) {
                        room->item[j - 1] = room->item[j];
                    }
                    room->item[--room->numberOfItems] = NULL; // Reduce room item count and clear last slot
                    return;
                } else {
                    printf("Your inventory is full!\n");
                    return;
                }
            }
        }
        printf("The item '%s' is not in this room.\n", itemName);
    } else {
        printf("There is nothing to pick up here.\n");
    }
}

// Function to discard an item from the player's inventory
void discard(Player *player, const char *itemName, Room *currentRoom) {
    int itemIndex = -1;

    // Find the item in the player's inventory
    for (int i = 0; i < player->numberOfItems; i++) {
        if (strcmp(player->inventory[i]->name, itemName) == 0) {
            itemIndex = i;
            break;
        }
    }

    // If the item is not found
    if (itemIndex == -1) {
        printf("There is no item named '%s' in your inventory.\n", itemName);
        return;
    }

    // Remove the item from the inventory
    player->damage -= player->inventory[itemIndex]->damage;
    printf("You discarded the %s.\n", player->inventory[itemIndex]->name);

    // Add the item to the room if there is space
    if (currentRoom->numberOfItems < 10) { // rooms capacity is 10
        currentRoom->item[currentRoom->numberOfItems] = player->inventory[itemIndex];
        currentRoom->numberOfItems++;
    } else {
        printf("The room is full, the item cannot be discarded here.\n");
    }

    // Shift remaining items in the inventory
    free(player->inventory[itemIndex]);  // Free the memory
    for (int i = itemIndex; i < player->numberOfItems - 1; i++) {
        player->inventory[i] = player->inventory[i + 1];
    }
    player->inventory[--player->numberOfItems] = NULL;  // Clear the last slot
}

// Function to show the player's status
void showStatus(Player *player){
    printf("health = %d \n",player->health);
    printf("damage = %d \n",player->damage);
    inventory(player);

}

// Function to use an item from the inventory
void useItem(Player *player, Item *item) {
    bool itemFound = false;
    int indexOfItem = 0;
    
    // Find the item in the player's inventory
    for (int i = 0; i < player->numberOfItems; i++) {
        if (strcmp(player->inventory[i]->name, item->name) == 0) {
            itemFound = true;
            indexOfItem = i;
            break;
        }
    }
    
    if (!itemFound) {
        printf("There is no item like '%s' in your inventory.\n", item->name);
        return;
    }

    Item *currentItem = player->inventory[indexOfItem];

    // If it's a sword (damage > 0), handle the buffs
    if (currentItem->damage > 0) {
        // Check if there is already a sword being used
        Item *equippedItem = NULL;
        for (int i = 0; i < player->numberOfItems; i++) {
            Item *inventoryItem = player->inventory[i];
            if (inventoryItem->isUsing && inventoryItem->damage > 0) {
                equippedItem = inventoryItem;
                break;
            }
        }

        // If there is an equipped sword, stop using it and remove its buffs
        if (equippedItem && equippedItem != currentItem) {
            equippedItem->isUsing = false;  // Stop using the old sword
            printf("You stop using the %s. Its buffs are removed.\n", equippedItem->name);
            player->damage -= equippedItem->damage; // Remove the old sword's damage buff
        }

        // Mark the current sword as being used
        currentItem->isUsing = true;
        printf("You start using the %s. Its buffs are applied.\n", currentItem->name);
        player->damage += currentItem->damage;  // Add the new sword's damage buff
    } 
    // If it's a potion (health > 0), use it and remove it from inventory
    else if (currentItem->health > 0) {
        if (currentItem->durability > 0) {
            player->health += currentItem->health;
            currentItem->durability -= 1;
            printf("You used the %s and restored %d health.\n", currentItem->name, currentItem->health);

            // If the potion is consumed, remove it from the inventory
            if (currentItem->durability <= 0) {
                printf("The %s is consumed and is now thrown away.\n", currentItem->name);
                for (int i = indexOfItem; i < player->numberOfItems - 1; i++) {
                    player->inventory[i] = player->inventory[i + 1];
                }
                player->inventory[--player->numberOfItems] = NULL;
            }
        }
    } else {
        printf("The %s cannot be used.\n", currentItem->name);
    }
}

// Function to attack a creature in the room
void attack(Player *player, Room *room) {
    if (room->creature) {
        Creature *creature = room->creature;
        
        

        while (creature->health > 0 && player->health > 0) {
            // Check for 10% chance to deal double damage
            int isDoubleDamage = rand() % 9 == 0; //  chance for double damage

            int damageToDeal = isDoubleDamage ? player->damage * 2 : player->damage;

            // Player attacks
            creature->health -= damageToDeal;
            printf("You hit the %s for %d damage%s.\n", creature->name, damageToDeal, isDoubleDamage ? " (Double damage!)" : "");

            if (creature->health > 0) {
                // Creature attacks back 
                player->health -= creature->damage;
                printf("The %s hits you for %d damage.\n", creature->name, creature->damage);
            }
        }

        if (creature->health <= 0) {
            printf("You defeated the %s!\n", creature->name);
            room->creature = NULL; // Remove the creature from the room

            // Add the White Monster Potion to the room
            Item *whiteMonsterPotion = (Item*)malloc(sizeof(Item));
            whiteMonsterPotion->name = "White Monster Potion";
            whiteMonsterPotion->damage = 0;
            whiteMonsterPotion->health = 150;  // Assuming it restores 150 health
            whiteMonsterPotion->durability = 1;
            whiteMonsterPotion->isUsing = false;

            // Add the potion to the room's item list if there's space
            if (room->numberOfItems < MAX_INVENTORY) {
                room->item[room->numberOfItems++] = whiteMonsterPotion;
                printf("A White Monster Potion appears on the ground!\n");
            } else {
                printf("There's no space in the room for the White Monster Potion.\n");
                free(whiteMonsterPotion);  // Clean up if the potion can't be added
            }
        }

        if (player->health <= 0) {
            printf("You have been defeated. Game over.\n");
            exit(0);
        }
    } else {
        printf("There is nothing to attack here.\n");
    }
}
