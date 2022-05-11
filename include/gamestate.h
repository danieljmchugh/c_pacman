#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "player.h"
#include "ghost.h"

typedef struct {
    char* map;

    struct player pacman;
    struct ghost ghost_1;
    struct ghost ghost_2;
    struct ghost ghost_3;

    int finished;
} game_state;

/* Initialized a gamestate, takes in a map as string and pre-made player object. This will allocate memory from heap 
   which should be freed when done */
game_state init_gamestate(char* map, struct player player);

/* Updates the gamestate based on the input given. Game checks and logic occur in here and returns the new gamestate */
game_state update_gamestate();

/* To free up allocated memory from the heap */
void destroy_gamestate();

#endif