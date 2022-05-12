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
    {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
}; 

/*
    TODO:
        Implement the ghosts, spooky!
        Finish game game state logic
        Add curses windows so more info can be shown on screen (lives, score, etc.)

    Bugs:
        Fix pacman moving faster when player spams input 
*/


void print_matrix(char map[MAX_ROWS][MAX_COLS]);
int get_input();

int main() 
{
    initscr();                      /* Start curses mode */
    cbreak();                       /* Disables line buffering, but still allows control characters */
    noecho();                       /* Disables echoing of characters typed */
    curs_set(FALSE);                /* Disables blinking curser */
    keypad(stdscr, TRUE);           /* Allows use of F1,F2, etc. and arrow keys!*/
    halfdelay(5);                   /* Characters typed are immediately available, but only wait X tenths of a second*/



    player player = init_player(3, 1, 3);
    game_state test_game = init_gamestate(player, test_map);    
   
    
    while(TRUE) {
        print_game_state(test_game);
        
        
        int direction = get_input();
        test_game = update_gamestate(test_game, direction);
        
        clear();
    }
    
    endwin();                       /* End curses mode */
}

int get_input()
{
    int input = getch();     

    switch (input) {
        case 'd':
        case KEY_RIGHT:
            return DIR_RIGHT;
        case 'a':
        case KEY_LEFT:
            return DIR_LEFT;
        case 'w':
        case KEY_UP:
            return DIR_UP;
        case 's':
        case KEY_DOWN:
            return DIR_DOWN;
        default:
            return -1;
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
