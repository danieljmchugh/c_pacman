#include "../include/pacman.h"
#include "../include/util.h"

pacman init_pacman(int lives, int x, int y) {
    pacman new_pacman;
    
    new_pacman.lives = lives;
    new_pacman.score = 0;
    new_pacman.x = x;
    new_pacman.y = y;
    new_pacman.direction = DIR_RIGHT;
    new_pacman.energized = 0;

    return new_pacman;
}