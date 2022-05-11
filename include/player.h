#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x;
    int y;
    int direction; /* 1: right, 2: left, 3: up, 4: down*/
    int lives;
    int energized;
} player;

/* Initializes the new player with number of lives, x cordinates and y cordinates as arguments */
player init_player(int lives, int x, int y);

#endif