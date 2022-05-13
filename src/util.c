#include "../include/util.h"

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4

// TODO: figure out a more elegant solution
int is_collision(game_state current_state, int x, int y, int direction)
{
    switch (direction) {
        case DIR_RIGHT:
            if (is_wall_cell(current_state, x + 1, y)) {
                return 1;
            }
            break;
        case DIR_LEFT:
            if (is_wall_cell(current_state, x - 1, y)) {
                return 1;
            }
            break;
        case DIR_UP:
            if (is_wall_cell(current_state, x, y - 1)) {
                return 1;
            }
            break;
        case DIR_DOWN:
            if (is_wall_cell(current_state, x, y + 1)) {
                return 1;
            }
            break;
    }

    return 0;
}

int is_wall_cell(game_state current_state, int x, int y)
{
    if (current_state.map[y][x] == '#') {
        return 1;
    }
    
    return 0;
}

void print_game_state(game_state current_state)
{
    for (int row = 0; row < MAX_ROWS; row++) {
        printw(": ");
        for (int col = 0; col < MAX_COLS; col++) {
            
            // Pacman
            if (current_state.pacman.y == row && current_state.pacman.x == col) {
                switch (current_state.pacman.direction) {
                    case DIR_RIGHT:
                        addch(ACS_LARROW);
                        printw(" ");
                        break;
                    case DIR_LEFT:
                        addch(ACS_RARROW);
                        printw(" ");
                        break;
                    case DIR_UP:
                        // addch(ACS_DARROW);           /* TODO: ACS_DARROW prints as ꓕ on my terminal, fix*/
                        printw("v ");
                        break;
                    case DIR_DOWN:
                        addch(ACS_UARROW);
                        printw(" ");
                        break;
                    default:
                        break;
                }
            }
            // Ghost
            else if (current_state.ghost_1.y == row && current_state.ghost_1.x == col ||
                     current_state.ghost_2.y == row && current_state.ghost_2.x == col ||
                     current_state.ghost_3.y == row && current_state.ghost_3.x == col ||
                     current_state.ghost_4.y == row && current_state.ghost_4.x == col) {
                addch(ACS_DIAMOND);
                printw(" ");
            }
            // Matrix
            else {
                printw("%c ", current_state.map[row][col]);
            }
            
        }
        printw("\n");
    }
}
