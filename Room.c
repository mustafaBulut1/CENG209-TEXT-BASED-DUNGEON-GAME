#include "Room.h" // Include the header file containing declarations for Room-related functions and structures

#include <stdio.h> // Standard input/output library for printing
#include <stdlib.h> // Standard library for memory management functions
#include <string.h> // String manipulation functions

// Function to create a new room with a description, optional item, and optional creature
Room *createRoom(const char *description, Item *item, Creature *creature) {
    Room *room = malloc(sizeof(Room)); // Allocate memory for a new Room
    room->description = strdup(description); // Copy the room's description into allocated memory
    room->numberOfItems = 0; // Initialize the number of items in the room to 0

    // Initialize all item slots to NULL
    for (int i = 0; i < MAX_INVENTORY; i++) {
        room->item[i] = NULL;
    }

    // If an item is provided, add it to the room's inventory
    if (item != NULL) {
        room->item[room->numberOfItems++] = item;
    }

    room->creature = creature; // Assign the creature to the room
    room->up = NULL; // Initialize the 'up' connection to NULL
    room->down = NULL; // Initialize the 'down' connection to NULL
    room->left = NULL; // Initialize the 'left' connection to NULL
    room->right = NULL; // Initialize the 'right' connection to NULL
    return room; // Return the newly created room
}

// Function to establish a connection between two rooms in a specified direction
void set_connection(Room *room, Room *connectedRoom, const char *direction) {
    if (strcmp(direction, "up") == 0) { // Connect rooms vertically upwards
        room->up = connectedRoom;
        connectedRoom->down = room;
    } else if (strcmp(direction, "down") == 0) { // Connect rooms vertically downwards
        room->down = connectedRoom;
        connectedRoom->up = room;
    } else if (strcmp(direction, "right") == 0) { // Connect rooms horizontally to the right
        room->right = connectedRoom;
        connectedRoom->left = room;
    } else if (strcmp(direction, "left") == 0) { // Connect rooms horizontally to the left
        room->left = connectedRoom;
        connectedRoom->right = room;
    }
}

// Function to display the room's description, contents, and possible connections
void look(Room *room) {
    printf("%s\n", room->description); // Print the room's description

    // Check if the room contains any items
    if (room->numberOfItems > 0) {
        for (int i = 0; i < room->numberOfItems; i++) {
            // Print the name of each item in the room
            printf(" %s lying on the ground \n", room->item[i]->name);
        }
    }

    // Check if the room contains a creature
    if (room->creature != NULL) {
        printf("There is a %s in the room!\n", room->creature->name); // Print the creature's name
    } else {
        printf("The room is empty.\n"); // Indicate that the room is empty
    }

    // Display the possible directions the player can move
    printf("Possible directions: ");
    if (room->up) printf("up "); // Display 'up' if a connection exists
    if (room->down) printf("down "); // Display 'down' if a connection exists
    if (room->left) printf("left "); // Display 'left' if a connection exists
    if (room->right) printf("right "); // Display 'right' if a connection exists
    printf("\n");
}

// Function to free the memory allocated for a room
void free_room(Room *room) {
    if (room) { // Check if the room pointer is not NULL
        free(room->description); // Free the memory allocated for the room's description
        free(room); // Free the memory allocated for the Room structure
    }
}
