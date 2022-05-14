#include <ncurses.h>
#include "../include/util.h"

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4

int get_input()
{
    int input = getch();     

    switch (input) {
        case 'd':
        case KEY_RIGHT:
            return DIR_RIGHT;
        case 'a':
        case KEY_LEFT:
            return DIR_LEFT;
        case 'w':
        case KEY_UP:
            return DIR_UP;
        case 's':
        case KEY_DOWN:
            return DIR_DOWN;
        default:
            return -1;
    }
}

// TODO: figure out a more elegant solution
int is_wall_collision(game_state current_state, int x, int y, int direction)
{
    switch (direction) {
        case DIR_RIGHT:
            if (is_wall_cell(current_state, x + 1, y)) {return TRUE;}
            break;
        case DIR_LEFT:
            if (is_wall_cell(current_state, x - 1, y)) {return TRUE;}
            break;
        case DIR_UP:
            if (is_wall_cell(current_state, x, y - 1)) {return TRUE;}
            break;
        case DIR_DOWN:
            if (is_wall_cell(current_state, x, y + 1)) {return TRUE;}
            break;
    }
    return FALSE;
}

int is_wall_cell(game_state current_state, int x, int y)
{
    if (current_state.map[y][x] == '#') {
        return TRUE;
    }
    return FALSE;
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

int is_ghost_collision(game_state current_state, ghost ghost, int direction) 
{
    switch (direction) {
        case DIR_RIGHT:
            if (is_ghost_cell(current_state, ghost.x + 1, ghost.y)) {return TRUE;}
            break;
        case DIR_LEFT:
            if (is_ghost_cell(current_state, ghost.x - 1, ghost.y)) {return TRUE;}
            break;
        case DIR_UP:
            if (is_ghost_cell(current_state, ghost.x, ghost.y - 1)) {return TRUE;}
            break;
        case DIR_DOWN:
            if (is_ghost_cell(current_state, ghost.x, ghost.y + 1)) {return TRUE;}
            break;
    }
    return FALSE;
}

int is_ghost_cell(game_state current_state, int x, int y)
{
    if ((x == current_state.ghost_1.x && y == current_state.ghost_1.y) ||
        (x == current_state.ghost_2.x && y == current_state.ghost_2.y) ||
        (x == current_state.ghost_3.x && y == current_state.ghost_3.y) ||
        (x == current_state.ghost_4.x && y == current_state.ghost_4.y)) {
        
        return TRUE;
    }

    return FALSE;
}