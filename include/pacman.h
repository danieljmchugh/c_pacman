#ifndef pacman_H
#define pacman_H

typedef struct {
    int x;
    int y;
    int direction; /* 1: right, 2: left, 3: up, 4: down*/
    int lives;
    int energized;
} pacman;

/* Initializes the new pacman with number of lives, x cordinates and y cordinates as arguments */
pacman init_pacman(int lives, int x, int y);

#endif