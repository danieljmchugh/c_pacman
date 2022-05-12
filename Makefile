all: pacman

pacman: src/main.c src/gamestate.c src/player.c src/ghost.c src/util.c
	gcc -o pacman src/main.c src/gamestate.c src/player.c src/ghost.c src/util.c -lncurses

clean:
	rm pacman