#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
// Display player's inventory

void save_game(Player *player, Room *rooms, Room *current_room, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    // Oyuncu verilerini kaydet
    fwrite(player, sizeof(Player), 1, file);

    // Oda durumlarını kaydet
    for (int i = 0; i < 5; i++) {
        fwrite(&rooms[i].enemy, sizeof(Enemy*), 1, file);
        fwrite(&rooms[i].item, sizeof(Item*), 1, file);
    }

    // Mevcut oda indeksini kaydet
    int current_room_index = current_room - rooms;
    fwrite(&current_room_index, sizeof(int), 1, file);

    fclose(file);
    printf("Game saved successfully to %s!\n", filename);
}

void load_game(Player *player, Room *rooms, Room **current_room, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Could not open file for loading.\n");
        return;
    }

    // Oyuncu verilerini yükle
    fread(player, sizeof(Player), 1, file);

    // Oda durumlarını yükle
    for (int i = 0; i < 5; i++) {
        fread(&rooms[i].enemy, sizeof(Enemy*), 1, file);
        fread(&rooms[i].item, sizeof(Item*), 1, file);
    }

    // Mevcut oda indeksini yükle
    int current_room_index;
    fread(&current_room_index, sizeof(int), 1, file);
    *current_room = &rooms[current_room_index];

    fclose(file);
    printf("Game loaded successfully from %s!\n", filename);
}


void show_inventory(Player *player) {
    if (player->inventory_count == 0) {
        printf("Your inventory is empty.\n");
        return;
    }
    printf("Your Inventory:\n");
    for (int i = 0; i < player->inventory_count; i++) {
        printf(" - %s\n", player->inventory[i]);
    }
}

// Pickup item from the current room
void pickup_item(Player *player, Room *current_room) {
    if (current_room->item) {
        printf("You picked up: %s\n", current_room->item->name);

        // Check for special effect: Map
        if (strcmp(current_room->item->name, "Map") == 0) {
            printf("You now have the Map! You can see directions to other rooms.\n");
            player->has_map = 1;  // Set the Map flag
        }

        if (current_room->item != NULL && strcmp(current_room->item->name, "Sword") == 0) {
            printf("The Sword increases your attack damage!\n");
            player->damage = 20;
            printf("Your new damage: %d\n", player->damage);  // Test için ekle
        }

        if (strcmp(current_room->item->name, "Key") == 0) {
            printf("You now have the Key!\n");
            player->has_key = 1;
        }

        if (current_room->item != NULL && strcmp(current_room->item->name, "Health Potion") == 0) {
            printf("Your health is full\n");
            player->health = 100;
        }


        if (strcmp(current_room->item->name, "Note") == 0) {
            printf("Hint: A wolf guards a key in the east.\n");

        }


        // Add item to inventory
        if (player->inventory_count < MAX_INVENTORY) {
            strcpy(player->inventory[player->inventory_count], current_room->item->name);
            player->inventory_count++;
            free(current_room->item);  // Remove the item from the room
            current_room->item = NULL;
        } else {
            printf("Your inventory is full!\n");
        }
    } else {
        printf("There is nothing to pick up here.\n");
    }
}



void initialize_game(Player *player, Room **rooms) {
    player->health = 100;
    player->damage = 10;
    player->inventory_count = 0;
    player->has_map = 0;
    player->has_key = 0;
    player->name;

    *rooms = malloc(5 * sizeof(Room));
    if (*rooms == NULL) {
        printf("Error allocating memory for rooms!\n");
        exit(1);
    }

    // Room 1: Map Room
    strcpy((*rooms)[0].description, "Room 1: A map is on the wall. There is an exit to the east.");
    (*rooms)[0].item = malloc(sizeof(Item));
    if ((*rooms)[0].item != NULL) {
        strcpy((*rooms)[0].item->name, "Map");
        strcpy((*rooms)[0].item->effect, "Reveals room directions.");
    }
    (*rooms)[0].enemy = NULL;
    (*rooms)[0].east = &(*rooms)[1];
    (*rooms)[0].north = NULL;
    (*rooms)[0].west = NULL;
    (*rooms)[0].south = NULL;

    // Room 2: Goblin Room
    strcpy((*rooms)[1].description, "Room 2: A goblin blocks your path!");
    (*rooms)[1].enemy = malloc(sizeof(Enemy));
    if ((*rooms)[1].enemy != NULL) {
        strcpy((*rooms)[1].enemy->name, "Goblin");
        (*rooms)[1].enemy->health = 50;
        (*rooms)[1].enemy->damage = 10;
    }
    (*rooms)[1].item = NULL;
    (*rooms)[1].east = &(*rooms)[2];
    (*rooms)[1].north = NULL;
    (*rooms)[1].west = &(*rooms)[0];
    (*rooms)[1].south = NULL;

    // Room 3: Note Room
    strcpy((*rooms)[2].description, "Room 3: A note lies on the ground.");
    (*rooms)[2].item = malloc(sizeof(Item));
    if ((*rooms)[2].item != NULL) {
        strcpy((*rooms)[2].item->name, "Note");
        strcpy((*rooms)[2].item->effect, "Hint: A wolf guards a key in the east.");
    }
    (*rooms)[2].enemy = NULL;
    (*rooms)[2].east = &(*rooms)[3];
    (*rooms)[2].north = &(*rooms)[4];
    (*rooms)[2].west = &(*rooms)[1];
    (*rooms)[2].south = NULL;

    // Room 4: Wolf Room
    strcpy((*rooms)[3].description, "Room 4: A wolf growls at you, ready to attack.");
    (*rooms)[3].enemy = malloc(sizeof(Enemy));
    if ((*rooms)[3].enemy != NULL) {
        strcpy((*rooms)[3].enemy->name, "Wolf");
        (*rooms)[3].enemy->health = 70;
        (*rooms)[3].enemy->damage = 10;
    }
    (*rooms)[3].item = NULL;
    (*rooms)[3].east = NULL;
    (*rooms)[3].north = NULL;
    (*rooms)[3].west = &(*rooms)[2];
    (*rooms)[3].south = NULL;

    // Room 5: Dragon Room
    strcpy((*rooms)[4].description, "Room 5: The final chamber. A dragon awaits you.");
    (*rooms)[4].enemy = malloc(sizeof(Enemy));
    if ((*rooms)[4].enemy != NULL) {
        strcpy((*rooms)[4].enemy->name, "Dragon");
        (*rooms)[4].enemy->health = 100;
        (*rooms)[4].enemy->damage = 20;
    }
    (*rooms)[4].item = malloc(sizeof(Item));
    if ((*rooms)[4].item != NULL) {
        strcpy((*rooms)[4].item->name, "Health Potion");
        strcpy((*rooms)[4].item->effect, "Restores full health.");
    }
    (*rooms)[4].east = NULL;
    (*rooms)[4].north = NULL;
    (*rooms)[4].west = &(*rooms)[2];
    (*rooms)[4].south = NULL;
    (*rooms)[4].has_lock = 1;
}

void cleanup_game(Room *rooms, int room_count) {
    for (int i = 0; i < room_count; i++) {
        if (rooms[i].item != NULL) {
            free(rooms[i].item);
            rooms[i].item = NULL;
        }
        if (rooms[i].enemy != NULL) {
            free(rooms[i].enemy);
            rooms[i].enemy = NULL;
        }
    }
    free(rooms);
}



void describe_room(Room *current_room, Player *player) {
    printf("\n%s\n", current_room->description);

    // Check if there is an item
    if (current_room->item != NULL) {
        printf("You see an item: %s.\n", current_room->item->name);
    }

    // Check if there is an enemy
    if (current_room->enemy != NULL) {
        printf("An enemy is here: %s!\n", current_room->enemy->name);
    }

    // Show directions ONLY if player has the Map
    if (player->has_map) {
        printf("You can move in these directions:\n");
        if (current_room->north != NULL) printf(" - North (n)\n");
        if (current_room->south != NULL) printf(" - South (s)\n");
        if (current_room->east != NULL)  printf(" - East (e)\n");
        if (current_room->west != NULL)  printf(" - West (w)\n");
    }
}


void move_player(Room **current_room, char direction, Player *player) {
    Room *next_room = NULL;

    if (direction == 'e') {
        next_room = (*current_room)->east;
    } else if (direction == 'w') {
        next_room = (*current_room)->west;
    } else if (direction == 'n') {
        next_room = (*current_room)->north;
    } else if (direction == 's') {
        next_room = (*current_room)->south;
    } else {
        printf("Invalid direction! Use 'n', 's', 'e', or 'w'.\n");
        return;
    }

    if (next_room != NULL && next_room->has_lock == 1) {
        if (player->has_key == 1) {
            *current_room = next_room;  // Yalnızca geçerli bir oda varsa ilerle
            printf("You moved to a new room.\n");
        }else {printf("It is locked.\n");}
    } else if (next_room != NULL) {
        *current_room = next_room;  // Yalnızca geçerli bir oda varsa ilerle
        printf("You moved to a new room.\n");
    } else {
        printf("You cannot move in that direction. There is no path!\n");
    }
}


