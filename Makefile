all: pacman

pacman: src/main.c src/gamestate.c src/player.c src/ghost.c
	gcc -o pacman src/main.c src/gamestate.c src/player.c src/ghost.c -lncurses

clean:
	rm pacman