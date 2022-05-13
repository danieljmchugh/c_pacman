#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "pacman.h"
#include "ghost.h"

#define MAX_ROWS 20
#define MAX_COLS 20

typedef struct {
    char map[MAX_ROWS][MAX_COLS];

    pacman pacman;
    ghost ghost_1;
    ghost ghost_2;
    ghost ghost_3;
    ghost ghost_4;

    int finished;
} game_state;

/* Initialized a gamestate, takes in a map as string and pre-made pacman object. This will allocate memory from heap 
   which should be freed when done */
game_state init_gamestate(pacman pacman, char map[MAX_ROWS][MAX_COLS]);

/* Updates the gamestate based on the input given. Game checks and logic occur in here and returns the new gamestate */
game_state update_gamestate(game_state current_state, int direction);

pacman update_pacman(game_state current_state, pacman pacman, int new_direction);

ghost update_ghost(game_state current_state, ghost ghost);

/* To free up allocated memory from the heap */
void destroy_gamestate();


#endif