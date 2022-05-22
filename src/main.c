#include <stdio.h>
#include <stdlib.h>     
#include <unistd.h>
#include <ncurses.h>

#include "../include/gamestate.h"
#include "../include/pacman.h"
#include "../include/util.h"

#define REFRESH_DELAY 700000
#define MAX_HEIGHT 40
#define MAX_WIDTH 60
#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4
#define COLOR_PACMAN 1
#define COLOR_GHOST 2

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
        Add comments to UI code
        Add colours!
    Bugs:
        Fix game moving faster when spamming input
*/

int main() 
{
    WINDOW *game_win;
    int start_x, start_y, width, height; 

    initscr();                      /* Start curses mode */
    cbreak();                       /* Disables line buffering, but still allows control characters */
    noecho();                       /* Disables echoing of characters typed */
    curs_set(FALSE);                /* Disables blinking curser */
    keypad(stdscr, TRUE);           /* Allows use of F1,F2, etc. and arrow keys!*/
    halfdelay(2);                   /* Characters typed are immediately available, but only wait X tenths of a second*/
    
    if (!has_colors()) {
        endwin();
        printf("Terminal does not support color\n");
        exit(1);
    }
    
    start_color();                  /* Allow colour attributes */
    init_pair(COLOR_PACMAN, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_GHOST, COLOR_RED, COLOR_BLACK);
    
    height = 22;
    width = 42;
    start_y = (LINES - height) / 2;
    start_x = (COLS - width) / 2;
    game_win = create_newwin(height, width, start_y, start_x);
 
    pacman pacman = init_pacman(3, 1, 3);
    game_state test_game = init_gamestate(pacman, test_map);    
    
    while(TRUE) {
        print_gamestate(test_game, game_win);
        
        int direction = get_input(game_win); /* The getch() function does an implicit refresh()  */
        test_game = update_gamestate(test_game, direction);
        
        wclear(game_win);
    }
    
    destroy_win(game_win);
    endwin();                       /* End curses mode */
}

