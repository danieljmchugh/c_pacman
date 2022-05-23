#include <stdio.h>
#include <stdlib.h>     
#include <unistd.h>
#include <ncurses.h>

#include "../include/gamestate.h"
#include "../include/pacman.h"
#include "../include/util.h"

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
 *   TODO:
 *       Implement the ghosts, spooky!
 *       Finish game game state logic
 *       Add curses windows so more info can be shown on screen (lives, score, etc.)
 *       Add comments to UI code
 *   Bugs:
 *       Fix game moving faster when spamming input
 */

int main() 
{
    WINDOW *game_win;
    WINDOW *info_win;

    initscr();                      /* Start curses mode */
    cbreak();                       /* Disables line buffering, but still allows control characters */
    noecho();                       /* Disables echoing of characters typed */
    curs_set(false);                /* Disables blinking curser */
    keypad(stdscr, true);           /* Allows use of F1,F2, etc. and arrow keys!*/
    halfdelay(2);                   /* Characters typed are immediately available, but only wait X tenths of a second*/
    
    if (!has_colors()) {
        endwin();
        printf("Terminal does not support color\n");
        exit(1);
    }
    
    start_color();                  /* Allow colour attributes */
    init_pair(COLOR_PACMAN, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_GHOST, COLOR_RED, COLOR_BLACK);
    
    int gamewin_y = 22;
    int gamewin_x = 42;

    int start_y = (LINES - gamewin_y) / 2;
    int start_x = (COLS - gamewin_x) / 2;
    game_win = create_newwin(gamewin_y, gamewin_x, start_y, start_x);
    info_win = create_newwin(5, gamewin_x, start_y + gamewin_y, start_x);
 
    pacman pacman = init_pacman(3, 1, 3);
    game_state game_state = init_gamestate(pacman, test_map);    
        
    while(!game_state.finished) {
        print_gamestate(game_state, game_win);
        print_info(game_state, info_win);
        /* The getch() function does an implicit refresh()  */
        int direction = get_input(game_win); 
        game_state = update_gamestate(game_state, direction);
    }
    
    destroy_win(game_win);
    destroy_win(info_win);

    mvprintw(LINES/2, COLS/2, "GAME OVER");
    refresh();
    sleep(2);
    
    endwin();                       /* End curses mode */
}

