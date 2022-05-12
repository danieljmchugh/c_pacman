#include <stdio.h>
#include <string.h>
#include "../include/gamestate.h"

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4

game_state init_gamestate(player player, char map[MAX_ROWS][MAX_COLS]) 
{
    game_state new_game_state;
    strcpy(new_game_state.map, map);
    
    new_game_state.finished = 0;
    new_game_state.pacman = player;
    
    return new_game_state;
}

game_state update_gamestate(game_state current_state, int new_direction) {
    
    if (!is_collision(current_state, new_direction)) {
        current_state.pacman.direction = new_direction;
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
        printf(": ");
        for (int col = 0; col < MAX_COLS; col++) {
            
            // Pacman
            if (current_state.pacman.y == row && current_state.pacman.x == col) {
                switch (current_state.pacman.direction) {
                    case DIR_RIGHT:
                        printf("< ");
                        break;
                    case DIR_LEFT:
                        printf("> ");
                        break;
                    case DIR_UP:
                        printf("v ");
                        break;
                    case DIR_DOWN:
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