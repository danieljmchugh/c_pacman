#include "../include/ghost.h"

ghost init_ghost(int x, int y) 
{
    ghost new_ghost;
    
    new_ghost.alive = 1;
    new_ghost.fleeing = 0;
    new_ghost.x = x;
    new_ghost.y = y;
    new_ghost.direction = 3;

    return new_ghost;
}

ghost update_ghost(ghost current_ghost) 
{
    
}