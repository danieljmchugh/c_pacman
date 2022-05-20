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
int is_ghost_collision(game_state current_state, ghost ghost, int direction); 

int is_ghost_cell(game_state current_state, int x, int y);

void print_game_state(game_state current_state);

void move_actor(int x, int y, int direction);

WINDOW *create_newwin(int height, int width, int start_y, int start_x);

WINDOW destroy_win(WINDOW *local_win);

#endif