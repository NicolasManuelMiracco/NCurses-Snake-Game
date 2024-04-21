#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <vector>

using namespace std;

struct Coordinate {
    int x = 10, y = 10;
};

void drawLimits() {
    for (int i = 0; i < COLS; i++) {
        mvaddch(0, i, '#'); // Top border
        mvaddch(LINES - 1, i, '#'); // Bottom border
    }
    for (int i = 1; i < LINES - 1; i++) {
        mvaddch(i, 0, '#'); // Left border
        mvaddch(i, COLS - 1, '#'); // Right border
    }
}

void spawnEgg(Coordinate &egg) {
    do {
        egg.x = rand() % (COLS - 2) + 1; 
        egg.y = rand() % (LINES - 2) + 1; 
    } while (mvwinch(stdscr, egg.y, egg.x) == '@'); 
    mvaddch(egg.y, egg.x, 'o');
}

void startGame() {
    initscr(); cbreak(); noecho(); keypad(stdscr, TRUE); curs_set(0); nodelay(stdscr, TRUE);
    Coordinate position, egg;
    vector<Coordinate> tail; // Store tail segments
    int currentCursor = KEY_RIGHT, ch, score = 0, lives = 3, level = 1, eggsEaten = 0;
    int speedDelay = 100000; 
    bool game = true;

    drawLimits(); 
    spawnEgg(egg); 

    while (game) {
        ch = getch();
        if (ch != ERR) {
            int oppositeCursor = (currentCursor == KEY_UP) ? KEY_DOWN :
                                (currentCursor == KEY_DOWN) ? KEY_UP :
                                (currentCursor == KEY_LEFT) ? KEY_RIGHT : KEY_LEFT;
                                
            if (ch == oppositeCursor) {
                lives--; // Lose a life if trying to move in the opposite direction
                beep(); // Make a beep sound to indicate loss of life
                if (lives == 0) {
                    game = false; // End game if no lives left
                } else {
                    // Optional: You can add logic here to handle the snake's position or tail if needed
                }
            } else if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT) {
                currentCursor = ch;
            }
        }

        // Move tail (shift all segments)
        for (int i = tail.size() - 1; i > 0; i--) {
            tail[i] = tail[i - 1];
        }
        if (!tail.empty()) {
            tail[0] = position; // Head's previous position becomes tail's first segment
        }

        // Move head
        switch (currentCursor) {
            case KEY_UP:    position.y--; break;
            case KEY_DOWN:  position.y++; break;
            case KEY_LEFT:  position.x--; break;
            case KEY_RIGHT: position.x++; break;
        }

        // Check for collisions
        bool collision = position.x <= 0 || position.x >= COLS - 1 || position.y <= 0 || position.y >= LINES - 1;
        for (const Coordinate &segment : tail) {
            if (position.x == segment.x && position.y == segment.y) {
                collision = true;
                break;
            }
        }

        if (collision) {
            lives--;
            beep(); // Low tone for losing a life
            if (lives == 0) {
                game = false;
            } else {
                // Reset to starting position
                position.x = 10;
                position.y = 10;
                tail.clear(); // Clear the tail
            }
        } else if (position.x == egg.x && position.y == egg.y) {
            spawnEgg(egg); 
            beep(); 
            score++; 
            eggsEaten++;
            tail.push_back(position); // Grow tail

            if (eggsEaten % 5 == 0) { // Level up every 5 eggs
                level++;
                speedDelay -= 10000; // Increase speed (decrease delay)
                if (level % 3 == 0) { // Extra life every 3 levels
                    lives++;
                    flash(); // Warning sound for extra life
                }
            }
        }

        clear();
        drawLimits(); 
        mvprintw(position.y, position.x, "@");
        for (const Coordinate &segment : tail) {
            mvprintw(segment.y, segment.x, "o"); // Draw tail
        }
        mvaddch(egg.y, egg.x, 'o'); 
        mvprintw(0, 2, "Level: %d", level);         // Display level
        mvprintw(0, COLS / 2 - 5, "Lives: %d", lives); // Display lives
        mvprintw(0, COLS - 12, "Score: %d", score);   // Display score
        refresh();
        usleep(speedDelay); 
    }

    endwin();
    cout << "Game over\n";
}

int main() {
    srand(time(NULL)); 
    startGame();
    return 0;
}