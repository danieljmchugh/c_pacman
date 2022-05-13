#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "../include/gamestate.h"
#include "../include/ghost.h"
#include "../include/util.h"


#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4

game_state init_gamestate(pacman pacman, char map[MAX_ROWS][MAX_COLS]) 
{
    game_state new_game;
    strcpy(new_game.map, map);
    
    new_game.finished = FALSE;
    new_game.pacman = pacman;
    new_game.ghost_1 = init_ghost(9, 12);
    new_game.ghost_2 = init_ghost(9, 13);
    new_game.ghost_3 = init_ghost(10, 12);
    new_game.ghost_4 = init_ghost(10, 13);
    
    return new_game;
}

game_state update_gamestate(game_state current_state, int new_direction) 
{    
    current_state.pacman = update_pacman(current_state, current_state.pacman, new_direction);
    // TODO: update ghosts
    current_state.ghost_1 = update_ghost(current_state, current_state.ghost_1);
    current_state.ghost_2 = update_ghost(current_state, current_state.ghost_2);
    current_state.ghost_3 = update_ghost(current_state, current_state.ghost_3);
    current_state.ghost_4 = update_ghost(current_state, current_state.ghost_4);
    // TODO: check if finished

    return current_state;
}

pacman update_pacman(game_state current_state, pacman pacman, int new_direction)
{
    // If input is given
    if (new_direction != -1) {
        // Check collision with new direction
        if (!is_wall_collision(current_state, pacman.x, pacman.y, new_direction)) {
            pacman.direction = new_direction;
        }
    }
   
    // Check collision with current direction - aka. don't move
    if (is_wall_collision(current_state, pacman.x, pacman.y, pacman.direction)) {
        return pacman;
    }

    switch (pacman.direction) {
        case DIR_RIGHT:
            pacman.x++;
            break;
        case DIR_LEFT:
            pacman.x--;
            break;
        case DIR_UP:
            pacman.y--;
            break;
        case DIR_DOWN:
            pacman.y++;
            break;
        default:
            break;
    }

    return pacman;
}

ghost update_ghost(game_state current_state, ghost ghost)
{
    /* Temporary implementation: ghost will randomize its movement */

    srand(time(NULL));
    int valid_direction = FALSE; 
    while (!valid_direction) {
        
        int direction = rand() % (4 + 1 - 1) + 1;

        if (!is_wall_collision(current_state, ghost.x, ghost.y, direction)
            // TODO: Stop ghost collision
        ) {
            ghost.direction = direction;
            valid_direction = TRUE;
        }
    }

    switch (ghost.direction) {
        case DIR_RIGHT:
            ghost.x++;
            break;
        case DIR_LEFT:
            ghost.x--;
            break;
        case DIR_UP:
            ghost.y--;
            break;
        case DIR_DOWN:
            ghost.y++;
            break;
        default:
            break;
    }

    return ghost;
}

void destroy_gamestate() {}

