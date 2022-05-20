#include <stdio.h>     
#include <unistd.h>
#include <ncurses.h>

#include "../include/gamestate.h"
#include "../include/pacman.h"
#include "../include/util.h"

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
        Fix game moving faster when spamming input
*/

int main() 
{
    initscr();                      /* Start curses mode */
    cbreak();                       /* Disables line buffering, but still allows control characters */
    noecho();                       /* Disables echoing of characters typed */
    curs_set(FALSE);                /* Disables blinking curser */
    keypad(stdscr, TRUE);           /* Allows use of F1,F2, etc. and arrow keys!*/
    halfdelay(2);                   /* Characters typed are immediately available, but only wait X tenths of a second*/

    pacman pacman = init_pacman(3, 1, 3);
    game_state test_game = init_gamestate(pacman, test_map);    
   
    while(TRUE) {
        print_game_state(test_game);
        
        int direction = get_input(); /* The getch() function does an implicit refresh()  */
        test_game = update_gamestate(test_game, direction);
        
        clear();
    }
    
    endwin();                       /* End curses mode */
}
