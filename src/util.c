#include <ncurses.h>
#include "../include/util.h"


int get_input(WINDOW *game_win)
{
    switch (wgetch(game_win)) {
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

// TODO: figure out a more elegant solution
int is_wall_collision(game_state current_state, int x, int y, int direction)
{
    switch (direction) {
        case DIR_RIGHT:
            if (is_wall_cell(current_state, x + 1, y)) {return true;}
            break;
        case DIR_LEFT:
            if (is_wall_cell(current_state, x - 1, y)) {return true;}
            break;
        case DIR_UP:
            if (is_wall_cell(current_state, x, y - 1)) {return true;}
            break;
        case DIR_DOWN:
            if (is_wall_cell(current_state, x, y + 1)) {return true;}
            break;
    }
    return false;
}

int is_wall_cell(game_state current_state, int x, int y)
{
    if (current_state.map[y][x] == '#') {
        return true;
    }
    return false;
}

int caught_by_ghost(game_state current_state)
{
    if (current_state.ghost_1.y == current_state.pacman.y && current_state.ghost_1.x == current_state.pacman.x ||
        current_state.ghost_2.y == current_state.pacman.y && current_state.ghost_2.x == current_state.pacman.x ||
        current_state.ghost_3.y == current_state.pacman.y && current_state.ghost_3.x == current_state.pacman.x ||
        current_state.ghost_4.y == current_state.pacman.y && current_state.ghost_4.x == current_state.pacman.x) {

        return true;
    }
    return false;
}

void print_gamestate(game_state current_state, WINDOW *game_win)
{
    int x, y; 
	getmaxyx(game_win, y, x);
    draw_borders(game_win);

    wmove(game_win, 1, 1);
    for (int row = 0; row < (MAX_ROWS); row++) {
        wmove(game_win, row + 1, 1);
        for (int col = 0; col < MAX_COLS; col++) {
            /* Pacman */
            if (current_state.pacman.y == row && current_state.pacman.x == col) {
                wattron(game_win, COLOR_PAIR(COLOR_PACMAN));
                switch (current_state.pacman.direction) {
                    case DIR_RIGHT:
                        waddch(game_win, ACS_LARROW);
                        wprintw(game_win, " ");
                        break;
                    case DIR_LEFT:
                        waddch(game_win, ACS_RARROW);
                        wprintw(game_win, " ");
                        break;
                    case DIR_UP:
                        // waddch(game_win, ACS_DARROW);           /* TODO: ACS_DARROW prints as ꓕ on my terminal, fix*/
                        wprintw(game_win, "V ");
                        break;
                    case DIR_DOWN:
                        waddch(game_win, ACS_UARROW);
                        wprintw(game_win, " ");
                        break;
                    default:
                        break;
                }
                wattroff(game_win, COLOR_PAIR(COLOR_PACMAN));
            }
            /* Ghost */
            else if (current_state.ghost_1.y == row && current_state.ghost_1.x == col ||
                     current_state.ghost_2.y == row && current_state.ghost_2.x == col ||
                     current_state.ghost_3.y == row && current_state.ghost_3.x == col ||
                     current_state.ghost_4.y == row && current_state.ghost_4.x == col) {
                wattron(game_win, COLOR_PAIR(COLOR_GHOST));
                waddch(game_win, ACS_DIAMOND);
                wattroff(game_win, COLOR_PAIR(COLOR_GHOST));
                wprintw(game_win, " ");
            }
            /* Matrix */
            else {
                wprintw(game_win, "%c ", current_state.map[row][col]);
            }
        }
        wmove(game_win, row + 1, 0);
    }
}

void print_info(game_state current_state, WINDOW *info_win)
{
    int x = getmaxx(info_win);
    
    draw_borders(info_win);
    mvwprintw(info_win, 1, 1, "Score: %d", current_state.pacman.score);
    mvwprintw(info_win, 1, x - 9, "Lives: %d", current_state.pacman.lives);
    // wmove(info_win, 1, x - 20);
    // wattron(info_win, COLOR_PAIR(COLOR_PACMAN));
    // for (int i = 1; i <= current_state.pacman.lives; i++) {
    //     waddch(info_win, ACS_LARROW);
    //     // wprintw(info_win, " ");
    // }
    // wattroff(info_win, COLOR_PAIR(COLOR_PACMAN));
    wrefresh(info_win);
}

void draw_borders(WINDOW *win) 
{ 
	int x, y; 
	getmaxyx(win, y, x); 

	/* Sides */ 
	for (int i = 0; i < y; i++) { 
		mvwprintw(win, i, 0, "|"); 
		mvwprintw(win, i, x - 1, "|"); 
	} 
	/* Top and bottom */
	for (int i = 0; i < x; i++) { 
		mvwprintw(win, 0, i, "-"); 
		mvwprintw(win, y - 1, i, "-"); 
	}
}

int is_ghost_collision(game_state current_state, ghost ghost, int direction) 
{
    switch (direction) {
        case DIR_RIGHT:
            if (is_ghost_cell(current_state, ghost.x + 1, ghost.y)) {return true;}
            break;
        case DIR_LEFT:
            if (is_ghost_cell(current_state, ghost.x - 1, ghost.y)) {return true;}
            break;
        case DIR_UP:
            if (is_ghost_cell(current_state, ghost.x, ghost.y - 1)) {return true;}
            break;
        case DIR_DOWN:
            if (is_ghost_cell(current_state, ghost.x, ghost.y + 1)) {return true;}
            break;
    }
    return false;
}

int is_ghost_cell(game_state current_state, int x, int y)
{
    if ((x == current_state.ghost_1.x && y == current_state.ghost_1.y) ||
        (x == current_state.ghost_2.x && y == current_state.ghost_2.y) ||
        (x == current_state.ghost_3.x && y == current_state.ghost_3.y) ||
        (x == current_state.ghost_4.x && y == current_state.ghost_4.y)) {
        
        return true;
    }

    return false;
}

WINDOW *create_newwin(int height, int width, int start_y, int start_x)
{
    WINDOW *local_win;

    local_win = newwin(height, width, start_y, start_x);
    box(local_win, 0, 0);       /* Gives default vertical/horizontal line characters */
    wrefresh(local_win);

    return local_win;
}

void destroy_win(WINDOW *local_win)
{
    delwin(local_win);
}