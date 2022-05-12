#include "../include/util.h"

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4

// TODO: figure out a more elegant solution
int is_collision(game_state current_state, int direction)
{
    switch (direction) {
        case DIR_RIGHT:
            if (is_wall_cell(current_state, current_state.pacman.x + 1, current_state.pacman.y)) {
                return 1;
            }
            break;
        case DIR_LEFT:
            if (is_wall_cell(current_state, current_state.pacman.x - 1, current_state.pacman.y)) {
                return 1;
            }
            break;
        case DIR_UP:
            if (is_wall_cell(current_state, current_state.pacman.x, current_state.pacman.y - 1)) {
                return 1;
            }
            break;
        case DIR_DOWN:
            if (is_wall_cell(current_state, current_state.pacman.x, current_state.pacman.y + 1)) {
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