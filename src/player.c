#include "../include/player.h"

player init_player(int lives, int x, int y) {
    player new_player;
    
    new_player.lives = lives;
    new_player.x = x;
    new_player.y = y;
    new_player.direction = 1;
    new_player.energized = 0;

    return new_player;
}