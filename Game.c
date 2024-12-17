// Include necessary headers for game components
#include "Item.h"
#include "Player.h"
#include "Creature.h"
#include "Room.h"
// Standard library headers for input/output, memory management, and utilities
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <dirent.h>

// Define constants for inventory, command input, and history limits
#define MAX_INVENTORY 10 // Maximum number of items in inventory
#define MAX_COMMMAND 100 // Maximum length of a command
#define MAX_HISTORY 1000 // Maximum number of commands stored in history

// Structure to manage game state and command history
typedef struct Game {
    char command_history[MAX_HISTORY][MAX_COMMMAND]; // Stores previous commands
    int command_count; // Tracks the number of stored commands
} Game;

// Initialize game state
Game game ={ .command_count=0 };



// Function declarations for gameplay
void parse_command(char *input, Player *player, Room **current_room);
void saveGame(const char *filepath); // Save game state to a file
void loadGame(const char *filepath, Player *player, Room **current_room); // Load game state from a file
void listSaves(); // List available save files
void printItem(Item *item); // Print item details


int main(){
    // Initialize random number generator for gameplay randomness
    srand(time(NULL));

    // Define player and items
    Player player ={100 ,10,{0},0};
    
    Item healthPotion = {"Health Potion",0,50,1,false};
    Item rustySword = {"Rusty Sword",5,0,50,false};
    Item silverSword = {"Silver Sword", 10,0,100,false};
    Item goldSword = {"Gold Sword",20,0,200,false};
    Item Cape={"Kvothe's Cape",20,150,5000,false};
    Item barukasDagger={"Baruka's Dagger",50,0,400,false}; 
    Item damagePotion = {"Damage Potion",20,0,1,false};
    Item guardiansPotion={"Guardians Potion",0,300,1,false};
    Item raptor = {"Raptor",100,0,800,false};
    Item whiteMonsterPotion = {"White Monster Potion",0,150,1,false};

    Creature goblin = {"Goblin", 80, 10};  
    Creature goblinArmy = {"Goblin Army", 150, 20};  
    Creature bossGoblin = {"Boss Goblin", 300, 30};  
    Creature spiderArmy = {"Spider Army", 150, 20};  
    Creature bossSpider = {"Boss Spider", 300, 30};  
    Creature finalBoss = {"Mighty Knight", 600, 70};  

    
    Room *entranceRoom = createRoom("You are in a dark dungeon. A soft whisper fills the air, saying, 'Go left...",&rustySword,NULL);
    Room *potionRoom = createRoom("The room full with darkness and The air is cold and still",&healthPotion,NULL);
    Room *skeletonRoom = createRoom("A gust of wind blows past you, and you hear a voice say, 'Don't go forward.",NULL,NULL);
    Room *specialRoom = createRoom("The strange puff grows stronger. The whispers become louder: 'Take it...",&Cape,NULL);
    Room *goblinRoom = createRoom("this is a dark dungeon room. The air smells damp and old. Shadows move on the stone walls from a weak torch nearby.",NULL,&goblin);
    Room *goblinArmyRoom = createRoom("you followed the road and floor become colder.",&goldSword,&goblinArmy);
    Room *dmgPotionRoom = createRoom("A room with a warm, comforting temperature. The air feels cozy, not too hot but just enough to make you feel relaxed. ",&whiteMonsterPotion,NULL);
    Room *specialDaggerRoom = createRoom("You find a chest in the corner of the room. Curiosity leads you to open it, and inside,",&barukasDagger,NULL);
    Room *passagePoint = createRoom("There is a woman lying unconscious on the floor, her face twisted in terror. Blood trails from the door on the right, leading to where she collapsed",NULL,NULL);
    Room *bossGoblinRoom = createRoom("The room is filthy, with mud and trash scattered across the floor. The air smells musty, and the walls are covered in grime",NULL,&bossGoblin);
    Room *spiderPit = createRoom("There is a deep pit in the center of the room. The walls are covered with small spiders",&silverSword,NULL);
    Room *spiderArmyRoom = createRoom("The room is dark and damp, with the smell of wet stone. Spider webs cover the walls, and small spiders crawl around. The floor is made of cracked stones",&goldSword,&spiderArmy);
    Room *bossSpiderRoom = createRoom("The room is pitch black, and the air feels heavy. The walls are damp and covered in thick, sticky webs. You can hear soft skittering sounds echoing around you",NULL,&bossSpider);
    Room *oldFriendRoom = createRoom("It feels safe here, with a calm atmosphere. On the ground, you see a man lying motionless, lifeless. Beside him, there are some items scattered around, maybe something useful.",&whiteMonsterPotion,NULL);
    Room *finalBossRoom = createRoom("The room has a big, dirty statue with a creepy smile.Its eyes are empty, but it feels like it's watching you. The room is quiet, but you can hear dripping sounds, maybe blood.",NULL,&finalBoss);
    Room *finalRoom = createRoom("You reach the exit of the dungeon. The light outside shines brightly, and you can feel the fresh air as you step closer to freedom. The dark and dangerous dungeon is now behind you",NULL,NULL);

    // Set connections between rooms to define the map

    set_connection(entranceRoom,potionRoom,"left");
    set_connection(entranceRoom,spiderPit,"right");
    set_connection(entranceRoom,goblinArmyRoom,"up");

    set_connection(potionRoom,skeletonRoom,"left");
    set_connection(potionRoom,goblinRoom,"up");
    
    set_connection(skeletonRoom,specialRoom,"up");

    set_connection(goblinRoom,specialDaggerRoom,"up");

    set_connection(goblinArmyRoom,dmgPotionRoom,"up");

    set_connection(dmgPotionRoom,passagePoint,"right");
    
    set_connection(passagePoint,bossGoblinRoom,"right");

    set_connection(bossGoblinRoom,oldFriendRoom,"right");
    set_connection(bossGoblinRoom,bossSpiderRoom,"up");
    set_connection(bossGoblinRoom,spiderArmyRoom,"down");

    set_connection(oldFriendRoom,finalBossRoom,"up");

    set_connection(finalBossRoom,finalRoom,"up");

    set_connection(spiderPit,spiderArmyRoom,"up");

    // Initialize the player's starting room
    Room *currentRoom = entranceRoom;

    // Game loop variables
    char command[MAX_COMMMAND];
    
    // Print introductory message to the player
    
    printf("\n        ********** Whisper **********\n");
    printf("Welcome, brave adventurer, to the Whisper Adventure Game!\n");
    printf("Your journey begins now. Below are the commands you can use:\n\n");

    printf("  - 'exit'      : Exit the game\n");
    printf("  - 'save'      : Save your current progress\n");
    printf("  - 'load'      : Load a saved game\n");
    printf("  - 'list'      : View a list of available save files\n\n");

    printf("  - 'move'      : Move to a different room\n");
    printf("  - 'pickup'    : Pick up an item from the ground\n");
    printf("  - 'use'       : Use an item from your inventory\n");
    printf("  - 'inventory' : View your current inventory\n\n");

    printf("  - 'discard'   : Discard an item from your inventory\n");
    printf("  - 'attack'    : Attack an enemy or creature\n");
    printf("  - 'look'      : Look around the room for a description\n");
    printf("  - 'status'    : View your current status (health, damage, etc.)\n\n");

    printf("Remember, your decisions will shape your fate. Choose wisely!\n");

    // Main game loop
    while (1) {
        printf("\n> ");
        fgets(command, MAX_COMMMAND, stdin); // Get player input
        command[strcspn(command, "\n")] = 0; // Remove the newline character

        // Handle "exit" command to quit the game
        if (strcmp(command, "exit") == 0) {
            printf("Thanks for playing!\n");
            break;
        }

        // Save the command in the history if space allows
        if (game.command_count < MAX_HISTORY) {
            strncpy(game.command_history[game.command_count++], command, MAX_COMMMAND);
        } else {
            printf("Command history is full. Unable to save further commands.\n");
        }

        // Handle special commands for saving, loading, or listing saves
        if (strcmp(command, "save") == 0) {
            char filename[50];
            printf("Enter save file name: ");
            scanf("%49s", filename);
            getchar(); // Consume the newline left by scanf
            saveGame(filename);
            printf("Game saved to %s.\n", filename);
            continue;
        } else if (strcmp(command, "load") == 0) {
            char filename[50];
            printf("Enter save file name to load: ");
            scanf("%49s", filename);
            getchar(); // Consume the newline left by scanf
            loadGame(filename, &player, &currentRoom);
            printf("Game loaded from %s.\n", filename);
            continue;
        } else if (strcmp(command, "list") == 0) {
            listSaves();
        }

        // Parse and execute player commands
        parse_command(command, &player, &currentRoom);
    }

    // Free allocated memory for rooms before exiting
    free_room(entranceRoom);
    free_room(spiderPit);
    free_room(spiderArmyRoom);
    free_room(potionRoom);
    free_room(skeletonRoom);
    free_room(specialRoom);
    free_room(goblinRoom);
    free_room(goblinArmyRoom);
    free_room(dmgPotionRoom);
    free_room(passagePoint);
    free_room(specialDaggerRoom);
    free_room(bossGoblinRoom);
    free_room(bossSpiderRoom);
    free_room(oldFriendRoom);
    free_room(finalBossRoom);

    return 0; // Exit the program successfully
}

// Function to parse player commands and execute appropriate actions
void parse_command(char *input, Player *player, Room **currentRoom) {
    char command[10], argument[90];
    // Read the command and argument from the input string
    sscanf(input, "%s %[^\n]", command, argument); // '%[^\n]' reads until the newline

    // Match command and execute corresponding functionality
    if (strcmp(command, "move") == 0) {
        move(player, currentRoom, argument); // Move to a connected room
    } else if (strcmp(command, "look") == 0) {
        look(*currentRoom); // Print room description
    } else if (strcmp(command, "inventory") == 0) {
        inventory(player); // Display player's inventory
    } else if (strcmp(command, "pickup") == 0) {
        pickup(player, *currentRoom, argument); // Pick up an item from the current room
    } else if (strcmp(command, "status") == 0) {
        showStatus(player); // Display player's status
    } else if (strcmp(command, "use") == 0) {
        if (player->numberOfItems > 0) { // Check if player has items
            for (int i = 0; i < player->numberOfItems; i++) {
                if (strcmp(player->inventory[i]->name, argument) == 0) {
                    useItem(player, (Item*)player->inventory[i]); // Use the specified item
                    break;
                }
            }
        }
    } else if (strcmp(command, "attack") == 0) {
        attack(player, *currentRoom); // Attack a creature in the room
    } else if (strcmp(command, "discard") == 0) {
        discard(player, argument, *currentRoom); // Discard an item to the current room
    } else {
        printf("Unknown command. Try 'move', 'look', 'inventory', 'pickup', 'use', 'status', or 'attack'.\n");
    }
}

// Function to save game state to a file
void saveGame(const char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Error: Could not save game. Unable to open file %s.\n", filepath);
    } else {
        for (int i = 0; i < game.command_count; i++) {
            fprintf(file, "%s\n", game.command_history[i]); // Write command history to the file
        }
        fclose(file); // Close the file
    }
}

// Function to load game state from a file
void loadGame(const char *filepath, Player *player, Room **current_room) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Error: Could not load game. Unable to open file %s.\n", filepath);
    } else {
        char command[MAX_COMMMAND];
        game.command_count = 0; // Reset command history

        while (fgets(command, MAX_COMMMAND, file)) {
            command[strcspn(command, "\n")] = 0; // Remove newline character
            if (game.command_count < MAX_HISTORY) {
                strncpy(game.command_history[game.command_count++], command, MAX_COMMMAND);
                parse_command(command, player, current_room); // Replay the command to restore game state
            }
        }
        fclose(file); // Close the file
    }
}

// Function to list available save files in the current directory
void listSaves() {
    DIR *dir = opendir(".");
    if (!dir) {
        printf("Error: Could not open current directory.\n");
        return;
    }

    struct dirent *entry;
    printf("Available save files:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".txt")) { // Only list .txt files
            printf("- %s\n", entry->d_name);
        }
    }
    closedir(dir); // Close the directory
}