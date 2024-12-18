#include <stdio.h>
#include <string.h>
#include "game.h"

int main() {
    Player player;
    Room *rooms = NULL;
    Room *current_room = NULL;
    char command[100];

    initialize_game(&player, &rooms);
    current_room = &rooms[0];

    printf("Welcome to the Adventure Game!\n");
    printf("Available commands: 'look', 'move <direction>', 'pickup', 'attack', 'inventory', 'exit'.\n");

    while (1) {
        printf("\nEnter command: ");
        fgets(command, sizeof(command), stdin);

        if (strncmp(command, "look", 4) == 0) {
            describe_room(current_room, &player);
        } else if (strncmp(command, "move", 4) == 0) {
            move_player(&current_room, command[5], &player);
        } else if (strncmp(command, "inventory", 9) == 0) {
            show_inventory(&player);
        } else if (strncmp(command, "pickup", 6) == 0) {
            pickup_item(&player, current_room);
        } else if (strncmp(command, "attack", 6) == 0) {
            if (current_room->enemy) {
                start_combat(&player, current_room->enemy, current_room);
            } else {
                printf("There is no one to attack here.\n");
            }
        } else if (strncmp(command, "exit", 4) == 0) {
            printf("Exiting the game. Goodbye!\n");
            break;
        } else if (strncmp(command, "save", 4) == 0) {
            char filename[50];
            sscanf(command + 5, "%49s", filename);  // Dosya adını al
            save_game(&player, rooms, current_room, filename);
        } else if (strncmp(command, "load", 4) == 0) {
            char filename[50];
            sscanf(command + 5, "%49s", filename);  // Dosya adını al
            load_game(&player, rooms, &current_room, filename);
        }else {
            printf("Invalid command! Try again.\n");
        }
    }


    cleanup_game(rooms, 5);
    return 0;
}
