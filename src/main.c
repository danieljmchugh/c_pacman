#include <stdio.h>      // printf
#include <unistd.h>     // sleep
#include <ncurses.h>

#include "../include/gamestate.h"
#include "../include/player.h"

#define REFRESH_DELAY 700000
#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4


char test_map[20][20] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ','#','#',' ','#','#','#',' ','#','#',' ','#','#','#',' ','#','#',' ','#'},
    {'#',' ','#','#',' ','#','#','#',' ','#','#',' ','#','#','#',' ','#','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ','#','#','#',' ','#',' ','#','#','#','#',' ','#',' ','#','#','#',' ','#'},
    {'#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#'},
    {'#','#',' ','#',' ',' ','#','#','#',' ',' ','#','#','#',' ',' ','#',' ','#','#'},
    {'#','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#','#'},
    {'#','#','#','#','#',' ','#',' ','#',' ',' ','#',' ','#',' ','#','#','#','#','#'},
    {'#','#',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ','#','#'},
    {'#','#',' ','#','#',' ','#',' ','#',' ',' ','#',' ','#',' ','#','#',' ','#','#'},
    {'#',' ',' ','#','#',' ','#',' ','#','#','#','#',' ','#',' ','#','#',' ',' ','#'},
    {'#',' ','#','#',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ','#','#',' ','#'},
    {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#',' ',' ','#','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
}; 

/*
    TODO:
        Will likely user (n)curses for better terminal and input control
        
        scanf buffers input until Enter is pressed, find solution to circumnavigate this behaviour
*/


void print_matrix(char map[MAX_ROWS][MAX_COLS]);
int input();

int main() 
{

    player player = init_player(3, 1, 3);

    game_state test_game = init_gamestate(player, test_map);
    
    
    while(1) {
        printf("\e[1;1H\e[2J"); // clears terminal
        
        print_game_state(test_game);
        int direction = input();
        test_game = update_gamestate(test_game, direction);
        usleep(REFRESH_DELAY);
    }
    
}

int input()
{
    char input;
    
    scanf(" %c", &input); // space before to ignore whitespaces 

    switch (input) {
        case 'd':
            return DIR_RIGHT;
            break;
        case 'a':
            return DIR_LEFT;
            break;
        case 'w':
            return DIR_UP;
            break;
        case 's':
            return DIR_DOWN;
            break;
        default:
            return 0;
            break;
    }
}


void print_matrix(char map[MAX_ROWS][MAX_COLS])
{
    for (int row = 0; row < MAX_ROWS; row++) {
        printf(": ");
        for (int col = 0; col < MAX_COLS; col++) {
            
            printf("%c ", map[row][col]);
        }
        printf("\n");
    }
}
