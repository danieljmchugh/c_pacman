#ifndef UTIL_H
#define UTIL_H

#include "gamestate.h"
#include "player.h"
#include "ghost.h"

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4

int is_collision(game_state current_state, int direction);

int is_wall_cell(game_state current_state, int x, int y);

    
#endif