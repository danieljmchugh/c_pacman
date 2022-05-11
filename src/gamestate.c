#include <stdio.h>
#include <string.h>
#include "../include/gamestate.h"

game_state init_gamestate(player player, char map[MAX_ROWS][MAX_COLS]) 
{
    game_state new_game_state;
    strcpy(new_game_state.map, map);
    
    new_game_state.finished = 0;
    new_game_state.pacman = player;

    return new_game_state;
}

game_state update_gamestate(game_state current_state, int direction) {
    
    current_state.pacman.direction = direction;

    switch (current_state.pacman.direction) {
        case 1:
            current_state.pacman.x++;
            break;
        case 2:
            current_state.pacman.x--;
            break;
        case 3:
            current_state.pacman.y--;
            break;
        case 4:
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
        printf(": ");
        for (int col = 0; col < MAX_COLS; col++) {
            
            // Pacman
            if (current_state.pacman.y == row && current_state.pacman.x == col) {
                switch (current_state.pacman.direction) {
                    case 1:
                        printf("< ");
                        break;
                    case 2:
                        printf("> ");
                        break;
                    case 3:
                        printf("v ");
                        break;
                    case 4:
                        printf("Ʌ ");
                        break;
                    default:
                        break;
                }
            }
            // Matrix
            else {
                printf("%c ", current_state.map[row][col]);
            }
            
        }
        printf("\n");
    }
}
