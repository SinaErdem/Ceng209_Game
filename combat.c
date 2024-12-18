#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // strcmp ve strcpy için gerekli
#include <time.h>
#include "game.h"

void start_combat(Player *player, Enemy *enemy, Room *current_room) {
    int input, target_number;
    srand(time(NULL));

    printf("Combat started against %s!\n", enemy->name);

    while (enemy->health > 0 && player->health > 0) {
        printf("\n%s's Health: %d | Your Health: %d\n", enemy->name, enemy->health, player->health);

        // Random number generation
        target_number = rand() % 9 + 1;
        printf("Press %d within 2 seconds to attack!\n", target_number);

        // Timed input
        time_t start_time = time(NULL);
        scanf("%d", &input);

        if (input == target_number && time(NULL) - start_time <= 2) {
            printf("You hit the enemy for %d damage!\n", player->damage);
            enemy->health -= player->damage;
        } else {
            printf("You missed your attack!\n");
        }

        // Enemy attack
        if (enemy->health > 0) {
            printf("The %s hits you for %d damage!\n", enemy->name, enemy->damage);
            player->health -= enemy->damage;
            if (player->health <= 0) {
                printf("You have been defeated. Game Over.\n");
                exit(0);
            }
        }
    }

    // Enemy defeated
    printf("You defeated the %s!\n", enemy->name);

    // Drop Sword as loot if Goblin is defeated
    if (strcmp(enemy->name, "Goblin") == 0) {
        printf("The Goblin dropped a Sword!\n");
        current_room->item = malloc(sizeof(Item));
        if (current_room->item != NULL) {
            strcpy(current_room->item->name, "Sword");
            strcpy(current_room->item->effect, "Doubles your attack damage.");
        }
    }

    if (strcmp(enemy->name, "Wolf") == 0) {
        printf("The Wolf dropped a Key!\n");
        current_room->item = malloc(sizeof(Item));
        if (current_room->item != NULL) {
            strcpy(current_room->item->name, "Key");
            strcpy(current_room->item->effect, "Unlocks a secret room.");
        }
    }

    free(enemy);  // Clean up enemy
    current_room->enemy = NULL;  // Remove enemy from the room

    if (strcmp(enemy->name, "Dragon") == 0) {
        printf("\n");
        printf("***************************************\n");
        printf("You cleared the dungeons from monsters.\n");
        printf("         You saved the village\n");
        printf("***************************************\n");
        current_room->item = malloc(sizeof(Item));
        if (current_room->item != NULL) {
            strcpy(current_room->item->name, "Key");
            strcpy(current_room->item->effect, "Unlocks a secret room.");
        }
    }
}
