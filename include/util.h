#ifndef UTIL_H
#define UTIL_H

#include <ncurses.h>
#include "gamestate.h"
#include "pacman.h"
#include "ghost.h"

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4

int get_input();

int is_wall_collision(game_state current_state, int x, int y, int direction);

int is_wall_cell(game_state current_state, int x, int y);

/* A check if primary ghost will collide with any of the other ghosts */
int is_ghost_collision(ghost primary, ghost secondary, ghost tertiary, ghost quaternary);

void print_game_state(game_state current_state);
    
#endif