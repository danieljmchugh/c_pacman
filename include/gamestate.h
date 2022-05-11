#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "player.h"
#include "ghost.h"

#define MAX_ROWS 20
#define MAX_COLS 20

typedef struct {
    char map[MAX_ROWS][MAX_COLS];

    player pacman;
    ghost ghost_1;
    ghost ghost_2;
    ghost ghost_3;

    int finished;
} game_state;

/* Initialized a gamestate, takes in a map as string and pre-made player object. This will allocate memory from heap 
   which should be freed when done */
game_state init_gamestate(player player, char map[MAX_ROWS][MAX_COLS]);

/* Updates the gamestate based on the input given. Game checks and logic occur in here and returns the new gamestate */
game_state update_gamestate(game_state current, int direction);

/* To free up allocated memory from the heap */
void destroy_gamestate();

void print_game_state(game_state current_game_state);

#endif