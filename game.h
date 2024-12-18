#ifndef GAME_H
#define GAME_H

#define MAX_INVENTORY 5
#define ROOM_DESC_SIZE 256
#define ITEM_NAME_SIZE 50

// Player Structure
typedef struct {
    int health;
    int damage;
    char inventory[MAX_INVENTORY][ITEM_NAME_SIZE];
    int inventory_count;
    int has_map;
    int has_key;
    char name[20];
} Player;


// Enemy Structure
typedef struct {
    char name[ITEM_NAME_SIZE];
    int health;
    int damage;
} Enemy;

// Item Structure
typedef struct {
    char name[ITEM_NAME_SIZE];
    char effect[ITEM_NAME_SIZE];
} Item;

// Room Structure
typedef struct Room {
    char description[ROOM_DESC_SIZE];
    int has_lock;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    Item *item;
    Enemy *enemy;
} Room;

// Function Prototypes
void initialize_game(Player *player, Room **rooms);
void move_player(Room **current_room, char direction, Player *player);
void describe_room(Room *current_room, Player *player);
void show_inventory(Player *player);
void pickup_item(Player *player, Room *current_room);
void start_combat(Player *player, Enemy *enemy, Room *current_room);
void clear_screen();
void print_delayed(const char *message);
void cleanup_game(Room *rooms, int room_count);
void save_game(Player *player, Room *rooms, Room *current_room, const char *filename);
void load_game(Player *player, Room *rooms, Room **current_room, const char *filename);

#endif
