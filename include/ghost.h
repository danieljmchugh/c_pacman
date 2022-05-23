#ifndef GHOST_H
#define GHOST_H

typedef struct {
    int x;
    int y;
    int direction; /* 1: right, 2: left, 3: up, 4: down*/
    int alive;
    int fleeing;
} ghost;

ghost init_ghost(int x, int y);
    
#endif