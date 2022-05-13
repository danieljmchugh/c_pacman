#include "../include/pacman.h"

pacman init_pacman(int lives, int x, int y) {
    pacman new_pacman;
    
    new_pacman.lives = lives;
    new_pacman.x = x;
    new_pacman.y = y;
    new_pacman.direction = 1;
    new_pacman.energized = 0;

    return new_pacman;
}