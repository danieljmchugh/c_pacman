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
    TODO:
        Implement the ghosts, spooky!
        Finish game game state logic
        Add curses windows so more info can be shown on screen (lives, score, etc.)
        Add comments to UI code
    Bugs:
        Fix game moving faster when spamming input
*/

int main() 
{
    WINDOW *game_win;
    WINDOW *info_win;

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
    
    int height = 22;
    int width = 42;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;
    game_win = create_newwin(height, width, start_y, start_x);
    info_win = create_newwin(5, 42, start_y + 22, start_x);
 
    pacman pacman = init_pacman(3, 1, 3);
    game_state test_game = init_gamestate(pacman, test_map);    
        
    while(!test_game.finished) {
        print_gamestate(test_game, game_win);
        print_info(test_game, info_win);
        
        int direction = get_input(game_win); /* The getch() function does an implicit refresh()  */
        test_game = update_gamestate(test_game, direction);
        
        wclear(game_win);
    }
    
    destroy_win(game_win);
    destroy_win(info_win);

    mvprintw(LINES/2, COLS/2, "GAME OVER");
    refresh();
    sleep(2);
    
    endwin();                       /* End curses mode */
}

