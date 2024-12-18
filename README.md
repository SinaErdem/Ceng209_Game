README.md
Dungeon Adventure Game
Dungeon Adventure Game is a command-line-based adventure game developed in C. The player explores rooms in a dungeon, collects items, battles enemies, and uses hints to reach the end of the game.

Game Features
Room Exploration: Players navigate through dungeon rooms using the move command.
Combat System: Turn-based combat with enemies.
Inventory Management: Collect and manage items in the player's inventory.
Locked Rooms: Some rooms are locked and require a key to unlock.
Save System: Save the game's current state and load it later.
How to Run
1. Build the Game
To build the game, run the following commands in the root directory of the project:

bash
cmake .
make
2. Run the Game
After building the project, start the game with:

bash
./untitled
Game Commands
Command	Description
look	Displays the description of the current room.
move <dir>	Moves in the specified direction (n, s, e, w).
pickup	Picks up an item in the current room.
attack	Attacks the enemy in the current room.
inventory	Displays the player's inventory.
save <file>	Saves the game state to the specified file.
load <file>	Loads the game state from the specified file.
exit	Exits the game.
Game Flow
Start: The player starts in the first room.
Exploration: Use the look command to see room details, items, and enemies.
Movement: Navigate between rooms using the move command.
Combat: Engage in turn-based combat using the attack command.
Collect Items: Use the pickup command to collect items in the room.
Save and Load: Save progress with save and reload it later with load.

bash
/project
    |-- main.c          # Main game loop
    |-- game.c          # Game mechanics (movement, inventory, etc.)
    |-- combat.c        # Combat mechanics
    |-- utils.c         # Utility functions (screen clearing, delays, etc.)
    |-- game.h          # Header file for game functions
    |-- utils.h         # Header file for utility functions
    |-- CMakeLists.txt  # Build configuration
Save and Load System
Save: Use the save <filename> command to save the current game state.
Load: Use the load <filename> command to reload a previously saved game state.
Example Usage:

lua
save savefile.dat
load savefile.dat
Key Functions
save_game
Saves the current game state to a file.

load_game
Loads the game state from a file.

start_combat
Handles turn-based combat between the player and enemies.

Developer Notes
Compiler: GCC (MinGW) or Clang
Standard: C11
Platform: Windows/Linux/MacOS
How to Contribute
Contributions are welcome! Feel free to submit a pull request or open an issue to report bugs or suggest improvements.






