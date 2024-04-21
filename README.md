# NCurses-Snake-Game

One-line description: A terminal-based Snake game implemented in C++ using the ncurses library, featuring levels, scoring, and live updates.

Summary: This program creates a dynamic Snake game that runs directly in a terminal window. It utilizes the ncurses library to manage input/output within the terminal, allowing for real-time gameplay without refreshing the entire screen. The game initializes with a snake positioned in the middle of the screen, and the snake moves in response to arrow key inputs from the user. The main gameplay loop handles user input, updates the snake's position, checks for collisions, and manages the scoring and level system.

Key features include:
- **Boundary and Self-collision Detection**: The game ends if the snake runs into the screen boundaries or itself.
- **Egg Spawning and Eating**: Eggs appear randomly on the screen, and when eaten by the snake, they increase the player's score and lengthen the snake.
- **Level Progression**: The game becomes progressively faster as the player's score increases, with every set of eggs eaten increasing the level and speed.
- **Lives and Sound Effects**: The player starts with a set number of lives, which are lost on collisions. The game makes use of sound effects for various events like losing a life or eating an egg.
- **Graphical Updates**: The game board shows the current level, score, and remaining lives at the top of the window, and updates these in real time.

The game loop continuously checks for user input and updates the game state, red
