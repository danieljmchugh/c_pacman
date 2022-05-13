#ifndef GHOST_H
#define GHOST_H

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4

typedef struct {
    int x;
    int y;
    int direction; /* 1: right, 2: left, 3: up, 4: down*/
    int alive;
    int fleeing;
} ghost;

ghost init_ghost(int x, int y);
    
#endif