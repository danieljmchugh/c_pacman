#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "../include/gamestate.h"
#include "../include/ghost.h"
#include "../include/util.h"


#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4

game_state init_gamestate(player player, char map[MAX_ROWS][MAX_COLS]) 
{
    game_state new_game;
    strcpy(new_game.map, map);
    
    new_game.finished = 0;
    new_game.pacman = player;
    new_game.ghost_1 = init_ghost(9, 12);
    
    return new_game;
}

game_state update_gamestate(game_state current_state, int new_direction) 
{    
    // If input is given
    if (new_direction != -1) {
        // Check collision with new direction
        if (!is_collision(current_state, new_direction)) {
            current_state.pacman.direction = new_direction;
        }
    }
   
    // Check collision with current direction - aka. don't move
    if (is_collision(current_state, current_state.pacman.direction)) {
        return current_state;
    }

    switch (current_state.pacman.direction) {
        case DIR_RIGHT:
            current_state.pacman.x++;
            break;
        case DIR_LEFT:
            current_state.pacman.x--;
            break;
        case DIR_UP:
            current_state.pacman.y--;
            break;
        case DIR_DOWN:
            current_state.pacman.y++;
            break;
        default:
            break;
    }

    // TODO: update ghosts

    // TODO: check if finished

    return current_state;
}

void destroy_gamestate() {}

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
            else if (current_state.ghost_1.y == row && current_state.ghost_1.x == col) {
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
